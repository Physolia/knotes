/*
   SPDX-FileCopyrightText: 2013-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "knotefinddialog.h"
#include "widget/notelistwidget.h"

#include <PIM/notequery.h>
#include <PIM/resultiterator.h>

#include <KLocalizedString>
#include <QIcon>
#include <QLineEdit>
#include <QPushButton>

#include <KConfigGroup>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QLabel>
#include <QListWidget>
#include <QMenu>
#include <QVBoxLayout>

KNoteFindDialog::KNoteFindDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Search Notes"));
    auto mainLayout = new QVBoxLayout(this);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &KNoteFindDialog::reject);
    setAttribute(Qt::WA_DeleteOnClose);
    mNoteFindWidget = new KNoteFindWidget(this);
    connect(mNoteFindWidget, &KNoteFindWidget::noteSelected, this, &KNoteFindDialog::noteSelected);
    mainLayout->addWidget(mNoteFindWidget);
    mainLayout->addWidget(buttonBox);
    readConfig();
}

KNoteFindDialog::~KNoteFindDialog()
{
    writeConfig();
}

void KNoteFindDialog::setExistingNotes(const QHash<Akonadi::Item::Id, Akonadi::Item> &notes)
{
    mNoteFindWidget->setExistingNotes(notes);
}

void KNoteFindDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openStateConfig(), "KNoteFindDialog");
    grp.writeEntry("Size", size());
    grp.sync();
}

void KNoteFindDialog::readConfig()
{
    KConfigGroup grp(KSharedConfig::openStateConfig(), "KNoteFindDialog");
    const QSize size = grp.readEntry("Size", QSize(600, 300));
    if (size.isValid()) {
        resize(size);
    }
}

KNoteFindWidget::KNoteFindWidget(QWidget *parent)
    : QWidget(parent)
{
    auto vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 0, 0, 0);
    auto hbox = new QHBoxLayout;
    vbox->addLayout(hbox);
    auto lab = new QLabel(i18nc("@label:textbox", "Search notes:"), this);
    hbox->addWidget(lab);
    mSearchLineEdit = new QLineEdit(this);
    mSearchLineEdit->setClearButtonEnabled(true);
    connect(mSearchLineEdit, &QLineEdit::returnPressed, this, &KNoteFindWidget::slotSearchNote);
    connect(mSearchLineEdit, &QLineEdit::textChanged, this, &KNoteFindWidget::slotTextChanged);
    hbox->addWidget(mSearchLineEdit);

    mSearchButton = new QPushButton(QIcon::fromTheme(QStringLiteral("edit-find")), i18nc("@action:button Search notes", "Search..."), this);
    connect(mSearchButton, &QPushButton::clicked, this, &KNoteFindWidget::slotSearchNote);
    hbox->addWidget(mSearchButton);
    mSearchButton->setEnabled(false);

    // Result
    mNoteList = new NoteShared::NoteListWidget(this);
    mNoteList->setContextMenuPolicy(Qt::CustomContextMenu);
    mNoteList->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(mNoteList, &NoteShared::NoteListWidget::itemDoubleClicked, this, &KNoteFindWidget::slotItemDoubleClicked);
    connect(mNoteList, &NoteShared::NoteListWidget::customContextMenuRequested, this, &KNoteFindWidget::customContextMenuRequested);
    vbox->addWidget(mNoteList);

    mResultSearch = new QLabel(this);
    mResultSearch->setTextFormat(Qt::PlainText);
    vbox->addWidget(mResultSearch);

    mSearchLineEdit->setFocus();
}

KNoteFindWidget::~KNoteFindWidget() = default;

void KNoteFindWidget::setExistingNotes(const QHash<Akonadi::Item::Id, Akonadi::Item> &notes)
{
    mNotes = notes;
}

void KNoteFindWidget::slotItemDoubleClicked(QListWidgetItem *item)
{
    Q_EMIT noteSelected(mNoteList->itemId(item));
}

// code from kitinerary/src/lib/stringutil.cpp
static QString normalize(QStringView str)
{
    QString out;
    out.reserve(str.size());
    for (const auto c : str) {
        // case folding
        const auto n = c.toCaseFolded();

        // if the character has a canonical decomposition use that and skip the
        // combining diacritic markers following it
        // see https://en.wikipedia.org/wiki/Unicode_equivalence
        // see https://en.wikipedia.org/wiki/Combining_character
        if (n.decompositionTag() == QChar::Canonical) {
            out.push_back(n.decomposition().at(0));
        }
        // handle compatibility compositions such as ligatures
        // see https://en.wikipedia.org/wiki/Unicode_compatibility_characters
        else if (n.decompositionTag() == QChar::Compat && n.isLetter() && n.script() == QChar::Script_Latin) {
            out.append(n.decomposition());
        } else {
            out.push_back(n);
        }
    }
    return out;
}

void KNoteFindWidget::slotSearchNote()
{
    const QString searchStr = mSearchLineEdit->text().trimmed();
    if (searchStr.trimmed().isEmpty()) {
        return;
    }
    auto config = KConfig(QStringLiteral("akonadi_indexing_agent"));
    KConfigGroup cfg = config.group("General");
    const bool respectDiacriticAndAccents = cfg.readEntry("respectDiacriticAndAccents", true);
    const QString searchString = respectDiacriticAndAccents ? searchStr : normalize(searchStr);
    Akonadi::Search::PIM::NoteQuery query;
    query.matchNote(searchString);
    query.matchTitle(searchString);

    Akonadi::Search::PIM::ResultIterator it = query.exec();

    Akonadi::Item::List lst;
    while (it.next()) {
        const Akonadi::Item::Id id = it.id();
        if (mNotes.contains(id)) {
            lst << mNotes.value(id);
        }
    }
    mNoteList->setNotes(lst);
    if (lst.isEmpty()) {
        mResultSearch->setText(i18nc("@label", "No Results found in search."));
    } else {
        mResultSearch->clear();
    }
}

void KNoteFindWidget::slotTextChanged(const QString &text)
{
    mSearchButton->setEnabled(!text.trimmed().isEmpty());
}

void KNoteFindWidget::customContextMenuRequested(const QPoint &)
{
    QListWidgetItem *item = mNoteList->currentItem();
    QMenu menu(this);
    if (item) {
        menu.addAction(i18n("Show Note"), this, [this, item]() {
            Q_EMIT noteSelected(mNoteList->itemId(item));
        });
        menu.exec(QCursor::pos());
    }
}

/*******************************************************************
 KNotes -- Notes for the KDE project

 SPDX-FileCopyrightText: 2005 Michael Brade <brade@kde.org>

 SPDX-License-Identifier: GPL-2.0-or-later
*******************************************************************/

#include "notealarmdialog.h"

#include <KDateComboBox>
#include <KLocalizedString>
#include <KTimeComboBox>
#include <QVBoxLayout>
#include <QDateTime>

#include <QButtonGroup>
#include <QGroupBox>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>

using namespace NoteShared;

class NoteShared::NoteAlarmDialogPrivate
{
public:
    NoteAlarmDialogPrivate()
    {
    }

    KDateComboBox *m_atDate = nullptr;
    KTimeComboBox *m_atTime = nullptr;
    QButtonGroup *m_buttons = nullptr;
};

NoteAlarmDialog::NoteAlarmDialog(const QString &caption, QWidget *parent)
    : QDialog(parent)
    , d(new NoteShared::NoteAlarmDialogPrivate)
{
    setWindowTitle(caption);
    auto *mainLayout = new QVBoxLayout(this);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &NoteAlarmDialog::reject);
    QWidget *page = new QWidget(this);
    auto *pageVBoxLayout = new QVBoxLayout(page);
    pageVBoxLayout->setContentsMargins(0, 0, 0, 0);

    d->m_buttons = new QButtonGroup(this);
    QGroupBox *group = new QGroupBox(i18n("Scheduled Alarm"), page);
    pageVBoxLayout->addWidget(group);
    auto *layout = new QVBoxLayout;
    QRadioButton *none = new QRadioButton(i18n("&No alarm"));
    layout->addWidget(none);
    d->m_buttons->addButton(none, 0);

    group->setLayout(layout);

    QWidget *at = new QWidget;
    auto *atHBoxLayout = new QHBoxLayout(at);
    atHBoxLayout->setContentsMargins(0, 0, 0, 0);
    QRadioButton *label_at = new QRadioButton(i18n("Alarm &at:"), at);
    atHBoxLayout->addWidget(label_at);
    d->m_atDate = new KDateComboBox(at);
    atHBoxLayout->addWidget(d->m_atDate);
    d->m_atTime = new KTimeComboBox(at);
    atHBoxLayout->addWidget(d->m_atTime);
    const QDateTime dateTime = QDateTime::currentDateTime();
    d->m_atDate->setMinimumDate(dateTime.date());
    d->m_atTime->setMinimumTime(dateTime.time());
    atHBoxLayout->setStretchFactor(d->m_atDate, 1);
    layout->addWidget(at);
    d->m_buttons->addButton(label_at, 1);

    connect(d->m_buttons, qOverload<QAbstractButton *>(&QButtonGroup::buttonClicked), this, &NoteAlarmDialog::slotButtonChanged);
    connect(okButton, &QPushButton::clicked, this, &NoteAlarmDialog::accept);
    d->m_buttons->button(0)->setChecked(true);
    slotButtonChanged(d->m_buttons->checkedButton());
    mainLayout->addWidget(page);
    mainLayout->addWidget(buttonBox);
}

NoteAlarmDialog::~NoteAlarmDialog()
{
    delete d;
}

void NoteAlarmDialog::setAlarm(const QDateTime &dateTime)
{
    if (dateTime.isValid()) {
        d->m_buttons->button(1)->setChecked(true);
        d->m_atDate->setDate(dateTime.date());
        d->m_atTime->setTime(dateTime.time());
    } else {
        d->m_buttons->button(0)->setChecked(true);
    }
    slotButtonChanged(d->m_buttons->checkedButton());
}

void NoteAlarmDialog::slotButtonChanged(QAbstractButton *button)
{
    if (button) {
        const int id = d->m_buttons->id(button);
        switch (id) {
        case 0:
            d->m_atDate->setEnabled(false);
            d->m_atTime->setEnabled(false);
            break;
        case 1:
            d->m_atDate->setEnabled(true);
            d->m_atTime->setEnabled(true);
            break;
        }
    }
}

QDateTime NoteAlarmDialog::alarm() const
{
    if (d->m_buttons->checkedId() == 1) {
        return QDateTime(d->m_atDate->date(), d->m_atTime->time());
    } else {
        return QDateTime();
    }
}

/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef KNOTEEDITORCONFIGWIDGET_H
#define KNOTEEDITORCONFIGWIDGET_H

#include <QWidget>
#include "knotes_export.h"
class QSpinBox;
class QCheckBox;
class KFontRequester;
namespace NoteShared {
class NoteDisplayAttribute;
}

class KNOTES_EXPORT KNoteEditorConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KNoteEditorConfigWidget(QWidget *parent = nullptr);
    ~KNoteEditorConfigWidget();

    void load(NoteShared::NoteDisplayAttribute *attr, bool isRichText);
    void save(NoteShared::NoteDisplayAttribute *attr, bool &isRichText);

private:
    QSpinBox *kcfg_TabSize = nullptr;
    QCheckBox *kcfg_AutoIndent = nullptr;
    QCheckBox *kcfg_RichText = nullptr;
    KFontRequester *kcfg_Font = nullptr;
    KFontRequester *kcfg_TitleFont = nullptr;
};

#endif // KNOTEEDITORCONFIGWIDGET_H

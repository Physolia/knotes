/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef KNOTEDISPLAYCONFIGWIDGET_H
#define KNOTEDISPLAYCONFIGWIDGET_H

#include <QWidget>
#include "knotes_export.h"
class KColorButton;
class QCheckBox;
class QSpinBox;
namespace NoteShared {
class NoteDisplayAttribute;
}
class KNOTES_EXPORT KNoteDisplayConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KNoteDisplayConfigWidget(bool defaults, QWidget *parent = nullptr);
    ~KNoteDisplayConfigWidget();

    void load(NoteShared::NoteDisplayAttribute *attr);
    void save(NoteShared::NoteDisplayAttribute *attr);

private:
    KColorButton *kcfg_FgColor = nullptr;
    KColorButton *kcfg_BgColor = nullptr;
    QCheckBox *kcfg_ShowInTaskbar = nullptr;
    QCheckBox *kcfg_RememberDesktop = nullptr;
    QSpinBox *kcfg_Width = nullptr;
    QSpinBox *kcfg_Height = nullptr;
};

#endif // KNOTEDISPLAYCONFIGWIDGET_H

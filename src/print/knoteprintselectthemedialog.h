/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef KNOTEPRINTSELECTTHEMEDIALOG_H
#define KNOTEPRINTSELECTTHEMEDIALOG_H

#include <QDialog>
#include "knotes_export.h"

class KNotePrintSelectThemeComboBox;
class KNOTES_EXPORT KNotePrintSelectThemeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit KNotePrintSelectThemeDialog(QWidget *parent = nullptr);
    ~KNotePrintSelectThemeDialog() override;

    Q_REQUIRED_RESULT QString selectedTheme() const;

private:
    KNotePrintSelectThemeComboBox *mThemes = nullptr;
};

#endif // KNOTEPRINTSELECTTHEMEDIALOG_H

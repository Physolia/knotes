/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef SELECTEDNOTEFOLDERDIALOG_H
#define SELECTEDNOTEFOLDERDIALOG_H

#include <AkonadiWidgets/CollectionDialog>

namespace NoteShared
{
class SelectedNotefolderDialog : public Akonadi::CollectionDialog
{
    Q_OBJECT
public:
    explicit SelectedNotefolderDialog(QWidget *parent = nullptr);
    ~SelectedNotefolderDialog() override;

private:
    void readConfig();
    void writeConfig();
};
}

#endif // SELECTEDNOTEFOLDERDIALOG_H

/*
   SPDX-FileCopyrightText: 2014-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "knoteinterface.h"

KNoteInterface::KNoteInterface()
{
}

void KNoteInterface::setBlockSave(bool b)
{
    mBlockSave = b;
}

bool KNoteInterface::blockSave() const
{
    return mBlockSave;
}

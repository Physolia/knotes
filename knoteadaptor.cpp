/*
 * This file was generated by dbusidl2cpp version 0.6
 * Command line was: dbusidl2cpp -m -a knoteadaptor -- org.kde.KNotes.xml
 *
 * dbusidl2cpp is Copyright (C) 2006 Trolltech AS. All rights reserved.
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#include "knoteadaptor.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class KNotesAdaptor
 */

KNotesAdaptor::KNotesAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

KNotesAdaptor::~KNotesAdaptor()
{
    // destructor
}

void KNotesAdaptor::hideAllNotes()
{
    // handle method call org.kde.KNotes.hideAllNotes
    QMetaObject::invokeMethod(parent(), "hideAllNotes");

    // Alternative:
    //static_cast<YourObjectType *>(parent())->hideAllNotes();
}

void KNotesAdaptor::hideNote(const QString &noteId)
{
    // handle method call org.kde.KNotes.hideNote
    QMetaObject::invokeMethod(parent(), "hideNote", Q_ARG(QString, noteId));

    // Alternative:
    //static_cast<YourObjectType *>(parent())->hideNote(noteId);
}

void KNotesAdaptor::killNote(const QString &name, bool force)
{
    // handle method call org.kde.KNotes.killNote
    QMetaObject::invokeMethod(parent(), "killNote", Q_ARG(QString, name), Q_ARG(bool, force));

    // Alternative:
    //static_cast<YourObjectType *>(parent())->killNote(name, force);
}

void KNotesAdaptor::killNote(const QString &name)
{
    // handle method call org.kde.KNotes.killNote
    QMetaObject::invokeMethod(parent(), "killNote", Q_ARG(QString, name));

    // Alternative:
    //static_cast<YourObjectType *>(parent())->killNote(name);
}

QString KNotesAdaptor::newNote(const QString &name, const QString &text)
{
    // handle method call org.kde.KNotes.newNote
    QString out0;
    QMetaObject::invokeMethod(parent(), "newNote", Q_RETURN_ARG(QString, out0), Q_ARG(QString, name), Q_ARG(QString, text));

    // Alternative:
    //out0 = static_cast<YourObjectType *>(parent())->newNote(name, text);
    return out0;
}

QString KNotesAdaptor::newNoteFromClipboard(const QString &name)
{
    // handle method call org.kde.KNotes.newNoteFromClipboard
    QString out0;
    QMetaObject::invokeMethod(parent(), "newNoteFromClipboard", Q_RETURN_ARG(QString, out0), Q_ARG(QString, name));

    // Alternative:
    //out0 = static_cast<YourObjectType *>(parent())->newNoteFromClipboard(name);
    return out0;
}

void KNotesAdaptor::setName(const QString &noteId)
{
    // handle method call org.kde.KNotes.setName
    QMetaObject::invokeMethod(parent(), "setName", Q_ARG(QString, noteId));

    // Alternative:
    //static_cast<YourObjectType *>(parent())->setName(noteId);
}

void KNotesAdaptor::setName(const QString &noteId, const QString &newText)
{
    // handle method call org.kde.KNotes.setName
    QMetaObject::invokeMethod(parent(), "setName", Q_ARG(QString, noteId), Q_ARG(QString, newText));

    // Alternative:
    //static_cast<YourObjectType *>(parent())->setName(noteId, newText);
}

void KNotesAdaptor::showAllNotes()
{
    // handle method call org.kde.KNotes.showAllNotes
    QMetaObject::invokeMethod(parent(), "showAllNotes");

    // Alternative:
    //static_cast<YourObjectType *>(parent())->showAllNotes();
}

void KNotesAdaptor::showNote(const QString &noteId)
{
    // handle method call org.kde.KNotes.showNote
    QMetaObject::invokeMethod(parent(), "showNote", Q_ARG(QString, noteId));

    // Alternative:
    //static_cast<YourObjectType *>(parent())->showNote(noteId);
}


#include "knoteadaptor.moc"

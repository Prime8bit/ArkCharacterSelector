#include "CharacterManager.h"

CharacterManager::CharacterManager(QObject *parent)
    : QAbstractListModel(parent)
{
    //for debugging
    _watcher.addPath(".");
    //_watcher.addPath("../../Saved/SavedArksLocal");
    QObject::connect(&_watcher, SIGNAL(directoryChanged(QString)), this, SLOT(updateCharacters(QString)));

}

int CharacterManager::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _characters.count();
}

QVariant CharacterManager::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()
            || index.row() >= _characters.size()
            || role != Qt::DisplayRole)
        return QVariant();

    return _characters.at(index.row());
}

QVariant CharacterManager::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);

    // If the incorrect role or asking for
    // a row's header return empty
    if (role != Qt::DisplayRole
            || orientation == Qt::Vertical)
        return QVariant();

    return QString("Characters");
}


void updateCharacters(const QString &path)
{
    Q_UNUSED(path)
    qDebug("Folder changed.");
}

/**
void addCharacter(const QString &characterName)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _characters << characterName;
    endInsertRows();
}**/

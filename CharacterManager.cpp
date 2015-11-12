#include "CharacterManager.h"

//for debugging user _characterDir(".");
//for live user _characterDir("../Saved/SavedArksLocal");
CharacterManager::CharacterManager(QObject *parent)
    : QAbstractListModel(parent)
    , _characterDir(".")
{
    // TODO: Change to correct file extension
    _characterDir.setNameFilters(QStringList() << "*.txt");

    _watcher.addPath(_characterDir.absolutePath());

    qDebug("Watching: ");
    foreach (const QString &item, _watcher.directories())
        qDebug("" + item.toLatin1());

    QObject::connect(&_watcher, SIGNAL(directoryChanged(QString)), this, SLOT(updateCharacters(QString)));
    updateCharacters(_characterDir.absolutePath());
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


void CharacterManager::updateCharacters(const QString &path)
{
    // I already have a QDir corresponding to the only path
    // that will ever be used by this function
    // Parameter is required for _watcher.directoryChanged
    Q_UNUSED(path)

    beginRemoveRows(QModelIndex(), 0, _characters.count());
    _characters.clear();
    endRemoveRows();

    _characterDir.refresh();

    if (_characterDir.count() > 0)
    {
        beginInsertRows(QModelIndex(), 0, _characterDir.count() - 1);
        _characters = _characterDir.entryList();
        endInsertRows();
    }
}

/**
void addCharacter(const QString &characterName)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _characters << characterName;
    endInsertRows();
}**/

#include <fstream>
#include <sstream>
#include <vector>

#include "CharacterManager.h"

//for debugging use _characterDir(".");
//for live use _characterDir("../Saved/SavedArksLocal");
CharacterManager::CharacterManager(QObject *parent)
    : QAbstractListModel(parent)
    , _characterDir(".")
{
    _characterDir.setNameFilters(QStringList() << "*.arkprofile");

    _watcher.addPath(_characterDir.absolutePath());

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

    QStringList fileList = _characterDir.entryList();
    for (int i = 0; i < fileList.size(); i ++)
    {
        QString curFile = fileList.at(i);
        if (fileList.at(i) == "LocalPlayer.arkprofile")
        {
            _currentCharacter = parseLocalPlayer(curFile);
            fileList.replace(i, _localPlayerName);
        }
        else
        {
            int lastPeriodIndex = curFile.lastIndexOf(".");
            fileList.replace(i, curFile.left(lastPeriodIndex));
        }
    }

    if (_characterDir.count() > 0)
    {
        beginInsertRows(QModelIndex(), 0, _characterDir.count() - 1);
        _characters = fileList;
        endInsertRows();
    }
}

QString CharacterManager::parseLocalPlayer(const QString &fileName)
{
    std::ifstream input(fileName.toStdString(), std::ios::binary);
    std::stringstream formattedOutput;
    bool firstUnused = true;
    std::vector<std::string> tokens;

    if (input.is_open())
    {
        char curChar;
        while(input.get(curChar))
        {
            if (curChar < ' ' || curChar > '~')
            {
                if (firstUnused)
                {
                    firstUnused = false;
                    if (formattedOutput.rdbuf()->in_avail() > 0)
                        tokens.push_back(formattedOutput.str());
                    formattedOutput.str(std::string());
                }
            }
            else
            {
                firstUnused = true;
                formattedOutput << curChar;
            }
        }

        input.close();

        for(std::vector<std::string>::iterator iter = tokens.begin(); iter != tokens.end(); ++iter) {
            std::string curItem = *iter;
            if (curItem.compare("PlayerCharacterName") == 0
                    && ++iter != tokens.end())
            {
                return QString::fromStdString(*(++iter));
            }
        }
    }

    return QString("LocalProfile");
}

#include <fstream>
#include <sstream>
#include <vector>
#include <QProcess>
#include <QCoreApplication>

#include "CharacterManager.h"

//for debugging use _characterDir(".");
//for live use _characterDir("../../Saved/SavedArksLocal");
CharacterManager::CharacterManager(QObject *parent)
    : QAbstractListModel(parent)
    , _characterDir("../../Saved/SavedArksLocal")
    , _log("ArkCharacterSelector.log")
{
    _log.WriteLine("Starting Ark Character Selector.");
    if (!_characterDir.exists())
        _log.WriteLine(QString("ERROR: Directory %1 does not exist.").arg(_characterDir.absolutePath().toStdString().c_str()));
    _characterDir.setNameFilters(QStringList() << "*.local.arkprofile" << CHARACTERMANAGER_CURRENT_CHARACTER_FILENAME);

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

void CharacterManager::newCharacter()
{
    if (_currentCharacter.length() < 1)
        _currentCharacter = parseLocalCharacter();
    if (_characterDir.exists(CHARACTERMANAGER_CURRENT_CHARACTER_FILENAME))
    {
        // I add .local to the name because when ARK doesn't find LocalPlayer.arkprofile, it checks for (CharacterName).arkprofile
        // We need something that is different from (CharacterName).arkprofile
        if (!_characterDir.rename(CHARACTERMANAGER_CURRENT_CHARACTER_FILENAME, _currentCharacter.append(".local.arkprofile")))
        {
            _log.WriteLine(QString("ERROR: Unable to rename %1. Check your files/permissions and try again.").arg(_characterDir.absoluteFilePath(CHARACTERMANAGER_CURRENT_CHARACTER_FILENAME)).toLatin1());
            return;
        }
    }

    QProcess gameProcess;
    if(gameProcess.startDetached(".\\ShooterGame.exe"))
        QCoreApplication::quit();
    else
        _log.WriteLine("ERROR: Unable to start ARK: Survival Evolved. Ensure that ArkCharacterSelector exists in the same directory as the ShooterGame executable.");
}

void CharacterManager::playAsCharacter(int index)
{
    if (index > -1
            && index < _characters.size())
    {
        // If the selected character isn't the current character then
        // we need to swap file names
        if (_characters.at(index).compare(_currentCharacter) != 0)
        {
            if (_characterDir.exists(CHARACTERMANAGER_CURRENT_CHARACTER_FILENAME))
            {
                if (_currentCharacter.length() < 1)
                    _currentCharacter = parseLocalCharacter();
                if (!_characterDir.rename(CHARACTERMANAGER_CURRENT_CHARACTER_FILENAME, _currentCharacter.append(".local.arkprofile")))
                {
                    _log.WriteLine(QString("ERROR: Unable to rename %1. Check your files/permissions and try again.").arg(_characterDir.absoluteFilePath(CHARACTERMANAGER_CURRENT_CHARACTER_FILENAME)).toLatin1());
                    return;
                }
            }

            QString newFileName = QString("%1.local.arkprofile").arg(_characters.at(index));
            if (_characterDir.exists(newFileName))
            {
                if (_characterDir.rename(newFileName, CHARACTERMANAGER_CURRENT_CHARACTER_FILENAME))
                {
                    _log.WriteLine(QString("ERROR: Unable to rename %1. Check your files/permissions and try again.").arg(_characterDir.absoluteFilePath(newFileName)).toLatin1());
                    return;
                }
            }
        }

        QProcess gameProcess;
        if(gameProcess.startDetached(".\\ShooterGame.exe"))
            QCoreApplication::quit();
        else
            _log.WriteLine("ERROR: Unable to start ARK: Survival Evolved. Ensure that ArkCharacterSelector exists in the same directory as the ShooterGame executable.");
    }
}

void CharacterManager::deleteCharacter(int index)
{
    if (_characters.size() > index && index > -1)
    {
        QString characterFile("");
        if (characterFile.compare(_currentCharacter) == 0)
            characterFile = "LocalPlayer";
        else
        {
            characterFile = _characters.at(index);
            characterFile.append(".local");
        }

        characterFile.append(".arkprofile");
        if (_characterDir.exists(characterFile))
        {
            if (!_characterDir.remove(characterFile))
                _log.WriteLine(QString("ERROR: Unable to delete %1. Check your files/permissions and try again.").arg(_characterDir.absoluteFilePath(characterFile)).toLatin1());
        }
    }
}

QString CharacterManager::parseLocalCharacter()
{
    std::ifstream input(_characterDir.filePath(CHARACTERMANAGER_CURRENT_CHARACTER_FILENAME).toStdString(), std::ios::binary);
    std::stringstream formattedOutput;
    bool firstUnused = true;
    std::vector<std::string> tokens;

    if (!input.is_open())
        _log.WriteLine(QString("Unable to open %1").arg(CHARACTERMANAGER_CURRENT_CHARACTER_FILENAME));
    else
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

    return QString("BogusName");
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
        if (curFile.endsWith(".local.arkprofile"))
        {
            // The length of ".local.arkprofile" is 17. We want to trim it off.
            fileList.replace(i, curFile.left(curFile.length() - 17));
        }
        else if (curFile.compare(CHARACTERMANAGER_CURRENT_CHARACTER_FILENAME) == 0)
        {
            _currentCharacter = parseLocalCharacter();
            fileList.replace(i, _currentCharacter);
        }
    }

    fileList.sort();

    if (_characterDir.count() > 0)
    {
        beginInsertRows(QModelIndex(), 0, fileList.count() - 1);
        _characters = fileList;
        endInsertRows();
    }
}

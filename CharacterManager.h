#ifndef SELECTLISTMODEL_H
#define SELECTLISTMODEL_H

#include <QAbstractListModel>
#include <QFileSystemWatcher>
#include <QDir>

#define CHARACTERMANAGER_CURRENT_CHARACTER_FILENAME "LocalPlayer.arkprofile"

class CharacterManager : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CharacterManager(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void newCharacter();
    Q_INVOKABLE void playAsCharacter(int index);
    Q_INVOKABLE void deleteCharacter(int index);
signals:
    void dataChanged();

private:
    QStringList _characters;
    QFileSystemWatcher _watcher;
    QDir _characterDir;
    QString _currentCharacter;

    QString parseLocalCharacter();

private slots:
    void updateCharacters(const QString &path);

};

#endif // SELECTLISTMODEL_H

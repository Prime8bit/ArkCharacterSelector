#ifndef SELECTLISTMODEL_H
#define SELECTLISTMODEL_H

#include <QAbstractListModel>
#include <QFileSystemWatcher>
#include <QDir>

class CharacterManager : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString currentCharacter READ currentCharacter)
public:
    explicit CharacterManager(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void PlayAsCharacter(QString &characterName);
    Q_INVOKABLE void DeleteCharacter(QString &characterName);
signals:
    void dataChanged();
    QString currentCharacter() { return _currentCharacter; }

private:
    QStringList _characters;
    QFileSystemWatcher _watcher;
    QDir _characterDir;
    QString _currentCharacter;

    QString parseLocalPlayer(const QString &fileName);

private slots:
    void updateCharacters(const QString &path);

};

#endif // SELECTLISTMODEL_H

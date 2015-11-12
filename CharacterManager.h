#ifndef SELECTLISTMODEL_H
#define SELECTLISTMODEL_H

#include <QAbstractListModel>
#include <QFileSystemWatcher>
#include <QDir>

class CharacterManager : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CharacterManager(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

signals:
    void dataChanged();

private:
    QStringList _characters;
    QFileSystemWatcher _watcher;
    QDir _characterDir;

private slots:
    void updateCharacters(const QString &path);

};

#endif // SELECTLISTMODEL_H

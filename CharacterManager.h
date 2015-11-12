#ifndef SELECTLISTMODEL_H
#define SELECTLISTMODEL_H

#include <QAbstractListModel>
#include <QFileSystemWatcher>

class CharacterManager : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CharacterManager(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);

signals:
    void dataChanged();

private:
    QStringList _characters;
    QFileSystemWatcher _watcher;

private slots:
    void updateCharacters(const QString &path);

};

#endif // SELECTLISTMODEL_H

#ifndef SELECTLISTMODEL_H
#define SELECTLISTMODEL_H

#include <QAbstractListModel>

class SelectListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SelectListModel(const QStringList &items, QObject *parent = 0)
        : QAbstractListModel(parent)
        , listData(items)
    {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QStringList listData;
};

#endif // SELECTLISTMODEL_H

#include "selectlistmodel.h"

int SelectListModel::rowCount(const QModelIndex &parent = QModelIndex()) const
{
    return listData.count();
}

QVariant SelectListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()
            || index.row() >= listData.size()
            || role != Qt::DisplayRole)
        return QVariant();

    return listData.at(index.row());
}

QVariant SelectListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section)
}

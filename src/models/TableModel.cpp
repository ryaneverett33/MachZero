#include "machzero/models/TableModel.h"

TableModel::TableModel(QObject* parent = nullptr)
    : QAbstractTableModel(parent) 
    { }

QVariant TableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }
    if (role != QT::DisplayRole) {
        return QVariant();
    }
    
}
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != QT::DisplayRole) {
        return QVariant();
    }
    if (orientation != Qt::Horizontal) {
        return QVariant();
    }
    return HeaderTitles[section];
}
int TableModel::rowCount(const QModelIndex& parent) const {
    return _rows.size();
}
int TableModel::columnCount(const QModelIndex& parent) const {
    return HeaderTitles().size();
}

QList<QString> HeaderTitles() {
    return {"Offset", "Data", "Description", "Value"};
}
#include "machzero/models/EditableSheetModel.h"
#include "machzero/items/PositionItem.h"
#include <iostream>
#include <stack>
#include <cstring>
#include <llvm/ADT/StringRef.h>

bool EditableRow::IsColumnEditable(int columnIndex) {
    for (int editableIndex : EditableItems) { 
        if (editableIndex == columnIndex) {
            return true;
        }
    }
    return false;
}
QStandardItem* Row::GetItemByColumn(int columnIndex) {
    assert(columnIndex < Items.size());
    return Items[columnIndex];
}

EditableSheetModel::EditableSheetModel(QObject* parent)
    : QAbstractTableModel(parent)
    { }

void EditableSheetModel::setHorizontalHeaderLabels(const QStringList &labels) {
    _headerTitles = labels;
}

int EditableSheetModel::rowCount(const QModelIndex & /*parent*/) const
{
   return _rows.size();
}

int EditableSheetModel::columnCount(const QModelIndex & /*parent*/) const
{
    return _headerTitles.size();
}

QModelIndex EditableSheetModel::index(int row, int column, const QModelIndex& parent) const {
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }
    QStandardItem* item = _rows[row]->Items[column];
    return createIndex(row, column, item);
}

Qt::ItemFlags EditableSheetModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }
    Qt::ItemFlags baseFlags = QAbstractItemModel::flags(index);
    
    Row* row = _rows[index.row()];
    if (EditableRow* editableRow = dynamic_cast<EditableRow*>(row)) {
        if (editableRow->IsColumnEditable(index.column())) {
            return baseFlags | Qt::ItemIsEditable;
        }
    }

    return baseFlags;
}

QVariant EditableSheetModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation != Qt::Horizontal) {
        return QVariant();
    }
    if (section < _headerTitles.size()) {
        return _headerTitles[section];
    }
    return QVariant();
}

QVariant EditableSheetModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    QStandardItem* item = static_cast<QStandardItem*>(index.internalPointer());

    return item->text();
}

bool EditableSheetModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (value.toString().isEmpty()) {
        return false;
    }
    EditableRow* row = static_cast<EditableRow*>(_rows[index.row()]);

    if (row->EditFunction(index, value)) {
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
        return true;
    }
    return false;
}

Row* EditableSheetModel::appendRow(const QList<QStandardItem*>& items) {
    // TODO: don't do this
    QList<QStandardItem*> newItems;
    for (QStandardItem* item : items) {
        newItems.append(item);
    }
    Row* result = new Row(newItems);
    _rows.append(result);
    return result;
}
Row* EditableSheetModel::appendEditableRow(const QList<QStandardItem*>& items,
                                           std::function<bool(const QModelIndex&, const QVariant&)> editFunction,
                                           std::initializer_list<int> editableItems) {
    // TODO: don't do this
    QList<QStandardItem*> newItems;
    for (QStandardItem* item : items) {
        newItems.append(item);
    }
    Row* result = new EditableRow(newItems, editFunction, editableItems);
    _rows.append(result);
    return result;
}
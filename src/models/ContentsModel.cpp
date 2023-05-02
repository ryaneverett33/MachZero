#include "machzero/models/ContentsModel.h"
#include "machzero/items/ContentItem.h"
#include <iostream>

#include <llvm/BinaryFormat/MachO.h>

ContentsModel::ContentsModel(QObject* parent)
    : QAbstractItemModel(parent) {
        //_children.append(new ContentItem("Mach64 Header", 0));
        /*ContentItem* header = new ContentItem("Mach64 Header", nullptr, 0);
        llvm::MachO::mach_header_64 hdr = {0,1,2,3,4,5,6,7};
        header->Model = new MachHeaderModel(hdr);
        _children.append(header);*/
        /*ContentItem* exe = new ContentItem("Executable (ARM64_ALL)");
        exe->AddChild(new ContentItem("Mach64 Header"));
        exe->AddChild(new ContentItem("Load Commands"));
        exe->AddChild(new ContentItem("Section64 (__TEXT,__text)"));
        exe->AddChild(new ContentItem("Dynamic Loader Info"));

        AddItem(exe);*/
}
QVariant ContentsModel::data(const QModelIndex &index, int role) const {
    // Get the data (label) at a specific index
    // if the index isn't valid, return invalid data
    if (!index.isValid()) {
        return QVariant();
    }

    // if the role isn't for displaying data, return invalid data
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    // return the data for the item at the requested index
    ContentItem* item = static_cast<ContentItem*>(index.internalPointer());
    return item->data();
}
Qt::ItemFlags ContentsModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}
QModelIndex ContentsModel::index(int row, int column, const QModelIndex &parent) const {
    // Get the index of an item at (row, column) for a specific parent
    // If the parent is invalid, it's referring to this model. If it's valid, then it'll refer to a ContentItem with children
    // A basic model has these indices
    // Item1 (0,0)
    // Item2 (0,1)
    //      SubItem1 (1,0)
    //          SubItem2 (2,0)
    // Item3 (0,2)
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    ContentItem* childItem;

    if (parent.isValid()) {
        // If the parent is valid, then we need to find the child within the ContentItem
        ContentItem* parentItem = static_cast<ContentItem*>(parent.internalPointer());
        childItem = parentItem->GetChild(row);
        if (childItem == nullptr) {
            return QModelIndex();
        }
    }
    else {
        // If the parent is invalid, then we need to find the child within our list of items
        childItem = _children[row];
    }
    return createIndex(row, column, childItem);
}
QModelIndex ContentsModel::parent(const QModelIndex &index) const {
    // Gets the parent of an item at a specific index
    if (!index.isValid()) {
        return QModelIndex();
    }

    ContentItem* child = static_cast<ContentItem*>(index.internalPointer());
    ContentItem* parent = static_cast<ContentItem*>(child->Parent);

    // If the parent is null, then this model is the parent
    if (parent == nullptr) {
        return QModelIndex();
    }
    return createIndex(child->Row, 0, parent);
}
int ContentsModel::rowCount(const QModelIndex &parent) const {
    // get the number of rows for a given parent
    // If the parent isn't valid, then this model is considered the parent
    if (parent.isValid()) {
        ContentItem* child = static_cast<ContentItem*>(parent.internalPointer());
        return child->GetChildCount();
    }
    return _children.size();
}
int ContentsModel::columnCount(const QModelIndex &parent) const {
    return 1;
}

QAbstractItemModel* ContentsModel::GetModelAtIndex(QModelIndex& selected) {
    if (!selected.isValid()) {
        return nullptr;
    }
    //std::cout << "GetModelAtIndex(" << selected.row() << "," << selected.column() << ")\n";

    if (selected.parent().isValid()) {
        ContentItem* child = static_cast<ContentItem*>(selected.internalPointer());
        return child->Model;
    }
    else {
        // find this in our children
        return _children[selected.row()]->Model;
    }
}

void ContentsModel::AddItem(ContentItem* item) {
    item->Row = _children.size();
    beginInsertRows(QModelIndex(), _children.size(), 1);
    _children.append(item);
    endInsertRows();
}

ContentItem* ContentsModel::GetItemByLabel(QString label) {
    for (ContentItem* child : _children) {
        if (child->Label == label) {
            return child;
        }
    }
    return nullptr;
}

void ContentsModel::UpdateItemAtIndex(QModelIndex topLeft, QModelIndex bottomRight) {
    emit dataChanged(topLeft, bottomRight); 
}
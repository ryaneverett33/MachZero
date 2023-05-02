#pragma once

#include <QAbstractItemModel>
#include <QVariant>
#include <QStringList>
#include <QList>
#include <QStandardItem>
#include <functional>
#include <initializer_list>

class Row {
    public:
        Row(QList<QStandardItem*>& items)
            : Items(items) {}
        virtual ~Row() {}
        QStandardItem* GetItemByColumn(int columnIndex);

        QList<QStandardItem*> Items;
};

class EditableRow : public Row {
    public:
        EditableRow(QList<QStandardItem*>& items, 
                    std::function<bool(const QModelIndex&, const QVariant&)> editFunction, 
                    std::initializer_list<int> editableItems)
                    : Row(items),
                    EditFunction(editFunction),
                    EditableItems(editableItems) {}
        bool IsColumnEditable(int columnIndex);

        // TODO, this is a stupid way to store this info
        QList<int> EditableItems;
        std::function<bool(const QModelIndex& index, const QVariant&)> EditFunction;
};

class EditableSheetModel : public QAbstractTableModel {
    Q_OBJECT

    public:
        EditableSheetModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
        QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
        bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
        Qt::ItemFlags flags(const QModelIndex &index) const override;

        Row* appendRow(const QList<QStandardItem*>& items);
        Row* appendEditableRow(const QList<QStandardItem*>& items,
                               std::function<bool(const QModelIndex&, const QVariant&)> editFunction,
                               std::initializer_list<int> editableItems);
        void setHorizontalHeaderLabels(const QStringList& labels);

    private:
        QStringList _headerTitles;
        QList<Row*> _rows;
};
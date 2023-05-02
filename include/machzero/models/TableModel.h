#pragma once

#include <QAbstractTableModel>
#include <QVariant>
#include <QList>

// TODO what should we do here??

class TableRow {
    public:
        virtual QVariant data(int column);
};

/*class OffsetDataRow : public TableRow {
    public:
        OffsetDataRow(uint64_t offset, std::vector<std::byte> data, QString Description)
};*/

class TableModel : public QAbstractTableModel {
    Q_OBJECT

    public:
        TableModel(QObject* parent = nullptr);

        QVariant data(const QModelIndex& index, int role) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    protected:
        QList<QString> HeaderTitles();

    private:
        QList<TableRow> _rows;
};
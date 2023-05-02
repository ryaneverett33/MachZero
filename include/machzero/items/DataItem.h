#pragma once
#include <QStandardItem>
#include <QVariant>
#include <QString>
#include <vector>

class DataItem : public QStandardItem {
    public:
        DataItem(std::vector<std::byte>& data);
        DataItem(uint32_t data);

        virtual QVariant data(int role = Qt::UserRole + 1) const override;
    protected:
        DataItem()
            : QStandardItem() {}

        QString _dataString;

    private:
        std::vector<std::byte> Data;
};

class DecimalItem : public DataItem {
    public:
        DecimalItem(uint32_t data);
};
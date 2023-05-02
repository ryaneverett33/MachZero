#pragma once
#include <QStandardItem>
#include <QVariant>
#include <QString>

class PositionItem : public QStandardItem {
    public:
        PositionItem(uint64_t position);

        void ApplyRVAOffset(uint64_t offset);
        virtual QVariant data(int role = Qt::UserRole + 1) const override;

        uint64_t Position;
    private:
        QString _offsetString;
        QString _rvaString;
};
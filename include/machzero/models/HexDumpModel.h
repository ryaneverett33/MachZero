#pragma once

#include <llvm/Support/MemoryBufferRef.h>
#include "llvm/Support/MemoryBuffer.h"

#include <QAbstractTableModel>
#include <QVariant>

class HexDumpModel : public QAbstractTableModel {
    Q_OBJECT

    public:
        // TODO, make `end` a size value instead
        HexDumpModel(std::shared_ptr<llvm::WritableMemoryBuffer> data, uint64_t start, uint64_t end, QObject* parent = nullptr);

        QVariant data(const QModelIndex& index, int role) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        int columnCount(const QModelIndex& parent = QModelIndex()) const override;
        Qt::ItemFlags flags(const QModelIndex &index) const override;
        bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    private:
        std::shared_ptr<llvm::WritableMemoryBuffer> _data;
        uint64_t _dataStart;
        uint64_t _dataEnd;
};
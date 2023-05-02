#pragma once

#include <QStandardItemModel>
#include <QString>

#include <llvm/BinaryFormat/MachO.h>
#include "machzero/models/EditableSheetModel.h"

class LoadCommandModel : public EditableSheetModel {
    Q_OBJECT

    public:
        LoadCommandModel() = delete;
        LoadCommandModel(llvm::MachO::load_command& loadCommand,
                        const char* ptr,
                        const char* objectStartAddress,
                        QObject* parent = nullptr);
        uint64_t GetAddressOffset();
    private:
        bool editCommand(const QModelIndex& index, const QVariant& data);

        uint32_t _cmd;
        uint32_t _size;
        const char* _ptr;
        const char* _startAddress;
};
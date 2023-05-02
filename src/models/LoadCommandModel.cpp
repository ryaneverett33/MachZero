#include "machzero/models/LoadCommandModel.h"

#include "machzero/items/PositionItem.h"
#include "machzero/items/DataItem.h"
#include "machzero/Constants.h"
#include "machzero/Utils.h"

uint64_t LoadCommandModel::GetAddressOffset() {
    return reinterpret_cast<uint64_t>(_ptr) - reinterpret_cast<uint64_t>(_startAddress);
}

bool LoadCommandModel::editCommand(const QModelIndex& index, const QVariant& data) {
    printf("Called editCommand on column %d!\n", index.column());
    return false;
}

LoadCommandModel::LoadCommandModel(llvm::MachO::load_command& loadCommand, const char* ptr, const char* objectStartAddress, QObject* parent) 
    : EditableSheetModel(parent),
    _ptr(ptr),
    _startAddress(objectStartAddress),
    _cmd(loadCommand.cmd),
    _size(loadCommand.cmdsize) {
    setHorizontalHeaderLabels({"Offset", "Data", "Description", "Value"});

    appendEditableRow({new PositionItem(GetAddressOffset()), 
                new DataItem(static_cast<uint32_t>(loadCommand.cmd)), 
                new QStandardItem("Command"),
                new QStandardItem(Utils::loadCommandName(loadCommand.cmd))},
                std::bind(&LoadCommandModel::editCommand, this, std::placeholders::_1, std::placeholders::_2),
                {1,3});

    appendRow({new PositionItem(GetAddressOffset() + 4),
                new DataItem(static_cast<uint32_t>(loadCommand.cmdsize)),
                new QStandardItem("Command Size"),
                new DecimalItem(loadCommand.cmdsize)});
}
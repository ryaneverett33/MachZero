#include "machzero/models/LCMainModel.h"
#include "machzero/items/PositionItem.h"
#include "machzero/items/DataItem.h"

LCMainModel::LCMainModel(llvm::MachO::load_command& loadCommand,
                const char* ptr,
                const char* objectStartAddress,
                QObject* parent)
                : LoadCommandModel(loadCommand, ptr, objectStartAddress, parent) {
    llvm::MachO::entry_point_command* cmd = reinterpret_cast<llvm::MachO::entry_point_command*>(const_cast<char*>(ptr));
    _entryOffset = cmd->entryoff;
    _stackSize = cmd->stacksize;

    appendRow({new PositionItem(GetAddressOffset() + 8),
                new DataItem(_entryOffset),
                new QStandardItem("Entry Offset"),
                new DecimalItem(_entryOffset)});

    appendRow({new PositionItem(GetAddressOffset() + 16),
                new DataItem(_stackSize),
                new QStandardItem("Stack Size"),
                new DecimalItem(_stackSize)});
}
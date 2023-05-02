#pragma once

#include "machzero/models/LoadCommandModel.h"

class LCMainModel : public LoadCommandModel {
    Q_OBJECT

    public:
        LCMainModel() = delete;
        LCMainModel(llvm::MachO::load_command& loadCommand,
                        const char* ptr,
                        const char* objectStartAddress,
                        QObject* parent = nullptr);
    private:
        uint64_t _entryOffset;
        uint64_t _stackSize;
};
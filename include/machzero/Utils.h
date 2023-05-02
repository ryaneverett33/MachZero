#pragma once
#include <string>
#include <QString>

#include <llvm/ADT/Triple.h>
#include <llvm/Support/MemoryBuffer.h>

namespace Utils {
    void showError(std::string error);
    void showSuccess(std::string message);
    QString loadCommandName(uint32_t lc);
    void LoadBinary(QString file);
    void SaveBinary(QString file, std::shared_ptr<llvm::WritableMemoryBuffer> memoryBuffer);
};
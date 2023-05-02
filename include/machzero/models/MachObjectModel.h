#pragma once

#include <QStandardItemModel>
#include <QStringListModel>
#include <QModelIndex>
#include <vector>

// LLVM includes
#include <llvm/Object/Binary.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Object/MachO.h>

#include "machzero/models/ContentsModel.h"

class MachObjectModel : public ContentsModel {
    Q_OBJECT

    public:
        MachObjectModel() = delete;
        MachObjectModel(std::unique_ptr<llvm::object::MachOObjectFile> binary, 
                        std::shared_ptr<llvm::WritableMemoryBuffer> memoryBuffer, 
                        QObject* parent = nullptr);

        static MachObjectModel* FromBinary(std::unique_ptr<llvm::object::Binary>& binary, 
                                           std::unique_ptr<llvm::WritableMemoryBuffer>& memoryBuffer);
        std::shared_ptr<llvm::WritableMemoryBuffer> getMemory() {
            return _memoryBuffer;
        }
    private:
        void parseBinary();
        void parseHeader();
        void parseImmediates();
        void parseLoadCommands();

        std::unique_ptr<llvm::object::MachOObjectFile> _currentBinary;
        std::shared_ptr<llvm::WritableMemoryBuffer> _memoryBuffer;
        ContentItem* _rootItem;
};
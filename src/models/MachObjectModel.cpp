#include <iostream>

#include <QString>
#include <QStringList>
#include <llvm/BinaryFormat/MachO.h>
#include <llvm/ADT/Triple.h>

#include "machzero/models/MachObjectModel.h"
#include "machzero/models/LoadCommandModel.h"
#include "machzero/models/LCMainModel.h"
#include "machzero/Utils.h"
#include "machzero/models/MachHeaderModel.h"
#include "machzero/items/ContentItem.h"
#include "machzero/models/HexDumpModel.h"

MachObjectModel::MachObjectModel(std::unique_ptr<llvm::object::MachOObjectFile> binary, 
                        std::shared_ptr<llvm::WritableMemoryBuffer> memoryBuffer, 
                        QObject* parent)
    : ContentsModel(parent),
    _currentBinary(std::move(binary)),
    _memoryBuffer(std::move(memoryBuffer)) 
    {
        //_memoryBuffer->getBuffer()[0] = 'H';
        //_memoryBuffer->getBuffer()[1] = 'i';
    }

void MachObjectModel::parseBinary() {
    std::cout << "Parsing " << _currentBinary->getFileName().str() << std::endl;
    parseImmediates();
}

void MachObjectModel::parseHeader() {
    if (_currentBinary->is64Bit()) {
        llvm::MachO::mach_header_64 header = _currentBinary->getHeader64();
        _rootItem->AddChild(new ContentItem("Mach64 Header", new MachHeaderModel(header)));
    }
    else {
        llvm::MachO::mach_header header = _currentBinary->getHeader();
        _rootItem->AddChild(new ContentItem("Mach Header", new MachHeaderModel(header)));
    }
}
void MachObjectModel::parseLoadCommands() {
    llvm::object::MachOObjectFile::LoadCommandInfo firstLoadCommand = *(_currentBinary->begin_load_commands());
    llvm::object::MachOObjectFile::LoadCommandInfo lastLoadCommand = *(_currentBinary->end_load_commands() - 1);
    uint64_t loadCommandsStart = (uintptr_t)(firstLoadCommand.Ptr) - (uintptr_t)_memoryBuffer->getBufferStart();
    uint64_t loadCommandsSize = (uint64_t)(lastLoadCommand.Ptr - firstLoadCommand.Ptr) + lastLoadCommand.C.cmdsize;
    //printf("first lc: %p, last lc: %p\n", firstLoadCommand.Ptr, lastLoadCommand.Ptr);
    //printf("size: %llu, end-start: %llu, cmdsize: %u\n", loadCommandsSize, (uint64_t)(lastLoadCommand.Ptr - firstLoadCommand.Ptr), lastLoadCommand.C.cmdsize);

    ContentItem* loadCommands = new ContentItem("Load Commands", new HexDumpModel(_memoryBuffer, loadCommandsStart, loadCommandsStart+loadCommandsSize));
    _rootItem->AddChild(loadCommands);
    char* objectStartAddress = _memoryBuffer->getBufferStart();
    //printf("Start address: %p\n", objectStartAddress);

    for (llvm::object::MachOObjectFile::LoadCommandInfo inf : _currentBinary->load_commands()) {
        //printf("Load command address: %p\n", inf.Ptr);
        llvm::MachO::load_command lc = inf.C;
        LoadCommandModel* lcModel = nullptr;
        switch (lc.cmd) {
            default:
                lcModel = new LoadCommandModel(lc, inf.Ptr, objectStartAddress);
                break;
            case llvm::MachO::LC_MAIN:
                lcModel = new LCMainModel(lc, inf.Ptr, objectStartAddress);
                break;
        }

        QString name = Utils::loadCommandName(lc.cmd);
        loadCommands->AddChild(new ContentItem(name, lcModel));
    }
}

void MachObjectModel::parseImmediates() {
    QString topLevelName = QString::fromStdString("Executable (" + _currentBinary->getArchTriple().getArchName().str() + ")");
    _rootItem = new ContentItem(topLevelName, new HexDumpModel(_memoryBuffer, 0, _memoryBuffer->getBufferSize()));
    AddItem(_rootItem);
    parseHeader();
    parseLoadCommands();
}

MachObjectModel* MachObjectModel::FromBinary(std::unique_ptr<llvm::object::Binary>& binary, 
                                           std::unique_ptr<llvm::WritableMemoryBuffer>& memoryBuffer) {
    llvm::object::MachOObjectFile* machoBinary = llvm::dyn_cast<llvm::object::MachOObjectFile>(binary.release());
    std::unique_ptr<llvm::object::MachOObjectFile> smartMachoBinary(machoBinary);
    std::shared_ptr<llvm::WritableMemoryBuffer> smartMemoryBuffer(memoryBuffer.release());

    MachObjectModel* model = new MachObjectModel(std::move(smartMachoBinary), std::move(smartMemoryBuffer));
    model->parseBinary();

    return model;
}
#pragma once

#include <QStandardItemModel>
#include <QString>

#include <llvm/BinaryFormat/MachO.h>

class MachHeaderModel : public QStandardItemModel {
    Q_OBJECT

public:
    MachHeaderModel() = delete;
    MachHeaderModel(llvm::MachO::mach_header_64& header, QObject* parent = nullptr);
    MachHeaderModel(llvm::MachO::mach_header& header, QObject* parent = nullptr);

    void createMagicNumberRow(uint32_t magic);
    void createCPUTypeRow(uint32_t cpuType);
    void createCPUSubTypeRow(uint32_t cpuType, uint32_t cpuSubType);
    void createFileTypeRow(uint32_t fileType);
    void createNumLoadCommandsRow(uint32_t ncmds);
    void createSizeLoadCommandsRow(uint32_t sizeofcmds);
    void createFlagsRow(uint32_t flags);
    void createReservedRow(uint32_t reserved);

    QString Title;
    bool Is64Bit = false;
    union header {
        llvm::MachO::mach_header_64 header64;
        llvm::MachO::mach_header header32;
    };
    //llvm::mach_header_64& header64;
    //llvm::mach_header& header;
};
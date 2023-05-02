#include <QStandardItem>

#include "machzero/models/MachHeaderModel.h"
#include "machzero/items/PositionItem.h"
#include "machzero/items/DataItem.h"
#include "machzero/Constants.h"

QString getCPUSubType(uint32_t cpuType, uint32_t subType) {
    using namespace llvm::MachO;

    CPUType type = static_cast<CPUType>(cpuType);
    switch (type) {
        //case CPU_TYPE_X86:
        case CPU_TYPE_X86_64:
        case CPU_TYPE_I386:
            return GetX86CPUSubTypeName(subType);
        case CPU_TYPE_ARM:
            return GetARMCPUSubTypeName(subType);
        case CPU_TYPE_ARM64:
            return GetARM64CPUSubTypeName(subType);
        case CPU_TYPE_ARM64_32:
            return GetARM6432CPUSubTypeName(subType);
        case CPU_TYPE_POWERPC:
        case CPU_TYPE_POWERPC64:
            return GetPowerPCCPUSubTypeName(subType);
        default:
            return "UNKNOWN";
    }
}

std::vector<uint32_t> getFlagsSplit(uint32_t flags) {
    using namespace llvm::MachO;

    std::vector<uint32_t> flagArray;
    if ((flags & MH_NOUNDEFS) == MH_NOUNDEFS) { flagArray.push_back(MH_NOUNDEFS); }
    if ((flags & MH_INCRLINK) == MH_INCRLINK) { flagArray.push_back(MH_INCRLINK); }
    if ((flags & MH_DYLDLINK) == MH_DYLDLINK) { flagArray.push_back(MH_DYLDLINK); }
    if ((flags & MH_BINDATLOAD) == MH_BINDATLOAD) { flagArray.push_back(MH_BINDATLOAD); }
    if ((flags & MH_PREBOUND) == MH_PREBOUND) { flagArray.push_back(MH_PREBOUND); }
    if ((flags & MH_SPLIT_SEGS) == MH_SPLIT_SEGS) { flagArray.push_back(MH_SPLIT_SEGS); }
    if ((flags & MH_LAZY_INIT) == MH_LAZY_INIT) { flagArray.push_back(MH_LAZY_INIT); }
    if ((flags & MH_TWOLEVEL) == MH_TWOLEVEL) { flagArray.push_back(MH_TWOLEVEL); }
    if ((flags & MH_FORCE_FLAT) == MH_FORCE_FLAT) { flagArray.push_back(MH_FORCE_FLAT); }
    if ((flags & MH_NOMULTIDEFS) == MH_NOMULTIDEFS) { flagArray.push_back(MH_NOMULTIDEFS); }
    if ((flags & MH_NOFIXPREBINDING) == MH_NOFIXPREBINDING) { flagArray.push_back(MH_NOFIXPREBINDING); }
    if ((flags & MH_PREBINDABLE) == MH_PREBINDABLE) { flagArray.push_back(MH_PREBINDABLE); }
    if ((flags & MH_ALLMODSBOUND) == MH_ALLMODSBOUND) { flagArray.push_back(MH_ALLMODSBOUND); }
    if ((flags & MH_SUBSECTIONS_VIA_SYMBOLS) == MH_SUBSECTIONS_VIA_SYMBOLS) { flagArray.push_back(MH_SUBSECTIONS_VIA_SYMBOLS); }
    if ((flags & MH_CANONICAL) == MH_CANONICAL) { flagArray.push_back(MH_CANONICAL); }
    if ((flags & MH_WEAK_DEFINES) == MH_WEAK_DEFINES) { flagArray.push_back(MH_WEAK_DEFINES); }
    if ((flags & MH_BINDS_TO_WEAK) == MH_BINDS_TO_WEAK) { flagArray.push_back(MH_BINDS_TO_WEAK); }
    if ((flags & MH_ALLOW_STACK_EXECUTION) == MH_ALLOW_STACK_EXECUTION) { flagArray.push_back(MH_ALLOW_STACK_EXECUTION); }
    if ((flags & MH_ROOT_SAFE) == MH_ROOT_SAFE) { flagArray.push_back(MH_ROOT_SAFE); }
    if ((flags & MH_SETUID_SAFE) == MH_SETUID_SAFE) { flagArray.push_back(MH_SETUID_SAFE); }
    if ((flags & MH_NO_REEXPORTED_DYLIBS) == MH_NO_REEXPORTED_DYLIBS) { flagArray.push_back(MH_NO_REEXPORTED_DYLIBS); }
    if ((flags & MH_PIE) == MH_PIE) { flagArray.push_back(MH_PIE); }
    if ((flags & MH_DEAD_STRIPPABLE_DYLIB) == MH_DEAD_STRIPPABLE_DYLIB) { flagArray.push_back(MH_DEAD_STRIPPABLE_DYLIB); }
    if ((flags & MH_NO_HEAP_EXECUTION) == MH_NO_HEAP_EXECUTION) { flagArray.push_back(MH_NO_HEAP_EXECUTION); }
    if ((flags & MH_APP_EXTENSION_SAFE) == MH_APP_EXTENSION_SAFE) { flagArray.push_back(MH_APP_EXTENSION_SAFE); }
    if ((flags & MH_NLIST_OUTOFSYNC_WITH_DYLDINFO) == MH_NLIST_OUTOFSYNC_WITH_DYLDINFO) { flagArray.push_back(MH_NLIST_OUTOFSYNC_WITH_DYLDINFO); }
    if ((flags & MH_SIM_SUPPORT) == MH_SIM_SUPPORT) { flagArray.push_back(MH_SIM_SUPPORT); }
    if ((flags & MH_DYLIB_IN_CACHE) == MH_DYLIB_IN_CACHE) { flagArray.push_back(MH_DYLIB_IN_CACHE); }

    return flagArray;
}

void MachHeaderModel::createMagicNumberRow(uint32_t magic) {
    QStandardItem* magicName = new QStandardItem(GetMagicName(magic));
    appendRow({new PositionItem(0), new DataItem(magic), new QStandardItem("Magic Number"), magicName});
}

void MachHeaderModel::createCPUTypeRow(uint32_t cpuType) {
    QStandardItem* cpuTypeName = new QStandardItem(GetCPUTypeName(cpuType));
    appendRow({new PositionItem(4), new DataItem(cpuType), new QStandardItem("CPU Type"), cpuTypeName});
}

void MachHeaderModel::createCPUSubTypeRow(uint32_t cpuType, uint32_t cpuSubType) {
    QStandardItem* cpuSubTypeName = new QStandardItem(getCPUSubType(cpuType, cpuSubType));
    appendRow({new PositionItem(8), new DataItem(cpuSubType), new QStandardItem("CPU SubType"), new QStandardItem()});
    appendRow({new QStandardItem(), new QStandardItem(), new DataItem(cpuSubType), new QStandardItem("CPU_SUBTYPE_ARM64_ALL")});
}

void MachHeaderModel::createFileTypeRow(uint32_t fileType) {
    QStandardItem* fileTypeName = new QStandardItem(GetFileTypeName(fileType));
    appendRow({new PositionItem(12), new DataItem(fileType), new QStandardItem("File Type"), fileTypeName});
}

void MachHeaderModel::createNumLoadCommandsRow(uint32_t ncmds) {
    // todo make sizeofcmds be in decimal
    appendRow({new PositionItem(16), new DataItem(ncmds), new QStandardItem("Number of Load Commands"), new DecimalItem(ncmds)});
}

void MachHeaderModel::createSizeLoadCommandsRow(uint32_t sizeofcmds) {
    // todo make sizeofcmds be in decimal
    appendRow({new PositionItem(20), new DataItem(sizeofcmds), new QStandardItem("Size of Load Commands"), new DecimalItem(sizeofcmds)});
}

void MachHeaderModel::createFlagsRow(uint32_t flags) {
    appendRow({new PositionItem(24), new DataItem(flags), new QStandardItem("Flags"), new QStandardItem()});
    std::vector<uint32_t> flagArray = getFlagsSplit(flags);
    for (uint32_t flag : flagArray) {
        QStandardItem* flagName = new QStandardItem(GetHeaderFlagName(flag));
        appendRow({new QStandardItem(), new QStandardItem(), new DataItem(flag), flagName});
    }
}

void MachHeaderModel::createReservedRow(uint32_t reserved) {
    appendRow({new PositionItem(28), new DataItem(reserved), new QStandardItem("Reserved"), new DataItem(reserved)});
}

MachHeaderModel::MachHeaderModel(llvm::MachO::mach_header_64& header, QObject* parent) 
    : QStandardItemModel(parent) {
    Title = "Mach64 Header";
    Is64Bit = true;
    setHorizontalHeaderLabels({"Offset", "Data", "Description", "Value"});
    createMagicNumberRow(header.magic);
    createCPUTypeRow(header.cputype);
    createCPUSubTypeRow(header.cputype, header.cpusubtype);
    createFileTypeRow(header.filetype);
    createNumLoadCommandsRow(header.ncmds);
    createSizeLoadCommandsRow(header.sizeofcmds);
    createFlagsRow(header.flags);
    createReservedRow(header.reserved);
    //this->header64 = header;
}

MachHeaderModel::MachHeaderModel(llvm::MachO::mach_header& header, QObject* parent) 
    : QStandardItemModel(parent) {
    Title = "Mach Header";
    setHorizontalHeaderLabels({"Offset", "Data", "Description", "Value"});
    createMagicNumberRow(header.magic);
    createCPUTypeRow(header.cputype);
    createCPUSubTypeRow(header.cputype, header.cpusubtype);
    createFileTypeRow(header.filetype);
    createNumLoadCommandsRow(header.ncmds);
    createSizeLoadCommandsRow(header.sizeofcmds);
    createFlagsRow(header.flags);
    //this->header32 = header;
}
#include <llvm/BinaryFormat/MachO.h>
#include "machzero/Constants.h"

QString GetMagicName(uint32_t magic) {
    using namespace llvm::MachO;
    switch (magic) {
        case MH_MAGIC: { return "MH_MAGIC"; }
        case MH_CIGAM: { return "MH_CIGAM"; }
        case MH_MAGIC_64: { return "MH_MAGIC_64"; }
        case MH_CIGAM_64: { return "MH_CIGAM_64"; }
        case FAT_MAGIC: { return "FAT_MAGIC"; }
        case FAT_CIGAM: { return "FAT_CIGAM"; }
        case FAT_MAGIC_64: { return "FAT_MAGIC_64"; }
        case FAT_CIGAM_64: { return "FAT_CIGAM_64"; }
        default: { return "UNKNOWN"; }
    }
}

QString GetCPUTypeName(uint32_t cpuType) {
    using namespace llvm::MachO;

    CPUType type = static_cast<CPUType>(cpuType);
    switch (type) {
        case CPU_TYPE_ANY: { return "CPU_TYPE_ANY"; }
        case CPU_TYPE_I386: { return "CPU_TYPE_I386"; }
        case CPU_TYPE_X86_64: { return "CPU_TYPE_X86_64"; }
        case CPU_TYPE_ARM: { return "CPU_TYPE_ARM"; }
        case CPU_TYPE_ARM64: { return "CPU_TYPE_ARM64"; }
        case CPU_TYPE_ARM64_32: { return "CPU_TYPE_ARM64_32"; }
        case CPU_TYPE_SPARC: { return "CPU_TYPE_SPARC"; }
        case CPU_TYPE_POWERPC: { return "CPU_TYPE_POWERPC"; }
        case CPU_TYPE_POWERPC64: { return "CPU_TYPE_POWERPC64"; }
        // Duplicate case left for completeness only
        //case CPU_TYPE_X86: { return "CPU_TYPE_X86"; }
        default: { return "UNKNOWN"; }
    }
}

QString GetARMCPUSubTypeName(uint32_t cpuSubType) {
    using namespace llvm::MachO;

    CPUSubTypeARM type = static_cast<CPUSubTypeARM>(cpuSubType);
    switch (type) {
        case CPU_SUBTYPE_ARM_ALL: { return "CPU_SUBTYPE_ARM_ALL"; }
        case CPU_SUBTYPE_ARM_V4T: { return "CPU_SUBTYPE_ARM_V4T"; }
        case CPU_SUBTYPE_ARM_V6: { return "CPU_SUBTYPE_ARM_V6"; }
        case CPU_SUBTYPE_ARM_V5: { return "CPU_SUBTYPE_ARM_V5"; }
        case CPU_SUBTYPE_ARM_XSCALE: { return "CPU_SUBTYPE_ARM_XSCALE"; }
        case CPU_SUBTYPE_ARM_V7: { return "CPU_SUBTYPE_ARM_V7"; }
        case CPU_SUBTYPE_ARM_V7S: { return "CPU_SUBTYPE_ARM_V7S"; }
        case CPU_SUBTYPE_ARM_V7K: { return "CPU_SUBTYPE_ARM_V7K"; }
        case CPU_SUBTYPE_ARM_V6M: { return "CPU_SUBTYPE_ARM_V6M"; }
        case CPU_SUBTYPE_ARM_V7M: { return "CPU_SUBTYPE_ARM_V7M"; }
        case CPU_SUBTYPE_ARM_V7EM: { return "CPU_SUBTYPE_ARM_V7EM"; }
        // Duplicate case left for completeness only
        //case CPU_SUBTYPE_ARM_V5TEJ: { return "CPU_SUBTYPE_ARM_V5TEJ"; }
        default: { return "UNKNOWN"; }
    }
}

QString GetARM64CPUSubTypeName(uint32_t cpuSubType) {
    using namespace llvm::MachO;

    CPUSubTypeARM64 type = static_cast<CPUSubTypeARM64>(cpuSubType);
    switch (type) {
        case CPU_SUBTYPE_ARM64_ALL: { return "CPU_SUBTYPE_ARM64_ALL"; }
        case CPU_SUBTYPE_ARM64_V8: { return "CPU_SUBTYPE_ARM64_V8"; }
        case CPU_SUBTYPE_ARM64E: { return "CPU_SUBTYPE_ARM64E"; }
        default: { return "UNKNOWN"; }
    }
}

QString GetARM6432CPUSubTypeName(uint32_t cpuSubType) {
    using namespace llvm::MachO;

    CPUSubTypeARM64_32 type = static_cast<CPUSubTypeARM64_32>(cpuSubType);
    switch (type) {
        case CPU_SUBTYPE_ARM64_32_V8: { return "CPU_SUBTYPE_ARM64_32_V8"; }
        default: { return "UNKNOWN"; }
    }
}

QString GetX86CPUSubTypeName(uint32_t cpuSubType) {
    using namespace llvm::MachO;

    CPUSubTypeX86 type = static_cast<CPUSubTypeX86>(cpuSubType);
    switch (type) {

        case CPU_SUBTYPE_486: { return "CPU_SUBTYPE_486"; }
        case CPU_SUBTYPE_486SX: { return "CPU_SUBTYPE_486SX"; }
        case CPU_SUBTYPE_PENT: { return "CPU_SUBTYPE_PENT"; }
        case CPU_SUBTYPE_PENTPRO: { return "CPU_SUBTYPE_PENTPRO"; }
        case CPU_SUBTYPE_PENTII_M3: { return "CPU_SUBTYPE_PENTII_M3"; }
        case CPU_SUBTYPE_PENTII_M5: { return "CPU_SUBTYPE_PENTII_M5"; }
        case CPU_SUBTYPE_CELERON: { return "CPU_SUBTYPE_CELERON"; }
        case CPU_SUBTYPE_CELERON_MOBILE: { return "CPU_SUBTYPE_CELERON_MOBILE"; }
        case CPU_SUBTYPE_PENTIUM_3: { return "CPU_SUBTYPE_PENTIUM_3"; }
        case CPU_SUBTYPE_PENTIUM_3_M: { return "CPU_SUBTYPE_PENTIUM_3_M"; }
        case CPU_SUBTYPE_PENTIUM_3_XEON: { return "CPU_SUBTYPE_PENTIUM_3_XEON"; }
        case CPU_SUBTYPE_PENTIUM_M: { return "CPU_SUBTYPE_PENTIUM_M"; }
        case CPU_SUBTYPE_PENTIUM_4: { return "CPU_SUBTYPE_PENTIUM_4"; }
        case CPU_SUBTYPE_PENTIUM_4_M: { return "CPU_SUBTYPE_PENTIUM_4_M"; }
        case CPU_SUBTYPE_ITANIUM: { return "CPU_SUBTYPE_ITANIUM"; }
        case CPU_SUBTYPE_ITANIUM_2: { return "CPU_SUBTYPE_ITANIUM_2"; }
        case CPU_SUBTYPE_XEON: { return "CPU_SUBTYPE_XEON"; }
        case CPU_SUBTYPE_XEON_MP: { return "CPU_SUBTYPE_XEON_MP"; }
        case CPU_SUBTYPE_X86_64_ALL: { return "CPU_SUBTYPE_X86_64_ALL"; }
        // Duplicated cases left here for completeness sake only
        //case CPU_SUBTYPE_586: { return "CPU_SUBTYPE_586"; }
        //case CPU_SUBTYPE_X86_ARCH1: { return "CPU_SUBTYPE_X86_ARCH1"; }
        //case CPU_SUBTYPE_X86_64_H: { return "CPU_SUBTYPE_X86_64_H"; }
        //case CPU_SUBTYPE_I386_ALL: { return "CPU_SUBTYPE_I386_ALL"; }
        //case CPU_SUBTYPE_386: { return "CPU_SUBTYPE_386"; }
        //case CPU_SUBTYPE_X86_ALL: { return "CPU_SUBTYPE_X86_ALL"; }
        default: { return "UNKNOWN"; }
    }
}

QString GetPowerPCCPUSubTypeName(uint32_t cpuSubType) {
    using namespace llvm::MachO;

    CPUSubTypePowerPC type = static_cast<CPUSubTypePowerPC>(cpuSubType);
    switch (type) {
        case CPU_SUBTYPE_POWERPC_ALL: { return "CPU_SUBTYPE_POWERPC_ALL"; }
        case CPU_SUBTYPE_POWERPC_601: { return "CPU_SUBTYPE_POWERPC_601"; }
        case CPU_SUBTYPE_POWERPC_602: { return "CPU_SUBTYPE_POWERPC_602"; }
        case CPU_SUBTYPE_POWERPC_603: { return "CPU_SUBTYPE_POWERPC_603"; }
        case CPU_SUBTYPE_POWERPC_603e: { return "CPU_SUBTYPE_POWERPC_603e"; }
        case CPU_SUBTYPE_POWERPC_603ev: { return "CPU_SUBTYPE_POWERPC_603ev"; }
        case CPU_SUBTYPE_POWERPC_604: { return "CPU_SUBTYPE_POWERPC_604"; }
        case CPU_SUBTYPE_POWERPC_604e: { return "CPU_SUBTYPE_POWERPC_604e"; }
        case CPU_SUBTYPE_POWERPC_620: { return "CPU_SUBTYPE_POWERPC_620"; }
        case CPU_SUBTYPE_POWERPC_750: { return "CPU_SUBTYPE_POWERPC_750"; }
        case CPU_SUBTYPE_POWERPC_7400: { return "CPU_SUBTYPE_POWERPC_7400"; }
        case CPU_SUBTYPE_POWERPC_7450: { return "CPU_SUBTYPE_POWERPC_7450"; }
        case CPU_SUBTYPE_POWERPC_970: { return "CPU_SUBTYPE_POWERPC_970"; }
        // Duplicate cases left for completeness only
        //case CPU_SUBTYPE_MC980000_ALL: { return "CPU_SUBTYPE_MC980000_ALL"; }
        //case CPU_SUBTYPE_MC98601: { return "CPU_SUBTYPE_MC98601"; }
        default: { return "UNKNOWN"; }
    }
}

QString GetFileTypeName(uint32_t filetype) {
    using namespace llvm::MachO;

    HeaderFileType type = static_cast<HeaderFileType>(filetype);
    switch (type) {
        case MH_OBJECT: { return "MH_OBJECT"; }
        case MH_EXECUTE: { return "MH_EXECUTE"; }
        case MH_FVMLIB: { return "MH_FVMLIB"; }
        case MH_CORE: { return "MH_CORE"; }
        case MH_PRELOAD: { return "MH_PRELOAD"; }
        case MH_DYLIB: { return "MH_DYLIB"; }
        case MH_DYLINKER: { return "MH_DYLINKER"; }
        case MH_BUNDLE: { return "MH_BUNDLE"; }
        case MH_DYLIB_STUB: { return "MH_DYLIB_STUB"; }
        case MH_DSYM: { return "MH_DSYM"; }
        case MH_KEXT_BUNDLE: { return "MH_KEXT_BUNDLE"; }
        // maybe in a newer LLVM version?
        //case MH_FILESET: { return "MH_FILESET"; }
        default: { return "UNKNOWN"; }
    }
}

QString GetHeaderFlagName(uint32_t flag) {
    using namespace llvm::MachO;
    switch (flag) {
        case MH_NOUNDEFS: { return "MH_NOUNDEFS"; }
        case MH_INCRLINK: { return "MH_INCRLINK"; }
        case MH_DYLDLINK: { return "MH_DYLDLINK"; }
        case MH_BINDATLOAD: { return "MH_BINDATLOAD"; }
        case MH_PREBOUND: { return "MH_PREBOUND"; }
        case MH_SPLIT_SEGS: { return "MH_SPLIT_SEGS"; }
        case MH_LAZY_INIT: { return "MH_LAZY_INIT"; }
        case MH_TWOLEVEL: { return "MH_TWOLEVEL"; }
        case MH_FORCE_FLAT: { return "MH_FORCE_FLAT"; }
        case MH_NOMULTIDEFS: { return "MH_NOMULTIDEFS"; }
        case MH_NOFIXPREBINDING: { return "MH_NOFIXPREBINDING"; }
        case MH_PREBINDABLE: { return "MH_PREBINDABLE"; }
        case MH_ALLMODSBOUND: { return "MH_ALLMODSBOUND"; }
        case MH_SUBSECTIONS_VIA_SYMBOLS: { return "MH_SUBSECTIONS_VIA_SYMBOLS"; }
        case MH_CANONICAL: { return "MH_CANONICAL"; }
        case MH_WEAK_DEFINES: { return "MH_WEAK_DEFINES"; }
        case MH_BINDS_TO_WEAK: { return "MH_BINDS_TO_WEAK"; }
        case MH_ALLOW_STACK_EXECUTION: { return "MH_ALLOW_STACK_EXECUTION"; }
        case MH_ROOT_SAFE: { return "MH_ROOT_SAFE"; }
        case MH_SETUID_SAFE: { return "MH_SETUID_SAFE"; }
        case MH_NO_REEXPORTED_DYLIBS: { return "MH_NO_REEXPORTED_DYLIBS"; }
        case MH_PIE: { return "MH_PIE"; }
        case MH_DEAD_STRIPPABLE_DYLIB: { return "MH_DEAD_STRIPPABLE_DYLIB"; }
        case MH_HAS_TLV_DESCRIPTORS: { return "MH_HAS_TLV_DESCRIPTORS"; }
        case MH_NO_HEAP_EXECUTION: { return "MH_NO_HEAP_EXECUTION"; }
        case MH_APP_EXTENSION_SAFE: { return "MH_APP_EXTENSION_SAFE"; }
        case MH_NLIST_OUTOFSYNC_WITH_DYLDINFO: { return "MH_NLIST_OUTOFSYNC_WITH_DYLDINFO"; }
        case MH_SIM_SUPPORT: { return "MH_SIM_SUPPORT"; }
        case MH_DYLIB_IN_CACHE: { return "MH_DYLIB_IN_CACHE"; }
        default: { return "UNKNOWN"; }
    }
}
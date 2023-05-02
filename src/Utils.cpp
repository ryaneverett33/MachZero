#include "machzero/Utils.h"
#include <QMessageBox>
#include "machzero/WindowManager.h"

#include <iostream>
#include <fstream>

namespace Utils {
/*
 * After MacOS X 10.1 when a new load command is added that is required to be
 * understood by the dynamic linker for the image to execute properly the
 * LC_REQ_DYLD bit will be or'ed into the load command constant.  If the dynamic
 * linker sees such a load command it it does not understand will issue a
 * "unknown load command required for execution" error and refuse to use the
 * image.  Other load commands without this bit that are not understood will
 * simply be ignored.
 */
#define LC_REQ_DYLD 0x80000000

/* Constants for the cmd field of all load commands, the type */
#define	LC_SEGMENT	0x1	/* segment of this file to be mapped */
#define	LC_SYMTAB	0x2	/* link-edit stab symbol table info */
#define	LC_SYMSEG	0x3	/* link-edit gdb symbol table info (obsolete) */
#define	LC_THREAD	0x4	/* thread */
#define	LC_UNIXTHREAD	0x5	/* unix thread (includes a stack) */
#define	LC_LOADFVMLIB	0x6	/* load a specified fixed VM shared library */
#define	LC_IDFVMLIB	0x7	/* fixed VM shared library identification */
#define	LC_IDENT	0x8	/* object identification info (obsolete) */
#define LC_FVMFILE	0x9	/* fixed VM file inclusion (internal use) */
#define LC_PREPAGE      0xa     /* prepage command (internal use) */
#define	LC_DYSYMTAB	0xb	/* dynamic link-edit symbol table info */
#define	LC_LOAD_DYLIB	0xc	/* load a dynamically linked shared library */
#define	LC_ID_DYLIB	0xd	/* dynamically linked shared lib ident */
#define LC_LOAD_DYLINKER 0xe	/* load a dynamic linker */
#define LC_ID_DYLINKER	0xf	/* dynamic linker identification */
#define	LC_PREBOUND_DYLIB 0x10	/* modules prebound for a dynamically */
				/*  linked shared library */
#define	LC_ROUTINES	0x11	/* image routines */
#define	LC_SUB_FRAMEWORK 0x12	/* sub framework */
#define	LC_SUB_UMBRELLA 0x13	/* sub umbrella */
#define	LC_SUB_CLIENT	0x14	/* sub client */
#define	LC_SUB_LIBRARY  0x15	/* sub library */
#define	LC_TWOLEVEL_HINTS 0x16	/* two-level namespace lookup hints */
#define	LC_PREBIND_CKSUM  0x17	/* prebind checksum */

/*
 * load a dynamically linked shared library that is allowed to be missing
 * (all symbols are weak imported).
 */
#define	LC_LOAD_WEAK_DYLIB (0x18 | LC_REQ_DYLD)

#define	LC_SEGMENT_64	0x19	/* 64-bit segment of this file to be mapped */
#define	LC_ROUTINES_64	0x1a	/* 64-bit image routines */
#define LC_UUID		0x1b	/* the uuid */
#define LC_RPATH       (0x1c | LC_REQ_DYLD)    /* runpath additions */
#define LC_CODE_SIGNATURE 0x1d	/* local of code signature */
#define LC_SEGMENT_SPLIT_INFO 0x1e /* local of info to split segments */
#define LC_REEXPORT_DYLIB (0x1f | LC_REQ_DYLD) /* load and re-export dylib */
#define	LC_LAZY_LOAD_DYLIB 0x20	/* delay load of dylib until first use */
#define	LC_ENCRYPTION_INFO 0x21	/* encrypted segment information */
#define	LC_DYLD_INFO 	0x22	/* compressed dyld information */
#define	LC_DYLD_INFO_ONLY (0x22|LC_REQ_DYLD)	/* compressed dyld information only */
#define	LC_LOAD_UPWARD_DYLIB (0x23 | LC_REQ_DYLD) /* load upward dylib */
#define LC_VERSION_MIN_MACOSX 0x24   /* build for MacOSX min OS version */
#define LC_VERSION_MIN_IPHONEOS 0x25 /* build for iPhoneOS min OS version */
#define LC_FUNCTION_STARTS 0x26 /* compressed table of function start addresses */
#define LC_DYLD_ENVIRONMENT 0x27 /* string for dyld to treat like environment variable */
#define LC_MAIN (0x28|LC_REQ_DYLD) /* replacement for LC_UNIXTHREAD */
#define LC_DATA_IN_CODE 0x29 /* table of non-instructions in __text */
#define LC_SOURCE_VERSION 0x2A /* source version used to build binary */
#define LC_DYLIB_CODE_SIGN_DRS 0x2B /* Code signing DRs copied from linked dylibs */
#define	LC_ENCRYPTION_INFO_64 0x2C /* 64-bit encrypted segment information */
#define LC_LINKER_OPTION 0x2D /* linker options in MH_OBJECT files */
#define LC_LINKER_OPTIMIZATION_HINT 0x2E /* optimization hints in MH_OBJECT files */
#define LC_VERSION_MIN_TVOS 0x2F /* build for AppleTV min OS version */
#define LC_VERSION_MIN_WATCHOS 0x30 /* build for Watch min OS version */
#define LC_NOTE 0x31 /* arbitrary data included within a Mach-O file */
#define LC_BUILD_VERSION 0x32 /* build for platform min OS version */
#define LC_DYLD_EXPORTS_TRIE (0x33 | LC_REQ_DYLD) /* used with linkedit_data_command, payload is trie */
#define LC_DYLD_CHAINED_FIXUPS (0x34 | LC_REQ_DYLD) /* used with linkedit_data_command */
#define LC_FILESET_ENTRY      (0x35 | LC_REQ_DYLD) /* used with fileset_entry_command */

void showError(std::string error) {
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(error));
    msgBox.exec();
}
void showSuccess(std::string message) {
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(message));
    msgBox.exec();
}

QString loadCommandName(uint32_t cmd) {
    if (cmd == LC_SEGMENT) return "LC_SEGMENT";
    else if (cmd == LC_SYMTAB) return "LC_SYMTAB";
    else if (cmd == LC_SYMSEG) return "LC_SYMSEG";
    else if (cmd == LC_THREAD) return "LC_THREAD";
    else if (cmd == LC_UNIXTHREAD) return "LC_UNIXTHREAD";
    else if (cmd == LC_LOADFVMLIB) return "LC_LOADFVMLIB";
    else if (cmd == LC_IDFVMLIB) return "LC_IDFVMLIB";
    else if (cmd == LC_IDENT) return "LC_IDENT";
    else if (cmd == LC_FVMFILE) return "LC_FVMFILE";
    else if (cmd == LC_PREPAGE) return "LC_PREPAGE";
    else if (cmd == LC_DYSYMTAB) return "LC_DYSYMTAB";
    else if (cmd == LC_LOAD_DYLIB) return "LC_LOAD_DYLIB";
    else if (cmd == LC_ID_DYLIB) return "LC_ID_DYLIB";
    else if (cmd == LC_LOAD_DYLINKER) return "LC_LOAD_DYLINKER";
    else if (cmd == LC_ID_DYLINKER) return "LC_ID_DYLINKER";
    else if (cmd == LC_PREBOUND_DYLIB) return "LC_PREBOUND_DYLIB";
    else if (cmd == LC_ROUTINES) return "LC_ROUTINES";
    else if (cmd == LC_SUB_FRAMEWORK) return "LC_SUB_FRAMEWORK";
    else if (cmd == LC_SUB_UMBRELLA) return "LC_SUB_UMBRELLA";
    else if (cmd == LC_SUB_CLIENT) return "LC_SUB_CLIENT";
    else if (cmd == LC_SUB_LIBRARY) return "LC_SUB_LIBRARY";
    else if (cmd == LC_TWOLEVEL_HINTS) return "LC_TWOLEVEL_HINTS";
    else if (cmd == LC_PREBIND_CKSUM) return "LC_PREBIND_CKSUM";
    else if (cmd == LC_LOAD_WEAK_DYLIB) return "LC_LOAD_WEAK_DYLIB";
    else if (cmd == LC_SEGMENT_64) return "LC_SEGMENT_64";
    else if (cmd == LC_ROUTINES_64) return "LC_ROUTINES_64";
    else if (cmd == LC_UUID) return "LC_UUID";
    else if (cmd == LC_RPATH) return "LC_RPATH";
    else if (cmd == LC_CODE_SIGNATURE) return "LC_CODE_SIGNATURE";
    else if (cmd == LC_SEGMENT_SPLIT_INFO) return "LC_SEGMENT_SPLIT_INFO";
    else if (cmd == LC_REEXPORT_DYLIB) return "LC_REEXPORT_DYLIB";
    else if (cmd == LC_LAZY_LOAD_DYLIB) return "LC_LAZY_LOAD_DYLIB";
    else if (cmd == LC_ENCRYPTION_INFO) return "LC_ENCRYPTION_INFO";
    else if (cmd == LC_DYLD_INFO) return "LC_DYLD_INFO";
    else if (cmd == LC_DYLD_INFO_ONLY) return "LC_DYLD_INFO_ONLY";
    else if (cmd == LC_LOAD_UPWARD_DYLIB) return "LC_LOAD_UPWARD_DYLIB";
    else if (cmd == LC_VERSION_MIN_MACOSX) return "LC_VERSION_MIN_MACOSX";
    else if (cmd == LC_VERSION_MIN_IPHONEOS) return "LC_VERSION_MIN_IPHONEOS";
    else if (cmd == LC_FUNCTION_STARTS) return "LC_FUNCTION_STARTS";
    else if (cmd == LC_DYLD_ENVIRONMENT) return "LC_DYLD_ENVIRONMENT";
    else if (cmd == LC_MAIN) return "LC_MAIN";
    else if (cmd == LC_DATA_IN_CODE) return "LC_DATA_IN_CODE";
    else if (cmd == LC_SOURCE_VERSION) return "LC_SOURCE_VERSION";
    else if (cmd == LC_DYLIB_CODE_SIGN_DRS) return "LC_DYLIB_CODE_SIGN_DRS";
    else if (cmd == LC_ENCRYPTION_INFO_64) return "LC_ENCRYPTION_INFO_64";
    else if (cmd == LC_LINKER_OPTION) return "LC_LINKER_OPTION";
    else if (cmd == LC_LINKER_OPTIMIZATION_HINT) return "LC_LINKER_OPTIMIZATION_HINT";
    else if (cmd == LC_VERSION_MIN_TVOS) return "LC_VERSION_MIN_TVOS";
    else if (cmd == LC_VERSION_MIN_WATCHOS) return "LC_VERSION_MIN_WATCHOS";
    else if (cmd == LC_NOTE) return "LC_NOTE";
    else if (cmd == LC_BUILD_VERSION) return "LC_BUILD_VERSION";
    else if (cmd == LC_DYLD_EXPORTS_TRIE) return "LC_DYLD_EXPORTS_TRIE";
    else if (cmd == LC_DYLD_CHAINED_FIXUPS) return "LC_DYLD_CHAINED_FIXUPS";
    else if (cmd == LC_FILESET_ENTRY) return "LC_FILESET_ENTRY";
    return "UNKNOWN";
}

bool canOpenBinary(std::unique_ptr<llvm::object::Binary>& binary) {
    // Only MachO and MachO universal binaries are supported
    return binary->isMachO() || binary->isMachOUniversalBinary();
}
std::string getBinaryTypeString(std::unique_ptr<llvm::object::Binary>& binary) {
    switch (binary->getTripleObjectFormat()) {
        default:
            return "UNKNOWN";
        case llvm::Triple::ObjectFormatType::COFF:
            return "COFF";
        case llvm::Triple::ObjectFormatType::DXContainer:
            return "DXContainer";
        case llvm::Triple::ObjectFormatType::ELF:
            return "ELF";
        case llvm::Triple::ObjectFormatType::GOFF:
            return "GOFF";
        case llvm::Triple::ObjectFormatType::SPIRV:
            return "SPIRV";
        case llvm::Triple::ObjectFormatType::Wasm:
            return "WebAssembly";
        case llvm::Triple::ObjectFormatType::XCOFF:
            return "XCOFF";
    }
}

void LoadBinary(QString file) {
    std::cout << "Opening file: " << file.toStdString() << "\n";

    // open the binary as a memory buffer
    llvm::ErrorOr<std::unique_ptr<llvm::WritableMemoryBuffer>> errorOrMemory = 
        llvm::WritableMemoryBuffer::getFile(file.toStdString());
    if (!errorOrMemory) {
        showError("Encountered an error opening file: " + errorOrMemory.getError().message());
        return;
    }
    std::unique_ptr<llvm::WritableMemoryBuffer> memory = std::move(*errorOrMemory);

    // parse the binary from the memory buffer
    llvm::Expected<std::unique_ptr<llvm::object::Binary>> errorOrBinary = llvm::object::createBinary(memory->getMemBufferRef());
    if (!errorOrBinary) {
        std::error_code ec = llvm::errorToErrorCode(errorOrBinary.takeError());
        showError("Encountered an error parsing binary: " + ec.message());
    }
    std::unique_ptr<llvm::object::Binary> binary = std::move(*errorOrBinary);
    
    // try to open the binary
    // if we fail, then the data will be automatically deleted
    if (canOpenBinary(binary)) {
        WindowManager::getInstance().showBinaryWindow(binary, memory);
    }
    else {
        showError("Can't open binary of type: " + getBinaryTypeString(binary));
    }
}

void SaveBinary(QString file, std::shared_ptr<llvm::WritableMemoryBuffer> memoryBuffer) {
    std::cout << "Saving binary to " << file.toStdString() << "\n";

    try {
        std::ofstream outFile;
        outFile.open(file.toStdString());
        outFile.write(memoryBuffer->getBufferStart(), memoryBuffer->getBufferSize());
        outFile.close();
        showSuccess("Saved!");
    }
    catch (const std::ios_base::failure& failure) {
        showError("Failed to save, error: " + std::string(failure.what()));
    }
}
} // end namespace
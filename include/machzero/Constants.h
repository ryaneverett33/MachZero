#pragma once

#include <QString>

QString GetMagicName(uint32_t magic);
QString GetCPUTypeName(uint32_t cpuType);
QString GetARMCPUSubTypeName(uint32_t cpuSubType);
QString GetARM64CPUSubTypeName(uint32_t cpuSubType);
QString GetARM6432CPUSubTypeName(uint32_t cpuSubType);
QString GetX86CPUSubTypeName(uint32_t cpuSubType);
QString GetPowerPCCPUSubTypeName(uint32_t cpuSubType);
QString GetFileTypeName(uint32_t filetype);
QString GetHeaderFlagName(uint32_t flag);
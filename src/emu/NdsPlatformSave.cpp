#include "emu/NdsSession.hpp"

#include <Platform.h>
#include <cstdarg>
#include <cstdio>

namespace melonDS::Platform {

void SignalStop(StopReason, void*) {}

void Log(LogLevel level, const char* fmt, ...) {
    if (level == LogLevel::Debug) {
        return;
    }
    va_list args;
    va_start(args, fmt);
    std::vprintf(fmt, args);
    va_end(args);
}

void WriteNDSSave(const u8* savedata, u32 savelen, u32, u32, void* userdata) {
    if (auto* session = static_cast<emulocke::NdsSession*>(userdata)) {
        session->writeSave(savedata, savelen);
    }
}

void WriteGBASave(const u8*, u32, u32, u32, void*) {}

void WriteFirmware(const Firmware&, u32, u32, void*) {}

void WriteDateTime(int, int, int, int, int, int, void*) {}

}
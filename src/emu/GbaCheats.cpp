#include "emu/GbaSession.hpp"

#include "cheats/Lines.hpp"

#include <mgba/core/cheats.h>
#include <mgba/core/core.h>
#include <mgba/internal/gba/cheats.h>

namespace emulocke {
namespace {

bool addGbaLines(mCheatSet* set, std::string_view code) {
    bool any = false;
    for (const std::string& line : cheatLines(code)) {
        if (cheatComment(line)) {
            continue;
        }
        if (!mCheatAddLine(set, line.c_str(), GBA_CHEAT_AUTODETECT)) {
            return false;
        }
        any = true;
    }
    return any;
}

}  // namespace

bool GbaSession::cheatsOk(std::string_view code) {
    std::lock_guard lock(frameMutex_);
    if (!core_) {
        return false;
    }
    mCheatDevice* device = core_->cheatDevice(core_);
    if (!device) {
        return false;
    }
    mCheatSet* set = device->createSet(device, "trial");
    if (!set) {
        return false;
    }
    const bool ok = addGbaLines(set, code);
    mCheatSetDeinit(set);
    return ok;
}

void GbaSession::installCheats(std::span<const CheatSpec> cheats) {
    std::lock_guard lock(frameMutex_);
    if (!core_) {
        return;
    }
    mCheatDevice* device = core_->cheatDevice(core_);
    if (!device) {
        return;
    }
    mCheatDeviceClear(device);
    for (const CheatSpec& spec : cheats) {
        mCheatSet* set = device->createSet(device, spec.name.c_str());
        if (!set) {
            continue;
        }
        if (!addGbaLines(set, spec.code)) {
            mCheatSetDeinit(set);
            continue;
        }
        set->enabled = true;
        mCheatAddSet(device, set);
    }
}

}

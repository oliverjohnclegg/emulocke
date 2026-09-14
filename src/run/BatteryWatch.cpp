#include "run/BatteryWatch.hpp"

#include "adapter/GameAdapter.hpp"
#include "emu/FileBytes.hpp"

namespace emulocke {

bool BatteryWatch::refresh(const std::filesystem::path& path, const GameAdapter& adapter) {
    std::error_code ec;
    const auto mtime = std::filesystem::last_write_time(path, ec);
    const auto bytes = ec ? 0 : std::filesystem::file_size(path, ec);
    if (ec) {
        path_.clear();
        snapshot_ = GameSnapshot{};
        return false;
    }
    if (path == path_ && mtime == mtime_ && bytes == bytes_) {
        return false;
    }
    path_ = path;
    mtime_ = mtime;
    bytes_ = bytes;
    const auto sav = readWholeFile(path.string(), kMaxSaveFile);
    snapshot_ = sav.empty() ? GameSnapshot{} : adapter.readSave(sav);
    return true;
}

void BatteryWatch::mergeInto(GameSnapshot& live) const {
    if (!snapshot_.ok) {
        return;
    }
    if (!live.ok || live.party.count == 0) {
        live = snapshot_;
        return;
    }
    if (live.gyms.slots == 0 && snapshot_.gyms.slots != 0) {
        live.gyms = snapshot_.gyms;
        live.progress.badges = snapshot_.progress.badges;
        live.progress.flags = snapshot_.progress.flags;
    }
}

}

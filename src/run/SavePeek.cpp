#include "run/SavePeek.hpp"

#include "adapter/GameAdapter.hpp"
#include "emu/FileBytes.hpp"
#include "run/RunStore.hpp"

#include <filesystem>

namespace emulocke {

const GameSnapshot& SavePeek::get(const RunStore& store, const Run& run) {
    const auto path = store.batteryPath(run.id);
    std::error_code ec;
    if (!std::filesystem::is_regular_file(path, ec)) {
        return empty_;
    }
    const auto mtime = std::filesystem::last_write_time(path, ec);
    auto it = cache_.find(run.id);
    if (it != cache_.end() && it->second.mtime == mtime) {
        return it->second.snap;
    }
    const auto bytes = readWholeFile(path.string(), kMaxSaveFile);
    const GameAdapter* adapter = bytes.empty() ? nullptr : adapterForSave(bytes);
    Slot slot;
    slot.mtime = mtime;
    if (adapter) {
        slot.snap = adapter->readSave(bytes);
    }
    auto [ins, _] = cache_.insert_or_assign(run.id, std::move(slot));
    return ins->second.snap;
}

}

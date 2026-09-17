#include "emu/RamCapture.hpp"

#include "emu/FileBytes.hpp"

#include <filesystem>
#include <span>

namespace emulocke {

void RamCapture::maybeWrite(const LiveMemory& mem, bool inBattle, const std::filesystem::path& dir,
    uint64_t nowMs) {
    if (!inBattle) {
        wasBattle_ = false;
        return;
    }
    std::error_code ec;
    if (!std::filesystem::is_directory(dir, ec)) {
        return;
    }
    const bool entered = !wasBattle_;
    wasBattle_ = true;
    if (!entered && nowMs >= lastMs_ && nowMs - lastMs_ < kRamCaptureGapMs) {
        return;
    }
    lastMs_ = nowMs;
    if (buf_.size() != kNdsMainRamBytes) {
        buf_.assign(kNdsMainRamBytes, 0);
    }
    if (!mem.read(kNdsMainRam, std::span<uint8_t>{buf_})) {
        return;
    }
    if (entered) {
        writeWholeFile(dir / "send-in.bin", buf_.data(), buf_.size());
    }
    writeWholeFile(dir / "after.bin", buf_.data(), buf_.size());
}

}

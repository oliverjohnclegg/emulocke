#pragma once

#include "adapter/LiveMemory.hpp"

#include <cstdint>
#include <filesystem>
#include <vector>

namespace emulocke {

inline constexpr uint32_t kNdsMainRam = 0x02000000;
inline constexpr std::size_t kNdsMainRamBytes = 0x400000;
inline constexpr uint64_t kRamCaptureGapMs = 500;

class RamCapture {
public:
    void maybeWrite(const LiveMemory& mem, bool inBattle, const std::filesystem::path& dir,
        uint64_t nowMs);

private:
    bool wasBattle_{false};
    uint64_t lastMs_{0};
    std::vector<uint8_t> buf_{};
};

}

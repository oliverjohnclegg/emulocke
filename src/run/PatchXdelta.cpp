#include "run/PatchApply.hpp"

#include <algorithm>
#include <cstdlib>

extern "C" {
#include "xdelta3.h"
}

namespace emulocke {
namespace {

constexpr std::size_t kXdeltaFirstBuffer = std::size_t{32} << 20;

bool hasVcdiffMagic(std::span<const uint8_t> patch) {
    return patch.size() >= 4 && patch[0] == 0xD6 && patch[1] == 0xC3 && patch[2] == 0xC4;
}

void* capAlloc(void*, size_t items, usize_t size) {
    if (size == 0 || items == 0) {
        return std::malloc(1);
    }
    if (items > kMaxRomFile / static_cast<size_t>(size)) {
        return nullptr;
    }
    return std::malloc(items * static_cast<size_t>(size));
}

void capFree(void*, void* ptr) {
    std::free(ptr);
}

int decodeInto(std::span<const uint8_t> rom, std::span<const uint8_t> patch, uint8_t* out,
               usize_t avail, usize_t& wrote) {
    xd3_config config{};
    config.alloc = capAlloc;
    config.freef = capFree;
    xd3_stream stream;
    int rc = xd3_config_stream(&stream, &config);
    if (rc == 0) {
        xd3_source src{};
        src.blksize = static_cast<usize_t>(rom.size());
        src.onblk = static_cast<usize_t>(rom.size());
        src.curblk = rom.data();
        src.curblkno = 0;
        src.max_winsize = rom.size();
        rc = xd3_set_source_and_size(&stream, &src, static_cast<xoff_t>(rom.size()));
        if (rc == 0) {
            wrote = 0;
            rc = xd3_decode_stream(&stream, patch.data(), static_cast<usize_t>(patch.size()), out,
                &wrote, avail);
        }
    }
    xd3_free_stream(&stream);
    return rc;
}

}  // namespace

std::optional<std::vector<uint8_t>> applyXdeltaPatch(
    std::span<const uint8_t> rom, std::span<const uint8_t> patch) {
    if (rom.empty() || rom.size() > kMaxRomFile || !hasVcdiffMagic(patch)) {
        return std::nullopt;
    }
    std::size_t avail = std::max(rom.size(), kXdeltaFirstBuffer);
    while (true) {
        avail = std::min(avail, kMaxRomFile);
        std::vector<uint8_t> out(avail);
        usize_t wrote = 0;
        const int rc = decodeInto(rom, patch, out.data(), static_cast<usize_t>(avail), wrote);
        if (rc == 0) {
            out.resize(wrote);
            return out;
        }
        if (rc != ENOSPC || avail == kMaxRomFile) {
            return std::nullopt;
        }
        avail *= 2;
    }
}

}

#include "run/PatchApply.hpp"

#include <mgba-util/crc32.h>
#include <cstring>

namespace emulocke {
namespace {

bool readVli(std::span<const uint8_t> patch, size_t& i, uint64_t& value) {
    uint64_t shift = 1;
    value = 0;
    while (i < patch.size()) {
        const uint8_t x = patch[i++];
        value += (x & 0x7f) * shift;
        if (x & 0x80) {
            return true;
        }
        shift <<= 7;
        value += shift;
    }
    return false;
}

uint32_t le32(std::span<const uint8_t> p, size_t at) {
    return static_cast<uint32_t>(p[at]) | (static_cast<uint32_t>(p[at + 1]) << 8) |
           (static_cast<uint32_t>(p[at + 2]) << 16) | (static_cast<uint32_t>(p[at + 3]) << 24);
}

}  // namespace

std::optional<std::vector<uint8_t>> applyBpsPatch(
    std::span<const uint8_t> rom, std::span<const uint8_t> patch) {
    if (patch.size() < 16 || patch[0] != 'B' || patch[1] != 'P' || patch[2] != 'S' || patch[3] != '1') {
        return std::nullopt;
    }
    if (doCrc32(patch.data(), patch.size() - 4) != le32(patch, patch.size() - 4)) {
        return std::nullopt;
    }
    if (doCrc32(rom.data(), rom.size()) != le32(patch, patch.size() - 12)) {
        return std::nullopt;
    }
    size_t i = 4;
    uint64_t sourceSize = 0;
    uint64_t targetSize = 0;
    uint64_t meta = 0;
    if (!readVli(patch, i, sourceSize) || sourceSize != rom.size() || !readVli(patch, i, targetSize) ||
        !readVli(patch, i, meta) || i + meta + 12 > patch.size()) {
        return std::nullopt;
    }
    i += static_cast<size_t>(meta);
    std::vector<uint8_t> out(static_cast<size_t>(targetSize));
    size_t write = 0;
    size_t srcRel = 0;
    size_t dstRel = 0;
    const size_t commandsEnd = patch.size() - 12;
    while (i < commandsEnd) {
        uint64_t command = 0;
        if (!readVli(patch, i, command)) {
            return std::nullopt;
        }
        const size_t length = static_cast<size_t>((command >> 2) + 1);
        if (write + length > out.size()) {
            return std::nullopt;
        }
        switch (command & 3) {
        case 0:
            if (write + length > rom.size()) {
                return std::nullopt;
            }
            std::memcpy(out.data() + write, rom.data() + write, length);
            write += length;
            break;
        case 1:
            if (i + length > commandsEnd) {
                return std::nullopt;
            }
            std::memcpy(out.data() + write, patch.data() + i, length);
            i += length;
            write += length;
            break;
        case 2: {
            uint64_t offset = 0;
            if (!readVli(patch, i, offset) || ((offset & 1) && (offset >> 1) > srcRel)) {
                return std::nullopt;
            }
            srcRel = (offset & 1) ? srcRel - static_cast<size_t>(offset >> 1)
                                   : srcRel + static_cast<size_t>(offset >> 1);
            if (srcRel + length > rom.size()) {
                return std::nullopt;
            }
            std::memcpy(out.data() + write, rom.data() + srcRel, length);
            srcRel += length;
            write += length;
            break;
        }
        default: {
            uint64_t offset = 0;
            if (!readVli(patch, i, offset) || ((offset & 1) && (offset >> 1) > dstRel)) {
                return std::nullopt;
            }
            dstRel = (offset & 1) ? dstRel - static_cast<size_t>(offset >> 1)
                                   : dstRel + static_cast<size_t>(offset >> 1);
            if (dstRel + length > out.size()) {
                return std::nullopt;
            }
            for (size_t n = 0; n < length; ++n) {
                out[write++] = out[dstRel++];
            }
            break;
        }
        }
    }
    if (write != out.size() || doCrc32(out.data(), out.size()) != le32(patch, patch.size() - 8)) {
        return std::nullopt;
    }
    return out;
}

}

#include "run/BpsCommands.hpp"

#include <cstring>

namespace emulocke {
namespace {

bool moveRelative(BpsReader& reader, std::size_t& rel, std::size_t limit) {
    uint64_t offset = 0;
    if (!reader.readVli(offset)) {
        return false;
    }
    const uint64_t delta = offset >> 1;
    if (offset & 1) {
        if (delta > rel) {
            return false;
        }
        rel -= static_cast<std::size_t>(delta);
        return true;
    }
    if (delta > limit - rel) {
        return false;
    }
    rel += static_cast<std::size_t>(delta);
    return true;
}

bool sourceRead(BpsState& s, std::size_t length) {
    if (s.write > s.rom.size() || length > s.rom.size() - s.write) {
        return false;
    }
    std::memcpy(s.out.data() + s.write, s.rom.data() + s.write, length);
    s.write += length;
    return true;
}

bool targetRead(BpsReader& reader, BpsState& s, std::size_t length) {
    const uint8_t* data = reader.take(length);
    if (!data) {
        return false;
    }
    std::memcpy(s.out.data() + s.write, data, length);
    s.write += length;
    return true;
}

bool sourceCopy(BpsReader& reader, BpsState& s, std::size_t length) {
    if (!moveRelative(reader, s.srcRel, s.rom.size()) || length > s.rom.size() - s.srcRel) {
        return false;
    }
    std::memcpy(s.out.data() + s.write, s.rom.data() + s.srcRel, length);
    s.srcRel += length;
    s.write += length;
    return true;
}

bool targetCopy(BpsReader& reader, BpsState& s, std::size_t length) {
    if (!moveRelative(reader, s.dstRel, s.write) || s.dstRel >= s.write) {
        return false;
    }
    for (std::size_t n = 0; n < length; ++n) {
        s.out[s.write++] = s.out[s.dstRel++];
    }
    return true;
}

}  // namespace

bool runBpsCommand(BpsReader& reader, BpsState& s) {
    uint64_t command = 0;
    if (!reader.readVli(command)) {
        return false;
    }
    const uint64_t length = (command >> 2) + 1;
    if (length > s.out.size() - s.write) {
        return false;
    }
    const auto n = static_cast<std::size_t>(length);
    switch (command & 3) {
    case 0:
        return sourceRead(s, n);
    case 1:
        return targetRead(reader, s, n);
    case 2:
        return sourceCopy(reader, s, n);
    default:
        return targetCopy(reader, s, n);
    }
}

}

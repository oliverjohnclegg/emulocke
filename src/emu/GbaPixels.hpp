#pragma once

#include <cstdint>

namespace emulocke {

inline uint32_t gbaNativeToRgba(uint32_t native) {
    return (native & 0x00FFFFFFu) | 0xFF000000u;
}

}  // namespace emulocke

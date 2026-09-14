#pragma once

#include "run/BpsReader.hpp"

#include <cstddef>
#include <cstdint>
#include <span>
#include <vector>

namespace emulocke {

struct BpsState {
    std::span<const uint8_t> rom;
    std::vector<uint8_t> out;
    std::size_t write = 0;
    std::size_t srcRel = 0;
    std::size_t dstRel = 0;
};

bool runBpsCommand(BpsReader& reader, BpsState& state);

}

#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

namespace emulocke {

using NdsMac = std::array<uint8_t, 6>;

bool ndsMacAssigned(const NdsMac& mac);
NdsMac randomNdsMac();
std::optional<NdsMac> parseNdsMac(std::string_view text);
std::string formatNdsMac(const NdsMac& mac);

}
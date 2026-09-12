#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace emulocke {

std::optional<std::vector<uint8_t>> httpGetPng(const std::string& url);

}

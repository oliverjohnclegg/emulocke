#pragma once

#include <filesystem>
#include <string_view>

namespace emulocke {

bool catalogUuidOk(std::string_view uuid);
std::filesystem::path cheatGamePath(std::string_view catalogUuid);

}

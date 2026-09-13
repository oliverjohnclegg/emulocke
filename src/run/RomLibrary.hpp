#pragma once

#include "run/Catalog.hpp"

#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace emulocke {

struct ImportResult {
    bool ok = false;
    std::string message;
    const CatalogTitle* title{};
};

class RomLibrary {
public:
    RomLibrary() = default;
    RomLibrary(std::filesystem::path romsRoot, std::filesystem::path assetsRoot);
    ImportResult importFile(const std::filesystem::path& path);
    bool writeBaseline(const CatalogTitle& title, const std::vector<uint8_t>& bytes);
    bool has(const std::string& uuid) const;
    std::filesystem::path storedPath(const CatalogTitle& title, std::string_view optionId = {}) const;
    std::optional<std::filesystem::path> ensurePlayable(
        const std::string& uuid, std::string_view optionId = {});
    const std::string& lastError() const { return error_; }
    std::vector<const CatalogTitle*> playableTitles() const;

private:
    std::filesystem::path baselinesDir() const;
    std::filesystem::path derivedDir() const;
    std::filesystem::path romsRoot_;
    std::filesystem::path assetsRoot_;
    std::string error_;
};

}

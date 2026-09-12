#include "run/RomLibrary.hpp"

#include "emu/FileBytes.hpp"
#include "run/PatchApply.hpp"

namespace emulocke {

RomLibrary::RomLibrary(std::filesystem::path romsRoot, std::filesystem::path assetsRoot)
    : romsRoot_(std::move(romsRoot)), assetsRoot_(std::move(assetsRoot)) {
    std::error_code ec;
    std::filesystem::create_directories(baselinesDir(), ec);
    std::filesystem::create_directories(derivedDir(), ec);
}

std::filesystem::path RomLibrary::baselinesDir() const {
    return romsRoot_ / "baselines";
}

std::filesystem::path RomLibrary::derivedDir() const {
    return romsRoot_ / "derived";
}

std::filesystem::path RomLibrary::storedPath(const CatalogTitle& title) const {
    const std::string name = std::string(title.uuid) + title.ext;
    if (title.kind == TitleKind::Hack) {
        return derivedDir() / name;
    }
    return baselinesDir() / name;
}

bool RomLibrary::has(const std::string& uuid) const {
    const CatalogTitle* title = catalogByUuid(uuid);
    if (!title) {
        return false;
    }
    std::error_code ec;
    return std::filesystem::is_regular_file(storedPath(*title), ec);
}

bool RomLibrary::writeBaseline(const CatalogTitle& title, const std::vector<uint8_t>& bytes) {
    if (title.kind != TitleKind::Baseline || bytes.empty()) {
        error_ = "Not a supported baseline dump.";
        return false;
    }
    std::error_code ec;
    std::filesystem::create_directories(baselinesDir(), ec);
    const auto dest = storedPath(title);
    return writeWholeFile(dest.string(), bytes.data(), static_cast<uint32_t>(bytes.size()));
}

ImportResult RomLibrary::importFile(const std::filesystem::path& path) {
    ImportResult result;
    const auto bytes = readWholeFile(path.string());
    if (bytes.empty()) {
        result.message = "Couldn't read that file.";
        error_ = result.message;
        return result;
    }
    const CatalogTitle* title = catalogBySha1(sha1Hex(bytes));
    if (!title || title->kind != TitleKind::Baseline) {
        result.message = "Not a supported baseline dump.";
        error_ = result.message;
        return result;
    }
    if (!writeBaseline(*title, bytes)) {
        result.message = "Couldn't copy that dump into the library.";
        error_ = result.message;
        return result;
    }
    result.ok = true;
    result.title = title;
    result.message = std::string("Imported ") + title->fullName + ".";
    error_.clear();
    return result;
}

}
#include "run/RomLibrary.hpp"

#include "emu/FileBytes.hpp"
#include "run/PatchApply.hpp"

namespace emulocke {

std::optional<std::filesystem::path> RomLibrary::ensurePlayable(
    const std::string& uuid, std::string_view optionId) {
    const CatalogTitle* title = catalogByUuid(uuid);
    if (!title) {
        error_ = "Unknown game.";
        return std::nullopt;
    }
    const auto dest = storedPath(*title, optionId);
    std::error_code ec;
    if (std::filesystem::is_regular_file(dest, ec)) {
        error_.clear();
        return dest;
    }
    if (title->kind == TitleKind::Baseline) {
        error_ = std::string("Import ") + title->fullName + " first.";
        return std::nullopt;
    }
    const CatalogTitle* prereq = catalogByUuid(title->prerequisiteUuid);
    if (!prereq || !has(prereq->uuid)) {
        error_ = std::string("Import ") + (prereq ? prereq->fullName : "the baseline") + " to play this game.";
        return std::nullopt;
    }
    const char* asset = catalogPatchAsset(*title, optionId);
    const auto patchPath = assetsRoot_ / (asset ? asset : "");
    const auto base = readWholeFile(storedPath(*prereq), kMaxRomFile);
    const auto patch = readWholeFile(patchPath, kMaxPatchFile);
    if (base.empty()) {
        error_ = std::string("Import ") + prereq->fullName + " to play this game.";
        return std::nullopt;
    }
    if (patch.empty()) {
        error_ = "Patch asset missing for this game.";
        return std::nullopt;
    }
    auto patched = applyRomPatch(base, patch);
    if (!patched) {
        error_ = "Couldn't apply the patch.";
        return std::nullopt;
    }
    std::filesystem::create_directories(derivedDir(), ec);
    if (!writeWholeFile(dest, patched->data(), patched->size())) {
        error_ = "Couldn't write the patched dump.";
        return std::nullopt;
    }
    error_.clear();
    return dest;
}

std::vector<const CatalogTitle*> RomLibrary::playableTitles() const {
    std::vector<const CatalogTitle*> out;
    for (const CatalogTitle& title : catalogTitles()) {
        if (title.kind == TitleKind::Hack || has(title.uuid)) {
            out.push_back(&title);
        }
    }
    return out;
}

}

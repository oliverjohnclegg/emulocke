#include "run/Catalog.hpp"

namespace emulocke {
namespace {

constexpr PatchOption kBlazeBlackOptions[] = {
    {"full", "Full", "patches/8057987b-cc3f-5e3a-92a0-84c3427376b4-full.xdelta"},
    {"clean", "Clean", "patches/8057987b-cc3f-5e3a-92a0-84c3427376b4-clean.xdelta"},
};

constexpr PatchOption kVoltWhiteOptions[] = {
    {"full", "Full", "patches/5d188885-ae0f-5759-9780-80dcee31f3e1-full.xdelta"},
    {"clean", "Clean", "patches/5d188885-ae0f-5759-9780-80dcee31f3e1-clean.xdelta"},
};

constexpr CatalogTitle kTitles[] = {
#include "run/CatalogTitles.inc"
};

}  // namespace

std::span<const CatalogTitle> catalogTitles() {
    return kTitles;
}

}

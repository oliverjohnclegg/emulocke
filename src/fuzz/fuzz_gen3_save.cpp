#include "adapter/GameAdapter.hpp"
#include "adapter/frlg/FrlgAdapter.hpp"
#include "adapter/rse/RseAdapter.hpp"
#include "fuzz/FuzzRom.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    static const emulocke::FrlgAdapter fireRed{emulocke::FrlgEdition::FireRed, 1};
    static const emulocke::RseAdapter emerald{emulocke::RseEdition::Emerald, 0};
    static const emulocke::RseAdapter ruby{emulocke::RseEdition::Ruby, 0};
    const auto sav = emulocke::fuzz::input(data, size);
    fireRed.readSave(sav);
    emerald.readSave(sav);
    ruby.readSave(sav);
    if (const emulocke::GameAdapter* detected = emulocke::adapterForSave(sav)) {
        detected->readSave(sav);
    }
    return 0;
}

#include "adapter/Snapshot.hpp"
#include "adapter/gen4/Layout.hpp"
#include "adapter/gen4/Save.hpp"
#include "fuzz/FuzzRom.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    const auto sav = emulocke::fuzz::input(data, size);
    for (const emulocke::Gen4Layout& layout : {emulocke::dpLayout(), emulocke::ptLayout(), emulocke::hgssLayout()}) {
        emulocke::GameSnapshot snap;
        emulocke::readGen4Save(sav, layout, snap);
    }
    return 0;
}

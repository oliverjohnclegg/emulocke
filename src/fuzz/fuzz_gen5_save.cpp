#include "adapter/Snapshot.hpp"
#include "adapter/gen5/Save.hpp"
#include "fuzz/FuzzRom.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    const auto sav = emulocke::fuzz::input(data, size);
    for (const bool bw2 : {false, true}) {
        emulocke::GameSnapshot snap;
        emulocke::readGen5Save(sav, snap, bw2);
    }
    return 0;
}

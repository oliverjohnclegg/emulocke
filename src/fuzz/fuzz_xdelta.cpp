#include "fuzz/FuzzRom.hpp"
#include "run/PatchApply.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    emulocke::applyXdeltaPatch(emulocke::fuzz::baseRom(), emulocke::fuzz::input(data, size));
    return 0;
}

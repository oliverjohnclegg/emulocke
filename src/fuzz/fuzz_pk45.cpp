#include "adapter/Snapshot.hpp"
#include "adapter/gen45/Pk.hpp"
#include "fuzz/FuzzRom.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    const auto raw = emulocke::fuzz::input(data, size);
    for (const bool utf16 : {false, true}) {
        emulocke::Mon mon{};
        emulocke::parsePk45(raw, utf16, mon);
    }
    return 0;
}

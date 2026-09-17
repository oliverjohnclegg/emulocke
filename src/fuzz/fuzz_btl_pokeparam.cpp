#include "adapter/Snapshot.hpp"
#include "adapter/gen5/Pokeparam.hpp"
#include "fuzz/FuzzRom.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    const auto raw = emulocke::fuzz::input(data, size);
    emulocke::BattleBattler b;
    emulocke::readBtlPokeparam(raw, 495, 22, b);
    emulocke::readBtlPokeparam(raw, 1, 0, b);
    uint16_t hp = 0;
    emulocke::readBtlHp(raw, 22, 22, hp);
    emulocke::readBtlHp(raw, 20, 20, hp, 10, 16);
    emulocke::readBtlLiveHp(raw, 495, 22, 22, hp, 11, 12);
    return 0;
}

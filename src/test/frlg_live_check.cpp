#include "adapter/GameAdapter.hpp"
#include "adapter/frlg/FrlgLayout.hpp"
#include "adapter/gen3/BoxMon.hpp"
#include "emu/GbaSession.hpp"

#include <mgba/core/log.h>
#include <array>
#include <cstdio>
#include <cstring>
#include <string>

namespace {

void quiet(struct mLogger*, int, enum mLogLevel, const char*, va_list) {}

emulocke::DecryptedMon starter() {
    emulocke::DecryptedMon mon;
    mon.personality = 0xA1B2C3D4;
    mon.otId = 0x12345678;
    mon.species = 1;
    mon.level = 5;
    mon.hp = 20;
    mon.maxHp = 20;
    mon.metGame = emulocke::kVersionFireRed;
    mon.language = 2;
    std::strcpy(mon.nickname, "BULBASAUR");
    std::strcpy(mon.otName, "RED");
    return mon;
}

}  // namespace

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr, "usage: emulocke-frlg-live-check ROM.gba\n");
        return 2;
    }
    mLogger logger{};
    logger.log = quiet;
    mLogSetDefaultLogger(&logger);

    auto session = emulocke::GbaSession::open(argv[1]);
    if (!session || !session->cartridge() || !session->liveMemory()) {
        std::fprintf(stderr, "failed to open ROM\n");
        return 1;
    }
    const emulocke::GameAdapter* adapter = emulocke::adapterFor(*session->cartridge());
    if (!adapter) {
        std::fprintf(stderr, "no adapter for %s rev %u\n", session->cartridge()->code,
                     session->cartridge()->revision);
        return 1;
    }
    const std::string id{adapter->id()};
    if (id != "firered-us-1.0" && id != "firered-us-1.1") {
        std::fprintf(stderr, "unexpected adapter %s\n", id.c_str());
        return 1;
    }
    for (int i = 0; i < 32; ++i) {
        session->runFrame();
    }
    std::array<uint8_t, emulocke::kPartyMonSize> party{};
    if (!emulocke::encryptPartyMon(starter(), party)) {
        return 1;
    }
    uint8_t count = 1;
    if (!session->write(emulocke::kFrlgParty, party) ||
        !session->write(emulocke::kFrlgPartyCount, {&count, 1})) {
        std::fprintf(stderr, "live poke failed\n");
        return 1;
    }
    const emulocke::GameSnapshot snap = adapter->readLive(*session->liveMemory());
    std::printf("id=%s ok=%d species=%u lv=%u hp=%u/%u\n", snap.adapterId.data(), snap.ok,
                snap.party.mons[0].species, snap.party.mons[0].level, snap.party.mons[0].hp,
                snap.party.mons[0].maxHp);
    if (!snap.ok || snap.party.mons[0].species != 1 || snap.party.mons[0].level != 5) {
        return 1;
    }
    std::printf("frlg live check ok\n");
    return 0;
}

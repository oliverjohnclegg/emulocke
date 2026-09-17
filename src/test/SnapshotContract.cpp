#include "test/SnapshotContract.hpp"

#include <cstdio>
#include <cstdlib>

namespace {

void need(bool cond, const char* via, const char* what) {
    if (!cond) {
        std::fprintf(stderr, "fail %s: %s\n", via, what);
        std::exit(1);
    }
}

bool nameOk(const char* s) {
    if (!s || s[0] == 0 || s[0] == ' ') {
        return false;
    }
    for (int i = 0; s[i]; ++i) {
        const unsigned char c = static_cast<unsigned char>(s[i]);
        if (c < 32 || c > 126) {
            return false;
        }
    }
    return true;
}

}  // namespace

void requireSnapshotForSuite(const emulocke::GameSnapshot& snap, const char* via) {
    need(snap.ok, via, "ok");
    need(!snap.adapterId.empty() && snap.adapterId.data()[0] != 0, via, "adapterId");
    need(nameOk(snap.trainer.name), via, "trainer.name");
    need(snap.party.count >= 1 && snap.party.count <= 6, via, "party.count");
    for (uint8_t i = 0; i < snap.party.count; ++i) {
        const emulocke::Mon& mon = snap.party.mons[i];
        need(mon.species != 0, via, "party.species");
        need(nameOk(mon.speciesName), via, "party.speciesName");
        need(mon.level >= 1 && mon.level <= 100, via, "party.level");
        need(mon.maxHp > 0 && mon.hp <= mon.maxHp, via, "party.hp");
    }
    need(snap.boxes.current < emulocke::kMaxBoxes, via, "boxes.current");
    int boxed = 0;
    for (int b = 0; b < emulocke::kMaxBoxes; ++b) {
        for (int s = 0; s < 30; ++s) {
            const emulocke::Mon& mon = snap.boxes.boxes[static_cast<std::size_t>(b)].mons[static_cast<std::size_t>(s)];
            if (mon.species == 0) {
                continue;
            }
            ++boxed;
            need(nameOk(mon.speciesName), via, "box.speciesName");
        }
    }
    need(boxed > 0, via, "boxed.mons");
    need(nameOk(snap.overworld.mapName), via, "mapName");
    need(snap.gyms.slots != 0, via, "gyms.slots");
    bool flags = false;
    for (uint8_t b : snap.progress.flags) {
        if (b != 0) {
            flags = true;
            break;
        }
    }
    need(flags, via, "flags");
}

#pragma once

#include "adapter/Snapshot.hpp"
#include "adapter/StarterLine.hpp"

#include <cstdint>
#include <cstring>
#include <span>

namespace emulocke {

inline void fillStarterSpecies(GameSnapshot& snap, std::span<const uint16_t> ids) {
    auto take = [&](const Mon& mon) {
        if (snap.progress.starterSpecies != 0 || mon.egg || mon.species == 0) {
            return;
        }
        for (uint16_t id : ids) {
            if (mon.species == id || sameStarterLine(mon.species, id)) {
                snap.progress.starterSpecies = mon.species;
                return;
            }
        }
    };
    for (uint8_t i = 0; i < snap.party.count; ++i) {
        take(snap.party.mons[i]);
    }
    for (const PcBox& box : snap.boxes.boxes) {
        for (const Mon& mon : box.mons) {
            take(mon);
        }
    }
}

inline void fillGymsFromByte(GameSnapshot& snap, uint8_t earned, uint8_t slots = 8) {
    snap.gyms.slots = slots;
    snap.gyms.earned = earned;
    snap.progress.badges = earned;
}

inline void fillFlagBank(GameSnapshot& snap, const uint8_t* flags, std::size_t nbytes) {
    const std::size_t n = nbytes < kFlagBankBytes ? nbytes : kFlagBankBytes;
    std::memcpy(snap.progress.flags.data(), flags, n);
}

inline void writeDifficultyCode(GameSnapshot& snap, uint8_t code) {
    if (code > 3) {
        snap.progress.difficulty[0] = 0;
        return;
    }
    snap.progress.difficulty[0] = static_cast<char>('0' + code);
    snap.progress.difficulty[1] = 0;
}

}

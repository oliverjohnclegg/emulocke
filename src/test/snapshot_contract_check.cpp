#include "adapter/Cartridge.hpp"
#include "adapter/GameAdapter.hpp"
#include "test/SnapshotContract.hpp"
#include "test/snapshot_fixtures.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

namespace {

struct CartCase {
    const char* code;
    uint8_t revision;
    const char* id;
    SuiteSav sav;
};

const CartCase kCarts[] = {
    {"AXVE", 0, "ruby-us-1.0", SuiteSav::Rse},
    {"AXVE", 1, "ruby-us-1.1", SuiteSav::Rse},
    {"AXVE", 2, "ruby-us", SuiteSav::Rse},
    {"AXPE", 0, "sapphire-us-1.0", SuiteSav::Rse},
    {"AXPE", 1, "sapphire-us-1.1", SuiteSav::Rse},
    {"AXPE", 2, "sapphire-us", SuiteSav::Rse},
    {"BPEE", 0, "emerald-us", SuiteSav::Rse},
    {"BPRE", 0, "firered-us-1.0", SuiteSav::Frlg},
    {"BPRE", 1, "firered-us-1.1", SuiteSav::Frlg},
    {"BPGE", 0, "leafgreen-us-1.0", SuiteSav::Frlg},
    {"BPGE", 1, "leafgreen-us-1.1", SuiteSav::Frlg},
    {"ADAE", 0, "diamond-us", SuiteSav::Dp},
    {"ADAE", 5, "diamond-us", SuiteSav::Dp},
    {"ADAE", 13, "diamond-us", SuiteSav::Dp},
    {"APAE", 0, "pearl-us", SuiteSav::Dp},
    {"APAE", 5, "pearl-us", SuiteSav::Dp},
    {"APAE", 13, "pearl-us", SuiteSav::Dp},
    {"CPUE", 0, "platinum-us", SuiteSav::Pt},
    {"CPUE", 1, "platinum-us-1.1", SuiteSav::Pt},
    {"IPKE", 0, "heartgold-us", SuiteSav::Hgss},
    {"IPGE", 0, "soulsilver-us", SuiteSav::Hgss},
    {"IRBO", 0, "black-us", SuiteSav::Gen5},
    {"IRAO", 0, "white-us", SuiteSav::Gen5},
    {"IREO", 0, "black2-us", SuiteSav::Gen5},
    {"IRDO", 0, "white2-us", SuiteSav::Gen5},
};

}  // namespace

void testSnapshotContract() {
    std::vector<uint8_t> savs[6];
    savs[static_cast<int>(SuiteSav::Frlg)] = makeSuiteSav(SuiteSav::Frlg);
    savs[static_cast<int>(SuiteSav::Rse)] = makeSuiteSav(SuiteSav::Rse);
    savs[static_cast<int>(SuiteSav::Dp)] = makeSuiteSav(SuiteSav::Dp);
    savs[static_cast<int>(SuiteSav::Pt)] = makeSuiteSav(SuiteSav::Pt);
    savs[static_cast<int>(SuiteSav::Hgss)] = makeSuiteSav(SuiteSav::Hgss);
    savs[static_cast<int>(SuiteSav::Gen5)] = makeSuiteSav(SuiteSav::Gen5);

    int n = 0;
    for (const CartCase& c : kCarts) {
        emulocke::Cartridge cart;
        std::memcpy(cart.code, c.code, 4);
        cart.revision = c.revision;
        const emulocke::GameAdapter* adapter = emulocke::adapterFor(cart);
        char via[64];
        std::snprintf(via, sizeof(via), "%s r%u %s", c.code, c.revision, c.id);
        if (!adapter) {
            std::fprintf(stderr, "fail %s: no adapter\n", via);
            std::exit(1);
        }
        if (std::string(adapter->id()) != c.id) {
            std::fprintf(stderr, "fail %s: id %s\n", via, adapter->id().data());
            std::exit(1);
        }
        const emulocke::GameSnapshot snap = adapter->readSave(savs[static_cast<int>(c.sav)]);
        requireSnapshotForSuite(snap, via);
        ++n;
    }
    std::fprintf(stderr, "snapshot contract %d carts\n", n);
}

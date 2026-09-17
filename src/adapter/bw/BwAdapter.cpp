#include "adapter/bw/BwAdapter.hpp"

#include "adapter/gen45/Names.hpp"
#include "adapter/gen5/Save.hpp"

namespace emulocke {

BwAdapter::BwAdapter(bool white) : white_(white) {}

AdapterId BwAdapter::id() const {
    return white_ ? "white-us" : "black-us";
}

bool BwAdapter::matches(const Cartridge& cart) const {
    return cartridgeCodeIs(cart, white_ ? "IRAO" : "IRBO") && cart.revision == 0;
}

GameSnapshot BwAdapter::readSave(std::span<const uint8_t> sav) const {
    GameSnapshot snap;
    snap.adapterId = id();
    snap.origin = SnapshotOrigin::Save;
    readGen5Save(sav, snap);
    return snap;
}

GameSnapshot BwAdapter::readLive(const LiveMemory& mem) const {
    GameSnapshot snap;
    snap.adapterId = id();
    snap.origin = SnapshotOrigin::Live;
    fillGen5Live(mem, white_ ? kWhitePartyLive : kBwPartyLive, snap);
    return snap;
}

SpeciesRef BwAdapter::species(uint16_t internalId) const {
    return nationalSpeciesRef(internalId);
}

Bw2Adapter::Bw2Adapter(bool white) : white_(white) {}

AdapterId Bw2Adapter::id() const {
    return white_ ? "white2-us" : "black2-us";
}

bool Bw2Adapter::matches(const Cartridge& cart) const {
    return cartridgeCodeIs(cart, white_ ? "IRDO" : "IREO") && cart.revision == 0;
}

GameSnapshot Bw2Adapter::readSave(std::span<const uint8_t> sav) const {
    GameSnapshot snap;
    snap.adapterId = id();
    snap.origin = SnapshotOrigin::Save;
    readGen5Save(sav, snap, true);
    return snap;
}

GameSnapshot Bw2Adapter::readLive(const LiveMemory& mem) const {
    GameSnapshot snap;
    snap.adapterId = id();
    snap.origin = SnapshotOrigin::Live;
    fillGen5Live(mem, white_ ? kWhite2PartyLive : kBw2PartyLive, snap, true);
    return snap;
}

SpeciesRef Bw2Adapter::species(uint16_t internalId) const {
    return nationalSpeciesRef(internalId);
}

}

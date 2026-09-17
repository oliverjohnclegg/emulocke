#include "adapter/hgss/HgssAdapter.hpp"

#include "adapter/gen45/Names.hpp"
#include "adapter/gen4/Layout.hpp"
#include "adapter/gen4/Save.hpp"

namespace emulocke {

HgssAdapter::HgssAdapter(bool soulSilver) : soulSilver_(soulSilver) {}

AdapterId HgssAdapter::id() const {
    return soulSilver_ ? "soulsilver-us" : "heartgold-us";
}

bool HgssAdapter::matches(const Cartridge& cart) const {
    return cartridgeCodeIs(cart, soulSilver_ ? "IPGE" : "IPKE") && cart.revision == 0;
}

GameSnapshot HgssAdapter::readSave(std::span<const uint8_t> sav) const {
    GameSnapshot snap;
    snap.adapterId = id();
    snap.origin = SnapshotOrigin::Save;
    readGen4Save(sav, hgssLayout(), snap);
    return snap;
}

GameSnapshot HgssAdapter::readLive(const LiveMemory& mem) const {
    GameSnapshot snap;
    snap.adapterId = id();
    snap.origin = SnapshotOrigin::Live;
    fillGen4Live(mem, soulSilver_ ? kSsPartyLive : kHgPartyLive, hgssLayout(), snap);
    return snap;
}

SpeciesRef HgssAdapter::species(uint16_t internalId) const {
    return nationalSpeciesRef(internalId);
}

}

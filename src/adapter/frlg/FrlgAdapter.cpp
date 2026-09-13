#include "adapter/frlg/FrlgAdapter.hpp"

#include "adapter/frlg/FrlgLayout.hpp"
#include "adapter/frlg/FrlgLive.hpp"
#include "adapter/frlg/FrlgNames.hpp"
#include "adapter/frlg/FrlgSave.hpp"

namespace emulocke {
namespace {

AdapterId frlgId(FrlgEdition edition, uint8_t revision) {
    if (edition == FrlgEdition::LeafGreen) {
        return revision == 0 ? "leafgreen-us-1.0" : "leafgreen-us-1.1";
    }
    return revision == 0 ? "firered-us-1.0" : "firered-us-1.1";
}

}  // namespace

FrlgAdapter::FrlgAdapter(FrlgEdition edition, uint8_t revision) : edition_(edition), revision_(revision) {}

AdapterId FrlgAdapter::id() const {
    return frlgId(edition_, revision_);
}

bool FrlgAdapter::matches(const Cartridge& cart) const {
    if (cart.revision != revision_) {
        return false;
    }
    if (edition_ == FrlgEdition::LeafGreen) {
        return cartridgeCodeIs(cart, "BPGE");
    }
    return cartridgeCodeIs(cart, "BPRE");
}

GameSnapshot FrlgAdapter::readSave(std::span<const uint8_t> sav) const {
    GameSnapshot snap;
    snap.adapterId = id();
    snap.origin = SnapshotOrigin::Save;
    FrlgSaveBlocks blocks;
    if (!readFrlgSave(sav, blocks)) {
        return snap;
    }
    fillSnapshotFromFrlg(blocks, snap);
    if (edition_ != FrlgEdition::LeafGreen && snap.party.mons[0].metGame == kVersionLeafGreen) {
        snap.adapterId = frlgId(FrlgEdition::LeafGreen, revision_);
    } else {
        snap.adapterId = id();
    }
    return snap;
}

GameSnapshot FrlgAdapter::readLive(const LiveMemory& mem) const {
    GameSnapshot snap;
    snap.adapterId = id();
    snap.origin = SnapshotOrigin::Live;
    fillSnapshotFromFrlgLive(mem, snap);
    return snap;
}

SpeciesRef FrlgAdapter::species(uint16_t internalId) const {
    return frlgSpeciesRef(internalId);
}

}
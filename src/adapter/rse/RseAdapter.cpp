#include "adapter/rse/RseAdapter.hpp"

#include "adapter/gen45/Names.hpp"
#include "adapter/rse/RseLayout.hpp"
#include "adapter/rse/RseLive.hpp"
#include "adapter/rse/RseSave.hpp"

namespace emulocke {
namespace {

AdapterId rseId(RseEdition edition, uint8_t revision) {
    if (edition == RseEdition::Emerald) {
        return "emerald-us";
    }
    if (edition == RseEdition::Sapphire) {
        if (revision == 0) {
            return "sapphire-us-1.0";
        }
        return revision == 1 ? "sapphire-us-1.1" : "sapphire-us";
    }
    if (revision == 0) {
        return "ruby-us-1.0";
    }
    return revision == 1 ? "ruby-us-1.1" : "ruby-us";
}

}  // namespace

RseAdapter::RseAdapter(RseEdition edition, uint8_t revision) : edition_(edition), revision_(revision) {}

AdapterId RseAdapter::id() const {
    return rseId(edition_, revision_);
}

bool RseAdapter::matches(const Cartridge& cart) const {
    if (cart.revision != revision_) {
        return false;
    }
    if (edition_ == RseEdition::Emerald) {
        return cartridgeCodeIs(cart, "BPEE");
    }
    if (edition_ == RseEdition::Sapphire) {
        return cartridgeCodeIs(cart, "AXPE");
    }
    return cartridgeCodeIs(cart, "AXVE");
}

GameSnapshot RseAdapter::readSave(std::span<const uint8_t> sav) const {
    GameSnapshot snap;
    snap.adapterId = id();
    snap.origin = SnapshotOrigin::Save;
    RseSaveBlocks blocks;
    if (!readRseSave(sav, blocks)) {
        return snap;
    }
    fillSnapshotFromRse(blocks, snap, edition_ == RseEdition::Emerald);
    snap.adapterId = id();
    return snap;
}

GameSnapshot RseAdapter::readLive(const LiveMemory& mem) const {
    GameSnapshot snap;
    snap.adapterId = id();
    snap.origin = SnapshotOrigin::Live;
    fillSnapshotFromRseLive(mem, snap, edition_ == RseEdition::Emerald);
    return snap;
}

SpeciesRef RseAdapter::species(uint16_t internalId) const {
    if (internalId >= 277 && internalId <= 411) {
        return nationalSpeciesRef(static_cast<uint16_t>(internalId - 25));
    }
    return nationalSpeciesRef(internalId);
}

}

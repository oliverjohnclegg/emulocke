#include "adapter/dppt/DpptAdapter.hpp"

#include "adapter/gen4/Save.hpp"

namespace emulocke {

DpptAdapter::DpptAdapter(DpptEdition edition, uint8_t revision) : edition_(edition), revision_(revision) {}

AdapterId DpptAdapter::id() const {
    if (edition_ == DpptEdition::Pearl) {
        return "pearl-us";
    }
    if (edition_ == DpptEdition::Platinum) {
        return revision_ == 1 ? "platinum-us-1.1" : "platinum-us";
    }
    return "diamond-us";
}

bool DpptAdapter::matches(const Cartridge& cart) const {
    if (edition_ == DpptEdition::Pearl) {
        return cartridgeMatches(cart, "APAE", {0, 5, 13});
    }
    if (edition_ == DpptEdition::Platinum) {
        return cartridgeCodeIs(cart, "CPUE") && cart.revision == revision_;
    }
    return cartridgeMatches(cart, "ADAE", {0, 5, 13});
}

GameSnapshot DpptAdapter::readSave(std::span<const uint8_t> sav) const {
    GameSnapshot snap;
    snap.adapterId = id();
    snap.origin = SnapshotOrigin::Save;
    readGen4Save(sav, edition_ == DpptEdition::Platinum ? ptLayout() : dpLayout(), snap);
    return snap;
}

GameSnapshot DpptAdapter::readLive(const LiveMemory& mem) const {
    GameSnapshot snap;
    snap.adapterId = id();
    snap.origin = SnapshotOrigin::Live;
    const uint32_t ptrAddr = edition_ == DpptEdition::Platinum ? kPtSavePtr : kDpSavePtr;
    const uint32_t partyOff = edition_ == DpptEdition::Platinum ? kPtPartyFromSave : kDpPartyFromSave;
    const uint32_t base = mem.read32(ptrAddr);
    if (base >= 0x02000000) {
        fillGen4Live(mem, base + partyOff, snap);
    }
    return snap;
}

}

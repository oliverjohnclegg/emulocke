#include "adapter/GameAdapter.hpp"

#include "adapter/frlg/FrlgAdapter.hpp"
#include "adapter/frlg/FrlgLayout.hpp"
#include "adapter/frlg/FrlgSave.hpp"

namespace emulocke {
namespace {

const FrlgAdapter kFireRed10{FrlgEdition::FireRed, 0};
const FrlgAdapter kFireRed11{FrlgEdition::FireRed, 1};
const FrlgAdapter kLeafGreen10{FrlgEdition::LeafGreen, 0};
const FrlgAdapter kLeafGreen11{FrlgEdition::LeafGreen, 1};
const GameAdapter* kAll[] = {&kFireRed11, &kLeafGreen11, &kFireRed10, &kLeafGreen10};

}  // namespace

const GameAdapter* adapterFor(const Cartridge& cart) {
    for (const GameAdapter* adapter : kAll) {
        if (adapter->matches(cart)) {
            return adapter;
        }
    }
    return nullptr;
}

const GameAdapter* adapterForSave(std::span<const uint8_t> sav) {
    FrlgSaveBlocks blocks;
    if (!readFrlgSave(sav, blocks)) {
        return nullptr;
    }
    GameSnapshot snap;
    fillSnapshotFromFrlg(blocks, snap);
    if (snap.party.mons[0].metGame == kVersionLeafGreen) {
        return &kLeafGreen11;
    }
    return &kFireRed11;
}

}
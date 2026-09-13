#include "adapter/GameAdapter.hpp"

#include "adapter/bw/BwAdapter.hpp"
#include "adapter/dppt/DpptAdapter.hpp"
#include "adapter/frlg/FrlgAdapter.hpp"
#include "adapter/frlg/FrlgLayout.hpp"
#include "adapter/frlg/FrlgSave.hpp"
#include "adapter/gen3/BoxMon.hpp"
#include "adapter/gen3/Codec.hpp"
#include "adapter/gen4/Layout.hpp"
#include "adapter/gen4/Save.hpp"
#include "adapter/gen5/Save.hpp"
#include "adapter/hgss/HgssAdapter.hpp"
#include "adapter/rse/RseAdapter.hpp"
#include "adapter/rse/RseLayout.hpp"
#include "adapter/rse/RseSave.hpp"

namespace emulocke {
namespace {

const RseAdapter kRuby0{RseEdition::Ruby, 0};
const RseAdapter kRuby1{RseEdition::Ruby, 1};
const RseAdapter kRuby2{RseEdition::Ruby, 2};
const RseAdapter kSapphire0{RseEdition::Sapphire, 0};
const RseAdapter kSapphire1{RseEdition::Sapphire, 1};
const RseAdapter kSapphire2{RseEdition::Sapphire, 2};
const RseAdapter kEmerald{RseEdition::Emerald, 0};
const FrlgAdapter kFireRed10{FrlgEdition::FireRed, 0};
const FrlgAdapter kFireRed11{FrlgEdition::FireRed, 1};
const FrlgAdapter kLeafGreen10{FrlgEdition::LeafGreen, 0};
const FrlgAdapter kLeafGreen11{FrlgEdition::LeafGreen, 1};
const DpptAdapter kDiamond{DpptEdition::Diamond, 0};
const DpptAdapter kPearl{DpptEdition::Pearl, 0};
const DpptAdapter kPlatinum0{DpptEdition::Platinum, 0};
const DpptAdapter kPlatinum1{DpptEdition::Platinum, 1};
const HgssAdapter kHeartGold{false};
const HgssAdapter kSoulSilver{true};
const BwAdapter kBlack{false};
const BwAdapter kWhite{true};
const Bw2Adapter kBlack2{false};
const Bw2Adapter kWhite2{true};

const GameAdapter* kAll[] = {&kRuby0,     &kRuby1,       &kRuby2,       &kSapphire0,  &kSapphire1,   &kSapphire2,
                              &kEmerald,   &kFireRed11,   &kLeafGreen11, &kFireRed10,  &kLeafGreen10, &kDiamond,
                              &kPearl,     &kPlatinum1,   &kPlatinum0,   &kHeartGold,  &kSoulSilver,  &kBlack,
                              &kWhite,     &kBlack2,      &kWhite2};

bool gen4Footer(std::span<const uint8_t> sav, std::size_t generalSize, std::size_t footerSize) {
    return activeGen4Slot(sav, Gen4Layout{Gen4Family::DiamondPearl, generalSize, 0, footerSize, 0, 0, false}) >= 0;
}

bool partyAt(const uint8_t* block1, std::size_t off) {
    DecryptedMon mon;
    return decryptPartyMon({block1 + off, kPartyMonSize}, mon);
}

const GameAdapter* adapterForRseBlocks(const uint8_t* block2, const uint8_t* block1) {
    if (load32(block2 + 0xAC) != 0) {
        return &kEmerald;
    }
    DecryptedMon mon;
    if (decryptPartyMon({block1 + kRsePartyOff, kPartyMonSize}, mon) && mon.metGame == kVersionSapphire) {
        return &kSapphire2;
    }
    return &kRuby2;
}

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
    FrlgSaveBlocks frlg;
    RseSaveBlocks rse;
    const bool frlgOk = readFrlgSave(sav, frlg);
    const bool rseOk = readRseSave(sav, rse);
    if (frlgOk || rseOk) {
        const uint8_t* b1 = frlgOk ? frlg.block1.data() : rse.block1.data();
        const uint8_t* b2 = frlgOk ? frlg.block2.data() : rse.block2.data();
        const bool frlgParty = partyAt(b1, kFrlgPartyOff);
        const bool rseParty = partyAt(b1, kRsePartyOff);
        if (rseParty && !frlgParty) {
            return adapterForRseBlocks(b2, b1);
        }
        if (frlgOk && (frlgParty || !rseParty)) {
            GameSnapshot snap;
            fillSnapshotFromFrlg(frlg, snap);
            return snap.party.mons[0].metGame == kVersionLeafGreen ? &kLeafGreen11 : &kFireRed11;
        }
        if (rseOk) {
            return adapterForRseBlocks(b2, b1);
        }
    }
    if (gen4Footer(sav, kHgssGeneral, 0x10)) {
        const int slot = activeGen4Slot(sav, hgssLayout());
        const std::size_t base = slot < 0 ? 0 : static_cast<std::size_t>(slot) * kGen4Partition;
        return sav[base + kHgssTrainer + 0x1C] == 8 ? static_cast<const GameAdapter*>(&kSoulSilver) : &kHeartGold;
    }
    if (gen4Footer(sav, kPtGeneral, 0x14)) {
        return &kPlatinum0;
    }
    if (gen4Footer(sav, kDpGeneral, 0x14)) {
        const int slot = activeGen4Slot(sav, dpLayout());
        const std::size_t base = slot < 0 ? 0 : static_cast<std::size_t>(slot) * kGen4Partition;
        return sav[base + kDpTrainer + 0x1C] == 11 ? static_cast<const GameAdapter*>(&kPearl) : &kDiamond;
    }
    if (sav.size() > kGen5Trainer + 0x1F) {
        switch (sav[kGen5Trainer + 0x1F]) {
            case kVersionWhite:
                return &kWhite;
            case kVersionBlack:
                return &kBlack;
            case kVersionWhite2:
                return &kWhite2;
            case kVersionBlack2:
                return &kBlack2;
            default:
                break;
        }
        GameSnapshot snap;
        if (readGen5Save(sav, snap)) {
            return &kBlack;
        }
    }
    return nullptr;
}

}

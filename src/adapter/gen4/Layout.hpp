#pragma once

#include "adapter/gen45/Pk.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>

namespace emulocke {

inline constexpr uint32_t kGen4Magic = 0x20060623;
inline constexpr uint32_t kGen4Partition = 0x40000;
inline constexpr std::size_t kGen4BoxCount = 18;
inline constexpr std::size_t kGen4BoxSlots = 30;
inline constexpr std::size_t kGen4BoxNameBytes = 40;
inline constexpr std::size_t kGen4PackedBox = kGen4BoxSlots * kPkStoredSize;
inline constexpr std::size_t kGen4PaddedBox = 0x1000;
inline constexpr std::size_t kGen4TrainerBytes = 0x26;
inline constexpr std::size_t kGen4PartyBytes = 6 * kPk4PartySize;
inline constexpr std::size_t kDpGeneral = 0xC100;
inline constexpr std::size_t kPtGeneral = 0xCF2C;
inline constexpr std::size_t kHgssGeneral = 0xF628;
inline constexpr std::size_t kHgssStorage = 0xF700;
inline constexpr std::size_t kDpTrainer = 0x64;
inline constexpr std::size_t kPtTrainer = 0x68;
inline constexpr std::size_t kHgssTrainer = 0x64;
inline constexpr std::size_t kDpParty = 0x98;
inline constexpr std::size_t kPtParty = 0xA0;
inline constexpr std::size_t kHgssParty = 0x98;
inline constexpr uint32_t kDpSavePtr = 0x02106FAC;
inline constexpr uint32_t kDpPartyFromSave = 0xD2AC;
inline constexpr uint32_t kPtSavePtr = 0x02101D2C;
inline constexpr uint32_t kPtPartyFromSave = 0xD094;
inline constexpr uint32_t kHgPartyLive = 0x02111880;
inline constexpr uint32_t kSsPartyLive = 0x021118A0;
inline constexpr std::size_t kGen4FlagBytes = 364;
inline constexpr std::size_t kDpEventFlag = 0xFDC;
inline constexpr std::size_t kDpMap = 0x1238;
inline constexpr std::size_t kPtEventFlag = 0xFEC;
inline constexpr std::size_t kPtMap = 0x1280;
inline constexpr std::size_t kHgssEventFlag = 0x10C4;
inline constexpr std::size_t kHgssMap = 0x1234;

enum class Gen4Family { DiamondPearl, Platinum, HeartGoldSoulSilver };

struct Gen4Layout {
    Gen4Family family{};
    std::size_t generalSize{};
    std::size_t storageStart{};
    std::size_t footerSize{};
    std::size_t trainerOff{};
    std::size_t partyOff{};
    bool paddedBoxes{};
    std::size_t eventFlagOff{};
    std::size_t mapOff{};
};

inline Gen4Layout dpLayout() {
    return {Gen4Family::DiamondPearl, kDpGeneral, kDpGeneral, 0x14, kDpTrainer, kDpParty, false, kDpEventFlag,
        kDpMap};
}

inline Gen4Layout ptLayout() {
    return {Gen4Family::Platinum, kPtGeneral, kPtGeneral, 0x14, kPtTrainer, kPtParty, false, kPtEventFlag, kPtMap};
}

inline Gen4Layout hgssLayout() {
    return {Gen4Family::HeartGoldSoulSilver, kHgssGeneral, kHgssStorage, 0x10, kHgssTrainer, kHgssParty, true,
        kHgssEventFlag, kHgssMap};
}

inline constexpr std::size_t gen4StorageBytes(bool paddedBoxes) {
    const std::size_t names = kGen4BoxCount * kGen4BoxNameBytes;
    return paddedBoxes ? kGen4BoxCount * kGen4PaddedBox + 8 + names : 4 + kGen4BoxCount * kGen4PackedBox + names;
}

inline constexpr std::size_t gen4PartitionBytes(const Gen4Layout& layout) {
    return std::max({layout.trainerOff + kGen4TrainerBytes, layout.partyOff + kGen4PartyBytes,
                     layout.storageStart + gen4StorageBytes(layout.paddedBoxes)});
}

}

#pragma once

#include <cstddef>
#include <cstdint>

namespace emulocke {

inline constexpr uint32_t kGen4Magic = 0x20060623;
inline constexpr uint32_t kGen4Partition = 0x40000;
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
inline constexpr uint32_t kPtPartyFromSave = 0xD088;
inline constexpr uint32_t kHgPartyLive = 0x02111880;
inline constexpr uint32_t kSsPartyLive = 0x021118A0;

enum class Gen4Family { DiamondPearl, Platinum, HeartGoldSoulSilver };

struct Gen4Layout {
    Gen4Family family{};
    std::size_t generalSize{};
    std::size_t storageStart{};
    std::size_t footerSize{};
    std::size_t trainerOff{};
    std::size_t partyOff{};
    bool paddedBoxes{};
};

inline Gen4Layout dpLayout() {
    return {Gen4Family::DiamondPearl, kDpGeneral, kDpGeneral, 0x14, kDpTrainer, kDpParty, false};
}

inline Gen4Layout ptLayout() {
    return {Gen4Family::Platinum, kPtGeneral, kPtGeneral, 0x14, kPtTrainer, kPtParty, false};
}

inline Gen4Layout hgssLayout() {
    return {Gen4Family::HeartGoldSoulSilver, kHgssGeneral, kHgssStorage, 0x10, kHgssTrainer, kHgssParty, true};
}

}

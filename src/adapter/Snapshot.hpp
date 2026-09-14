#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>

namespace emulocke {

using AdapterId = std::string_view;

inline constexpr std::size_t kFlagBankBytes = 288;

enum class SnapshotOrigin { None, Save, Live };

enum class MonGender : uint8_t { Male, Female, Unknown };

inline constexpr int kMaxBoxes = 24;

struct Mon {
    uint16_t species{};
    uint16_t heldItem{};
    uint32_t personality{};
    uint32_t otId{};
    uint8_t level{};
    uint16_t hp{};
    uint16_t maxHp{};
    uint16_t attack{};
    uint16_t defense{};
    uint16_t speed{};
    uint16_t spAttack{};
    uint16_t spDefense{};
    uint8_t ivHp{};
    uint8_t ivAtk{};
    uint8_t ivDef{};
    uint8_t ivSpe{};
    uint8_t ivSpa{};
    uint8_t ivSpd{};
    uint8_t evHp{};
    uint8_t evAtk{};
    uint8_t evDef{};
    uint8_t evSpe{};
    uint8_t evSpa{};
    uint8_t evSpd{};
    uint8_t nature{};
    uint8_t abilityNum{};
    uint32_t experience{};
    MonGender gender{MonGender::Unknown};
    bool shiny{};
    bool egg{};
    uint32_t status{};
    uint16_t moves[4]{};
    uint8_t pp[4]{};
    uint16_t metLocation{};
    uint8_t metLevel{};
    uint8_t metGame{};
    uint8_t ball{};
    char speciesName[16]{};
    char nickname[16]{};
    char otName[12]{};
};

struct Trainer {
    char name[12]{};
    uint8_t gender{};
    uint32_t trainerId{};
    uint16_t playHours{};
    uint8_t playMinutes{};
    uint8_t playSeconds{};
};

struct Overworld {
    uint8_t mapGroup{};
    uint8_t mapNum{};
    char mapName[32]{};
};

struct Party {
    uint8_t count{};
    std::array<Mon, 6> mons{};
};

struct PcBox {
    char name[16]{};
    std::array<Mon, 30> mons{};
};

struct Boxes {
    uint8_t current{};
    std::array<PcBox, kMaxBoxes> boxes{};
};

struct Gyms {
    uint8_t earned{};
    uint8_t slots{};
};

struct Progress {
    uint16_t starterSpecies{};
    uint8_t badges{};
    char difficulty[16]{};
    std::array<uint8_t, kFlagBankBytes> flags{};
};

inline bool progressFlag(const Progress& progress, uint16_t id) {
    const std::size_t byte = static_cast<std::size_t>(id) / 8;
    if (byte >= kFlagBankBytes) {
        return false;
    }
    return (progress.flags[byte] & static_cast<uint8_t>(1u << (id % 8))) != 0;
}

struct GameSnapshot {
    bool ok{};
    AdapterId adapterId{};
    SnapshotOrigin origin{SnapshotOrigin::None};
    Trainer trainer{};
    Party party{};
    Boxes boxes{};
    Overworld overworld{};
    Progress progress{};
    Gyms gyms{};
};

}

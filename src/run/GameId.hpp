#pragma once

#include <optional>
#include <string_view>

namespace emulocke {

enum class GameId {
    Ruby,
    Sapphire,
    Emerald,
    FireRed,
    LeafGreen,
    Diamond,
    Pearl,
    Platinum,
    HeartGold,
    SoulSilver,
    Black,
    White,
    Black2,
    White2
};

inline constexpr int kGameCount = 14;

inline GameId gameIdAt(int index) {
    return static_cast<GameId>(index);
}

const char* gameTitle(GameId id);
const char* gameFullName(GameId id);
const char* gameKey(GameId id);
std::optional<GameId> gameIdFromKey(std::string_view key);
std::optional<GameId> gameIdFromCode(std::string_view code);

}

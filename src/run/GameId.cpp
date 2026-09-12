#include "run/GameId.hpp"

#include <array>

namespace emulocke {
namespace {

struct GameInfo {
    GameId id;
    const char* key;
    const char* title;
    const char* fullName;
    const char* codePrefix;
};

constexpr std::array<GameInfo, kGameCount> kGames{{
    {GameId::Ruby, "Ruby", "RUBY", "Pokemon Ruby", "AXV"},
    {GameId::Sapphire, "Sapphire", "SAPPHIRE", "Pokemon Sapphire", "AXP"},
    {GameId::Emerald, "Emerald", "EMERALD", "Pokemon Emerald", "BPE"},
    {GameId::FireRed, "FireRed", "FIRE RED", "Pokemon Fire Red", "BPR"},
    {GameId::LeafGreen, "LeafGreen", "LEAF GREEN", "Pokemon Leaf Green", "BPG"},
    {GameId::Diamond, "Diamond", "DIAMOND", "Pokemon Diamond", "ADA"},
    {GameId::Pearl, "Pearl", "PEARL", "Pokemon Pearl", "APA"},
    {GameId::Platinum, "Platinum", "PLATINUM", "Pokemon Platinum", "CPU"},
    {GameId::HeartGold, "HeartGold", "HEART GOLD", "Pokemon Heart Gold", "IPK"},
    {GameId::SoulSilver, "SoulSilver", "SOUL SILVER", "Pokemon Soul Silver", "IPG"},
    {GameId::Black, "Black", "BLACK", "Pokemon Black", "IRA"},
    {GameId::White, "White", "WHITE", "Pokemon White", "IRB"},
    {GameId::Black2, "Black2", "BLACK 2", "Pokemon Black 2", "IRE"},
    {GameId::White2, "White2", "WHITE 2", "Pokemon White 2", "IRD"},
}};

const GameInfo* find(GameId id) {
    const int i = static_cast<int>(id);
    if (i < 0 || i >= kGameCount) {
        return nullptr;
    }
    return &kGames[static_cast<size_t>(i)];
}

}  // namespace

const char* gameTitle(GameId id) {
    const GameInfo* info = find(id);
    return info ? info->title : "";
}

const char* gameFullName(GameId id) {
    const GameInfo* info = find(id);
    return info ? info->fullName : "";
}

const char* gameKey(GameId id) {
    const GameInfo* info = find(id);
    return info ? info->key : "";
}

std::optional<GameId> gameIdFromKey(std::string_view key) {
    for (const GameInfo& info : kGames) {
        if (key == info.key) {
            return info.id;
        }
    }
    return std::nullopt;
}

std::optional<GameId> gameIdFromCode(std::string_view code) {
    if (code.size() < 3) {
        return std::nullopt;
    }
    for (const GameInfo& info : kGames) {
        if (code.substr(0, 3) == info.codePrefix) {
            return info.id;
        }
    }
    return std::nullopt;
}

}

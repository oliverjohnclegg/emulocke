#include "adapter/frlg/CfruExpanded.hpp"

#include "adapter/ProgressFill.hpp"
#include "adapter/gen3/Codec.hpp"

#include <array>
#include <cstring>

namespace emulocke {
namespace {

bool unboundSignature(uint32_t sig) {
    return sig == kUnboundSignature210 || sig == kUnboundSignature200 || sig == kUnboundSignature;
}

bool expandedFlag(const uint8_t* flags, uint16_t flag) {
    const uint16_t i = static_cast<uint16_t>(flag - 0x900);
    return (flags[i / 8] & static_cast<uint8_t>(1u << (flag % 8))) != 0;
}

bool flagsErased(const uint8_t* flags) {
    for (std::size_t i = 0; i < 0x200; ++i) {
        if (flags[i] != 0xFF) {
            return false;
        }
    }
    return true;
}

uint16_t expandedVar(const uint8_t* vars, uint16_t id) {
    return load16(vars + static_cast<std::size_t>(id - 0x5000) * 2);
}

void fillFromBanks(GameSnapshot& snap, const uint8_t* flags, const uint8_t* vars, uint32_t signature) {
    const uint16_t unbound = expandedVar(vars, kUnboundDifficultyVar);
    if (unboundSignature(signature)) {
        writeDifficultyCode(snap, static_cast<uint8_t>(unbound));
        return;
    }
    if (flagsErased(flags)) {
        return;
    }
    if (expandedFlag(flags, kRrFlagHardcore)) {
        writeDifficultyCode(snap, 2);
        return;
    }
    if (expandedFlag(flags, kRrFlagRestrict)) {
        writeDifficultyCode(snap, 3);
        return;
    }
    if (expandedFlag(flags, kRrFlagEasy)) {
        writeDifficultyCode(snap, 1);
        return;
    }
    if (unbound >= 1 && unbound <= 3) {
        writeDifficultyCode(snap, static_cast<uint8_t>(unbound));
    }
}

}  // namespace

void copyCfruParasite(const uint8_t* sector, uint16_t id, FrlgSaveBlocks& out) {
    if (id == 0) {
        std::memcpy(out.expandedFlags.data(), sector + 0xF24, 0xCC);
        out.fileSignature = load32(sector + 0xFF8);
    } else if (id == 4) {
        std::memcpy(out.expandedFlags.data() + 0xCC, sector + 0xD98, 0x134);
        std::memcpy(out.expandedVars.data(), sector + 0xECC, 0x124);
    } else if (id == 13) {
        std::memcpy(out.expandedVars.data() + 0x124, sector + 0x450, 0xDC);
    }
}

void fillCfruDifficulty(const FrlgSaveBlocks& blocks, GameSnapshot& snap) {
    fillFromBanks(snap, blocks.expandedFlags.data(), blocks.expandedVars.data(), blocks.fileSignature);
}

void fillCfruDifficultyLive(const LiveMemory& mem, GameSnapshot& snap) {
    std::array<uint8_t, 0x200> flags{};
    std::array<uint8_t, 0x200> vars{};
    if (!mem.read(kCfruExpandedFlagsAddr, flags) || !mem.read(kCfruExpandedVarsAddr, vars)) {
        return;
    }
    fillFromBanks(snap, flags.data(), vars.data(), 0);
}

}

#include "adapter/frlg/CfruExpanded.hpp"
#include "adapter/frlg/FrlgAdapter.hpp"
#include "adapter/frlg/FrlgSave.hpp"
#include "adapter/gen3/Codec.hpp"
#include "test/Check.hpp"

#include <cstring>
#include <string>
#include <vector>

namespace {

void setSectorSignature(std::vector<uint8_t>& sav, uint32_t sig) {
    for (int i = 0; i < 14; ++i) {
        emulocke::store32(sav.data() + static_cast<std::size_t>(i) * 0x1000 + 0xFF8, sig);
    }
}

void setExpandedVar(std::vector<uint8_t>& sav, uint16_t var, uint16_t value) {
    const uint16_t off = static_cast<uint16_t>((var - 0x5000) * 2);
    if (off < 0x124) {
        emulocke::store16(sav.data() + 4 * 0x1000 + 0xECC + off, value);
    } else {
        emulocke::store16(sav.data() + 13 * 0x1000 + 0x450 + (off - 0x124), value);
    }
}

void setExpandedFlag(std::vector<uint8_t>& sav, uint16_t flag) {
    const uint16_t byte = static_cast<uint16_t>((flag - 0x900) / 8);
    const uint8_t bit = static_cast<uint8_t>(1u << (flag % 8));
    if (byte < 0xCC) {
        sav[0xF24 + byte] = static_cast<uint8_t>(sav[0xF24 + byte] | bit);
    } else {
        sav[4 * 0x1000 + 0xD98 + (byte - 0xCC)] = static_cast<uint8_t>(sav[4 * 0x1000 + 0xD98 + (byte - 0xCC)] | bit);
    }
}

emulocke::GameSnapshot readSav(const std::vector<uint8_t>& sav) {
    emulocke::FrlgAdapter fr(emulocke::FrlgEdition::FireRed, 1);
    return fr.readSave(sav);
}

}  // namespace

void testFrlgDifficulty() {
    emulocke::FrlgSaveBlocks blocks;
    const std::vector<uint8_t> vanilla = emulocke::writeFrlgSave(blocks);
    REQUIRE(readSav(vanilla).progress.difficulty[0] == 0);

    std::vector<uint8_t> unbound = vanilla;
    setSectorSignature(unbound, emulocke::kUnboundSignature210);
    REQUIRE(std::string(readSav(unbound).progress.difficulty) == "0");
    setExpandedVar(unbound, emulocke::kUnboundDifficultyVar, 2);
    REQUIRE(std::string(readSav(unbound).progress.difficulty) == "2");

    std::vector<uint8_t> hardcore = vanilla;
    setExpandedFlag(hardcore, emulocke::kRrFlagHardcore);
    REQUIRE(std::string(readSav(hardcore).progress.difficulty) == "2");
    std::vector<uint8_t> restrictMode = vanilla;
    setExpandedFlag(restrictMode, emulocke::kRrFlagRestrict);
    REQUIRE(std::string(readSav(restrictMode).progress.difficulty) == "3");
    std::vector<uint8_t> easy = vanilla;
    setExpandedFlag(easy, emulocke::kRrFlagEasy);
    REQUIRE(std::string(readSav(easy).progress.difficulty) == "1");

    std::vector<uint8_t> erased = vanilla;
    std::memset(erased.data() + 0xF24, 0xFF, 0xCC);
    std::memset(erased.data() + 4 * 0x1000 + 0xD98, 0xFF, 0x134);
    REQUIRE(readSav(erased).progress.difficulty[0] == 0);

    std::vector<uint8_t> ewram(0x40000, 0);
    emulocke::store16(ewram.data() + (emulocke::kCfruExpandedVarsAddr - 0x02000000) +
                          (emulocke::kUnboundDifficultyVar - 0x5000) * 2,
                      2);
    emulocke::FrlgAdapter fr(emulocke::FrlgEdition::FireRed, 1);
    emulocke::SpanMemory mem(0x02000000, ewram);
    REQUIRE(std::string(fr.readLive(mem).progress.difficulty) == "2");
    emulocke::store16(ewram.data() + (emulocke::kCfruExpandedVarsAddr - 0x02000000) +
                          (emulocke::kUnboundDifficultyVar - 0x5000) * 2,
                      0);
    const uint16_t flagByte = static_cast<uint16_t>((emulocke::kRrFlagHardcore - 0x900) / 8);
    ewram[(emulocke::kCfruExpandedFlagsAddr - 0x02000000) + flagByte] =
        static_cast<uint8_t>(1u << (emulocke::kRrFlagHardcore % 8));
    REQUIRE(std::string(fr.readLive(mem).progress.difficulty) == "2");
}

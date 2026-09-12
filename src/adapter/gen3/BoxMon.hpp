#pragma once

#include "adapter/Snapshot.hpp"

#include <cstdint>
#include <span>

namespace emulocke {

inline constexpr std::size_t kBoxMonSize = 80;
inline constexpr std::size_t kPartyMonSize = 100;

struct DecryptedMon {
    uint32_t personality{};
    uint32_t otId{};
    uint16_t species{};
    uint16_t heldItem{};
    uint32_t experience{};
    uint16_t moves[4]{};
    uint8_t pp[4]{};
    uint8_t evHp{};
    uint8_t evAtk{};
    uint8_t evDef{};
    uint8_t evSpe{};
    uint8_t evSpa{};
    uint8_t evSpd{};
    uint8_t pokerus{};
    uint8_t metLocation{};
    uint8_t metLevel{};
    uint8_t metGame{};
    uint8_t ball{};
    uint8_t otGender{};
    uint8_t ivHp{};
    uint8_t ivAtk{};
    uint8_t ivDef{};
    uint8_t ivSpe{};
    uint8_t ivSpa{};
    uint8_t ivSpd{};
    uint8_t abilityNum{};
    bool egg{};
    uint8_t language{};
    uint32_t status{};
    uint8_t level{};
    uint16_t hp{};
    uint16_t maxHp{};
    uint16_t attack{};
    uint16_t defense{};
    uint16_t speed{};
    uint16_t spAttack{};
    uint16_t spDefense{};
    char nickname[12]{};
    char otName[8]{};
    bool checksumOk{};
};

bool decryptBoxMon(std::span<const uint8_t> raw, DecryptedMon& out);
bool encryptBoxMon(const DecryptedMon& in, std::span<uint8_t> raw);
bool decryptPartyMon(std::span<const uint8_t> raw, DecryptedMon& out);
bool encryptPartyMon(const DecryptedMon& in, std::span<uint8_t> raw);
Mon toSnapshotMon(const DecryptedMon& in);
bool isShiny(uint32_t otId, uint32_t personality);
uint8_t natureOf(uint32_t personality);

}
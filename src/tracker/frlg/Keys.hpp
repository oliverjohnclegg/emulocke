#pragma once

#include <cstdint>

namespace emulocke {

inline constexpr uint8_t kMapPallet = 0x00;
inline constexpr uint8_t kMapViridian = 0x01;
inline constexpr uint8_t kMapPewter = 0x02;
inline constexpr uint8_t kMapCerulean = 0x03;
inline constexpr uint8_t kMapLavender = 0x04;
inline constexpr uint8_t kMapVermilion = 0x05;
inline constexpr uint8_t kMapCeladon = 0x06;
inline constexpr uint8_t kMapFuchsia = 0x07;
inline constexpr uint8_t kMapCinnabar = 0x08;
inline constexpr uint8_t kMapSaffron = 0x0A;
inline constexpr uint8_t kMapRoute4Center = 0x0B;
inline constexpr uint8_t kMapRoute10Center = 0x0C;
inline constexpr uint8_t kMapRoute1 = 0x0D;
inline constexpr uint8_t kMapRoute2 = 0x0E;
inline constexpr uint8_t kMapRoute3 = 0x0F;
inline constexpr uint8_t kMapRoute4 = 0x10;
inline constexpr uint8_t kMapRoute5 = 0x11;
inline constexpr uint8_t kMapRoute6 = 0x12;
inline constexpr uint8_t kMapRoute7 = 0x13;
inline constexpr uint8_t kMapRoute8 = 0x14;
inline constexpr uint8_t kMapRoute9 = 0x15;
inline constexpr uint8_t kMapRoute10 = 0x16;
inline constexpr uint8_t kMapRoute11 = 0x17;
inline constexpr uint8_t kMapRoute12 = 0x18;
inline constexpr uint8_t kMapRoute13 = 0x19;
inline constexpr uint8_t kMapRoute14 = 0x1A;
inline constexpr uint8_t kMapRoute15 = 0x1B;
inline constexpr uint8_t kMapRoute16 = 0x1C;
inline constexpr uint8_t kMapRoute17 = 0x1D;
inline constexpr uint8_t kMapRoute18 = 0x1E;
inline constexpr uint8_t kMapRoute19 = 0x1F;
inline constexpr uint8_t kMapRoute20 = 0x20;
inline constexpr uint8_t kMapRoute21 = 0x21;
inline constexpr uint8_t kMapRoute22 = 0x22;
inline constexpr uint8_t kMapRoute23 = 0x23;
inline constexpr uint8_t kMapRoute24 = 0x24;
inline constexpr uint8_t kMapRoute25 = 0x25;
inline constexpr uint8_t kMapViridianForest = 0x26;
inline constexpr uint8_t kMapMtMoon = 0x27;
inline constexpr uint8_t kMapSsAnne = 0x28;
inline constexpr uint8_t kMapDiglettsCave = 0x2B;
inline constexpr uint8_t kMapVictoryRoad = 0x2C;
inline constexpr uint8_t kMapRocketHideout = 0x2D;
inline constexpr uint8_t kMapSilph = 0x2E;
inline constexpr uint8_t kMapMansion = 0x2F;
inline constexpr uint8_t kMapSafari = 0x30;
inline constexpr uint8_t kMapRockTunnel = 0x32;
inline constexpr uint8_t kMapSeafoam = 0x33;
inline constexpr uint8_t kMapTower = 0x34;
inline constexpr uint8_t kMapCeruleanCave = 0x35;
inline constexpr uint8_t kMapPowerPlant = 0x36;
inline constexpr uint8_t kMapOneIsland = 0x37;
inline constexpr uint8_t kMapTwoIsland = 0x38;
inline constexpr uint8_t kMapThreeIsland = 0x39;
inline constexpr uint8_t kMapFourIsland = 0x3A;
inline constexpr uint8_t kMapFiveIsland = 0x3B;
inline constexpr uint8_t kMapSevenIsland = 0x3C;
inline constexpr uint8_t kMapSixIsland = 0x3D;

inline constexpr uint16_t kFlagHideHideoutGiovanni = 0x038;
inline constexpr uint16_t kFlagHideSilphRockets = 0x053;
inline constexpr uint16_t kFlagBeatLabRival = 0x258;
inline constexpr uint16_t kTrainerFlagsStart = 0x500;
inline constexpr uint16_t kFlagRivalRoute22 = kTrainerFlagsStart + 329;
inline constexpr uint16_t kFlagRivalCerulean = kTrainerFlagsStart + 332;
inline constexpr uint16_t kFlagRivalSsAnne = kTrainerFlagsStart + 426;
inline constexpr uint16_t kFlagRivalTower = kTrainerFlagsStart + 429;
inline constexpr uint16_t kFlagRivalSilph = kTrainerFlagsStart + 432;
inline constexpr uint16_t kFlagRivalRoute22Late = kTrainerFlagsStart + 435;
inline constexpr uint8_t kRivalTrainerSpan = 3;
inline constexpr uint16_t kFlagDefeatedBrock = 0x4B0;
inline constexpr uint16_t kFlagDefeatedMisty = 0x4B1;
inline constexpr uint16_t kFlagDefeatedSurge = 0x4B2;
inline constexpr uint16_t kFlagDefeatedErika = 0x4B3;
inline constexpr uint16_t kFlagDefeatedKoga = 0x4B4;
inline constexpr uint16_t kFlagDefeatedSabrina = 0x4B5;
inline constexpr uint16_t kFlagDefeatedBlaine = 0x4B6;
inline constexpr uint16_t kFlagDefeatedGiovanni = 0x4B7;
inline constexpr uint16_t kFlagDefeatedLorelei = 0x4B8;
inline constexpr uint16_t kFlagDefeatedBruno = 0x4B9;
inline constexpr uint16_t kFlagDefeatedAgatha = 0x4BA;
inline constexpr uint16_t kFlagDefeatedLance = 0x4BB;
inline constexpr uint16_t kFlagDefeatedChamp = 0x4BC;

}
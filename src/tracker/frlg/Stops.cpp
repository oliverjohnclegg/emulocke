#include "tracker/Atlas.hpp"

#include "tracker/frlg/Keys.hpp"
#include "tracker/frlg/Teams.hpp"

namespace emulocke {
namespace {

constexpr uint8_t kPallet[] = {kMapPallet};
constexpr uint8_t kRoute1[] = {kMapRoute1};
constexpr uint8_t kViridian[] = {kMapViridian};
constexpr uint8_t kRoute22[] = {kMapRoute22};
constexpr uint8_t kRoute2[] = {kMapRoute2};
constexpr uint8_t kForest[] = {kMapViridianForest};
constexpr uint8_t kRoute3[] = {kMapRoute3};
constexpr uint8_t kRoute4[] = {kMapRoute4, kMapRoute4Center};
constexpr uint8_t kMoon[] = {kMapMtMoon};
constexpr uint8_t kCerulean[] = {kMapCerulean};
constexpr uint8_t kRoute24[] = {kMapRoute24};
constexpr uint8_t kRoute25[] = {kMapRoute25};
constexpr uint8_t kRoute5[] = {kMapRoute5};
constexpr uint8_t kRoute6[] = {kMapRoute6};
constexpr uint8_t kVermilion[] = {kMapVermilion};
constexpr uint8_t kRoute11[] = {kMapRoute11};
constexpr uint8_t kDiglett[] = {kMapDiglettsCave};
constexpr uint8_t kRoute9[] = {kMapRoute9};
constexpr uint8_t kRoute10[] = {kMapRoute10, kMapRoute10Center};
constexpr uint8_t kTunnel[] = {kMapRockTunnel};
constexpr uint8_t kTower[] = {kMapTower};
constexpr uint8_t kRoute12[] = {kMapRoute12};
constexpr uint8_t kRoute8[] = {kMapRoute8};
constexpr uint8_t kRoute7[] = {kMapRoute7};
constexpr uint8_t kCeladon[] = {kMapCeladon};
constexpr uint8_t kSaffron[] = {kMapSaffron, kMapSilph};
constexpr uint8_t kRoute16[] = {kMapRoute16};
constexpr uint8_t kRoute17[] = {kMapRoute17};
constexpr uint8_t kRoute18[] = {kMapRoute18};
constexpr uint8_t kFuchsia[] = {kMapFuchsia};
constexpr uint8_t kSafari[] = {kMapSafari};
constexpr uint8_t kRoute15[] = {kMapRoute15};
constexpr uint8_t kRoute14[] = {kMapRoute14};
constexpr uint8_t kRoute13[] = {kMapRoute13};
constexpr uint8_t kPlant[] = {kMapPowerPlant};
constexpr uint8_t kRoute19[] = {kMapRoute19};
constexpr uint8_t kRoute20[] = {kMapRoute20};
constexpr uint8_t kSeafoam[] = {kMapSeafoam};
constexpr uint8_t kCinnabar[] = {kMapCinnabar};
constexpr uint8_t kMansion[] = {kMapMansion};
constexpr uint8_t kOne[] = {kMapOneIsland};
constexpr uint8_t kTwo[] = {kMapTwoIsland};
constexpr uint8_t kThree[] = {kMapThreeIsland};
constexpr uint8_t kRoute21[] = {kMapRoute21};
constexpr uint8_t kRoute23[] = {kMapRoute23};
constexpr uint8_t kVictory[] = {kMapVictoryRoad};
constexpr uint8_t kFour[] = {kMapFourIsland};
constexpr uint8_t kFive[] = {kMapFiveIsland};
constexpr uint8_t kSix[] = {kMapSixIsland};
constexpr uint8_t kSeven[] = {kMapSevenIsland};
constexpr uint8_t kCave[] = {kMapCeruleanCave};

const TrackerStop kStops[] = {
    {"starter", TrackerStopKind::Encounter, "Starter", "", BossKind::None, CatchKind::Starter, nullptr, 0,
        nullptr, 0, 0},
    {"pallet-town", TrackerStopKind::Encounter, "Pallet Town", "", BossKind::None, CatchKind::Met, kPallet, 1,
        nullptr, 0, 0},
    {"rival-1", TrackerStopKind::Boss, "Blue", "Pallet Town", BossKind::Rival, CatchKind::None, nullptr, 0,
        kTeamR1, kCountR1, kFlagBeatLabRival},
    {"route-1", TrackerStopKind::Encounter, "Route 1", "", BossKind::None, CatchKind::Met, kRoute1, 1, nullptr,
        0, 0},
    {"viridian-city", TrackerStopKind::Encounter, "Viridian City", "", BossKind::None, CatchKind::Met,
        kViridian, 1, nullptr, 0, 0},
    {"route-22", TrackerStopKind::Encounter, "Route 22", "", BossKind::None, CatchKind::Met, kRoute22, 1,
        nullptr, 0, 0},
    {"rival-2", TrackerStopKind::Boss, "Blue", "Route 22", BossKind::Rival, CatchKind::None, nullptr, 0, kTeamR2,
        kCountR2, kFlagHideRoute22Rival},
    {"route-2", TrackerStopKind::Encounter, "Route 2", "", BossKind::None, CatchKind::Met, kRoute2, 1, nullptr,
        0, 0},
    {"viridian-forest", TrackerStopKind::Encounter, "Viridian Forest", "", BossKind::None, CatchKind::Met,
        kForest, 1, nullptr, 0, 0},
    {"brock", TrackerStopKind::Boss, "Brock", "Pewter City", BossKind::Gym, CatchKind::None, nullptr, 0,
        kTeamBrock, kCountBrock, kFlagDefeatedBrock},
    {"route-3", TrackerStopKind::Encounter, "Route 3", "", BossKind::None, CatchKind::Met, kRoute3, 1, nullptr,
        0, 0},
    {"route-4", TrackerStopKind::Encounter, "Route 4", "", BossKind::None, CatchKind::Met, kRoute4, 2, nullptr,
        0, 0},
    {"mt-moon", TrackerStopKind::Encounter, "Mt. Moon", "", BossKind::None, CatchKind::Met, kMoon, 1, nullptr,
        0, 0},
    {"cerulean-city", TrackerStopKind::Encounter, "Cerulean City", "", BossKind::None, CatchKind::Met,
        kCerulean, 1, nullptr, 0, 0},
    {"misty", TrackerStopKind::Boss, "Misty", "Cerulean City", BossKind::Gym, CatchKind::None, nullptr, 0,
        kTeamMisty, kCountMisty, kFlagDefeatedMisty},
    {"route-24", TrackerStopKind::Encounter, "Route 24", "", BossKind::None, CatchKind::Met, kRoute24, 1,
        nullptr, 0, 0},
    {"rival-3", TrackerStopKind::Boss, "Blue", "Route 24", BossKind::Rival, CatchKind::None, nullptr, 0, kTeamR3,
        kCountR3, kFlagHideCeruleanRival},
    {"route-25", TrackerStopKind::Encounter, "Route 25", "", BossKind::None, CatchKind::Met, kRoute25, 1,
        nullptr, 0, 0},
    {"route-5", TrackerStopKind::Encounter, "Route 5", "", BossKind::None, CatchKind::Met, kRoute5, 1, nullptr,
        0, 0},
    {"route-6", TrackerStopKind::Encounter, "Route 6", "", BossKind::None, CatchKind::Met, kRoute6, 1, nullptr,
        0, 0},
    {"vermilion-city", TrackerStopKind::Encounter, "Vermilion City", "", BossKind::None, CatchKind::Met,
        kVermilion, 1, nullptr, 0, 0},
    {"rival-4", TrackerStopKind::Boss, "Blue", "S.S. Anne", BossKind::Rival, CatchKind::None, nullptr, 0,
        kTeamR4, kCountR4, kFlagHideSsAnneRival},
    {"surge", TrackerStopKind::Boss, "Lt. Surge", "Vermilion City", BossKind::Gym, CatchKind::None, nullptr, 0,
        kTeamSurge, kCountSurge, kFlagDefeatedSurge},
    {"route-11", TrackerStopKind::Encounter, "Route 11", "", BossKind::None, CatchKind::Met, kRoute11, 1,
        nullptr, 0, 0},
    {"digletts-cave", TrackerStopKind::Encounter, "Diglett's Cave", "", BossKind::None, CatchKind::Met,
        kDiglett, 1, nullptr, 0, 0},
    {"route-9", TrackerStopKind::Encounter, "Route 9", "", BossKind::None, CatchKind::Met, kRoute9, 1, nullptr,
        0, 0},
    {"route-10", TrackerStopKind::Encounter, "Route 10", "", BossKind::None, CatchKind::Met, kRoute10, 2,
        nullptr, 0, 0},
    {"rock-tunnel", TrackerStopKind::Encounter, "Rock Tunnel", "", BossKind::None, CatchKind::Met, kTunnel,
        1, nullptr, 0, 0},
    {"pokemon-tower", TrackerStopKind::Encounter, "Pokemon Tower", "", BossKind::None, CatchKind::Met, kTower,
        1, nullptr, 0, 0},
    {"route-12", TrackerStopKind::Encounter, "Route 12", "", BossKind::None, CatchKind::Met, kRoute12, 1,
        nullptr, 0, 0},
    {"route-8", TrackerStopKind::Encounter, "Route 8", "", BossKind::None, CatchKind::Met, kRoute8, 1, nullptr,
        0, 0},
    {"route-7", TrackerStopKind::Encounter, "Route 7", "", BossKind::None, CatchKind::Met, kRoute7, 1, nullptr,
        0, 0},
    {"celadon-city", TrackerStopKind::Encounter, "Celadon City", "", BossKind::None, CatchKind::Met, kCeladon,
        1, nullptr, 0, 0},
    {"erika", TrackerStopKind::Boss, "Erika", "Celadon City", BossKind::Gym, CatchKind::None, nullptr, 0,
        kTeamErika, kCountErika, kFlagDefeatedErika},
    {"giovanni-hideout", TrackerStopKind::Boss, "Giovanni", "Rocket Hideout", BossKind::EvilTeam,
        CatchKind::None, nullptr, 0, kTeamHideout, kCountHideout, kFlagHideHideoutGiovanni},
    {"rival-5", TrackerStopKind::Boss, "Blue", "Pokemon Tower", BossKind::Rival, CatchKind::None, nullptr, 0,
        kTeamR5, kCountR5, kFlagHideTowerRival},
    {"saffron-city", TrackerStopKind::Encounter, "Saffron City", "", BossKind::None, CatchKind::Met, kSaffron,
        2, nullptr, 0, 0},
    {"rival-6", TrackerStopKind::Boss, "Blue", "Silph Co.", BossKind::Rival, CatchKind::None, nullptr, 0,
        kTeamR6, kCountR6, kFlagHideSilphRival},
    {"giovanni-silph", TrackerStopKind::Boss, "Giovanni", "Silph Co.", BossKind::EvilTeam, CatchKind::None,
        nullptr, 0, kTeamSilph, kCountSilph, kFlagHideSilphRockets},
    {"sabrina", TrackerStopKind::Boss, "Sabrina", "Saffron City", BossKind::Gym, CatchKind::None, nullptr, 0,
        kTeamSabrina, kCountSabrina, kFlagDefeatedSabrina},
    {"route-16", TrackerStopKind::Encounter, "Route 16", "", BossKind::None, CatchKind::Met, kRoute16, 1,
        nullptr, 0, 0},
    {"route-17", TrackerStopKind::Encounter, "Route 17", "", BossKind::None, CatchKind::Met, kRoute17, 1,
        nullptr, 0, 0},
    {"route-18", TrackerStopKind::Encounter, "Route 18", "", BossKind::None, CatchKind::Met, kRoute18, 1,
        nullptr, 0, 0},
    {"fuchsia-city", TrackerStopKind::Encounter, "Fuchsia City", "", BossKind::None, CatchKind::Met, kFuchsia,
        1, nullptr, 0, 0},
    {"koga", TrackerStopKind::Boss, "Koga", "Fuchsia City", BossKind::Gym, CatchKind::None, nullptr, 0,
        kTeamKoga, kCountKoga, kFlagDefeatedKoga},
    {"safari-zone", TrackerStopKind::Encounter, "Safari Zone", "", BossKind::None, CatchKind::Met, kSafari, 1,
        nullptr, 0, 0},
    {"route-15", TrackerStopKind::Encounter, "Route 15", "", BossKind::None, CatchKind::Met, kRoute15, 1,
        nullptr, 0, 0},
    {"route-14", TrackerStopKind::Encounter, "Route 14", "", BossKind::None, CatchKind::Met, kRoute14, 1,
        nullptr, 0, 0},
    {"route-13", TrackerStopKind::Encounter, "Route 13", "", BossKind::None, CatchKind::Met, kRoute13, 1,
        nullptr, 0, 0},
    {"power-plant", TrackerStopKind::Encounter, "Power Plant", "", BossKind::None, CatchKind::Met, kPlant, 1,
        nullptr, 0, 0},
    {"route-19", TrackerStopKind::Encounter, "Route 19", "", BossKind::None, CatchKind::Met, kRoute19, 1,
        nullptr, 0, 0},
    {"route-20", TrackerStopKind::Encounter, "Route 20", "", BossKind::None, CatchKind::Met, kRoute20, 1,
        nullptr, 0, 0},
    {"seafoam-islands", TrackerStopKind::Encounter, "Seafoam Islands", "", BossKind::None, CatchKind::Met,
        kSeafoam, 1, nullptr, 0, 0},
    {"cinnabar-island", TrackerStopKind::Encounter, "Cinnabar Island", "", BossKind::None, CatchKind::Met,
        kCinnabar, 1, nullptr, 0, 0},
    {"pokemon-mansion", TrackerStopKind::Encounter, "Pokemon Mansion", "", BossKind::None, CatchKind::Met,
        kMansion, 1, nullptr, 0, 0},
    {"blaine", TrackerStopKind::Boss, "Blaine", "Cinnabar Island", BossKind::Gym, CatchKind::None, nullptr, 0,
        kTeamBlaine, kCountBlaine, kFlagDefeatedBlaine},
    {"one-island", TrackerStopKind::Encounter, "One Island", "", BossKind::None, CatchKind::Met, kOne, 1,
        nullptr, 0, 0},
    {"two-island", TrackerStopKind::Encounter, "Two Island", "", BossKind::None, CatchKind::Met, kTwo, 1,
        nullptr, 0, 0},
    {"three-island", TrackerStopKind::Encounter, "Three Island", "", BossKind::None, CatchKind::Met, kThree,
        1, nullptr, 0, 0},
    {"route-21", TrackerStopKind::Encounter, "Route 21", "", BossKind::None, CatchKind::Met, kRoute21, 1,
        nullptr, 0, 0},
    {"giovanni-gym", TrackerStopKind::Boss, "Giovanni", "Viridian City", BossKind::Gym, CatchKind::None,
        nullptr, 0, kTeamGiovanniGym, kCountGiovanniGym, kFlagDefeatedGiovanni},
    {"route-23", TrackerStopKind::Encounter, "Route 23", "", BossKind::None, CatchKind::Met, kRoute23, 1,
        nullptr, 0, 0},
    {"victory-road", TrackerStopKind::Encounter, "Victory Road", "", BossKind::None, CatchKind::Met, kVictory,
        1, nullptr, 0, 0},
    {"rival-7", TrackerStopKind::Boss, "Blue", "Victory Road", BossKind::Rival, CatchKind::None, nullptr, 0,
        kTeamR7, kCountR7, 0},
    {"lorelei", TrackerStopKind::Boss, "Lorelei", "Indigo Plateau", BossKind::EliteFour, CatchKind::None,
        nullptr, 0, kTeamLorelei, kCountLorelei, kFlagDefeatedLorelei},
    {"bruno", TrackerStopKind::Boss, "Bruno", "Indigo Plateau", BossKind::EliteFour, CatchKind::None, nullptr,
        0, kTeamBruno, kCountBruno, kFlagDefeatedBruno},
    {"agatha", TrackerStopKind::Boss, "Agatha", "Indigo Plateau", BossKind::EliteFour, CatchKind::None,
        nullptr, 0, kTeamAgatha, kCountAgatha, kFlagDefeatedAgatha},
    {"lance", TrackerStopKind::Boss, "Lance", "Indigo Plateau", BossKind::EliteFour, CatchKind::None, nullptr, 0,
        kTeamLance, kCountLance, kFlagDefeatedLance},
    {"blue", TrackerStopKind::Boss, "Blue", "Indigo Plateau", BossKind::EliteFour, CatchKind::None, nullptr, 0,
        kTeamChamp, kCountChamp, kFlagDefeatedChamp},
    {"four-island", TrackerStopKind::Encounter, "Four Island", "", BossKind::None, CatchKind::Met, kFour, 1,
        nullptr, 0, 0},
    {"five-island", TrackerStopKind::Encounter, "Five Island", "", BossKind::None, CatchKind::Met, kFive, 1,
        nullptr, 0, 0},
    {"six-island", TrackerStopKind::Encounter, "Six Island", "", BossKind::None, CatchKind::Met, kSix, 1,
        nullptr, 0, 0},
    {"seven-island", TrackerStopKind::Encounter, "Seven Island", "", BossKind::None, CatchKind::Met, kSeven, 1,
        nullptr, 0, 0},
    {"cerulean-cave", TrackerStopKind::Encounter, "Cerulean Cave", "", BossKind::None, CatchKind::Met, kCave,
        1, nullptr, 0, 0},
};

}  // namespace

const TrackerAtlas& frlgAtlas() {
    static const TrackerAtlas atlas{"frlg", kStops};
    return atlas;
}

}
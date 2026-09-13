#include "tracker/frlg/Teams.hpp"

namespace emulocke {
namespace {

constexpr uint16_t kGrass = 1;
constexpr uint16_t kFire = 4;
constexpr uint16_t kWater = 7;

}  // namespace

const BossMon kTeamR1[] = {{"bulbasaur", kWater}, {"charmander", kGrass}, {"squirtle", kFire}};
const BossMon kTeamR2[] = {
    {"pidgey", 0}, {"bulbasaur", kWater}, {"charmander", kGrass}, {"squirtle", kFire}};
const BossMon kTeamR3[] = {{"pidgeotto", 0}, {"abra", 0}, {"rattata", 0},
    {"bulbasaur", kWater}, {"charmander", kGrass}, {"squirtle", kFire}};
const BossMon kTeamR4[] = {{"pidgeotto", 0}, {"kadabra", 0}, {"raticate", 0},
    {"ivysaur", kWater}, {"charmeleon", kGrass}, {"wartortle", kFire}};
const BossMon kTeamR5[] = {{"pidgeotto", 0}, {"exeggcute", kGrass}, {"exeggcute", kFire},
    {"gyarados", kGrass}, {"gyarados", kWater}, {"growlithe", kWater}, {"growlithe", kFire},
    {"kadabra", 0}, {"ivysaur", kWater}, {"charmeleon", kGrass}, {"wartortle", kFire}};
const BossMon kTeamR6[] = {{"pidgeot", 0}, {"exeggcute", kGrass}, {"exeggcute", kFire},
    {"gyarados", kGrass}, {"gyarados", kWater}, {"growlithe", kWater}, {"growlithe", kFire},
    {"alakazam", 0}, {"venusaur", kWater}, {"charizard", kGrass}, {"blastoise", kFire}};
const BossMon kTeamR7[] = {{"pidgeot", 0}, {"rhyhorn", 0}, {"exeggcute", kGrass}, {"exeggcute", kFire},
    {"gyarados", kGrass}, {"gyarados", kWater}, {"growlithe", kWater}, {"growlithe", kFire},
    {"alakazam", 0}, {"venusaur", kWater}, {"charizard", kGrass}, {"blastoise", kFire}};
const BossMon kTeamBrock[] = {{"geodude", 0}, {"onix", 0}};
const BossMon kTeamMisty[] = {{"staryu", 0}, {"starmie", 0}};
const BossMon kTeamSurge[] = {{"voltorb", 0}, {"pikachu", 0}, {"raichu", 0}};
const BossMon kTeamErika[] = {{"victreebel", 0}, {"tangela", 0}, {"vileplume", 0}};
const BossMon kTeamKoga[] = {{"koffing", 0}, {"koffing", 0}, {"muk", 0}, {"weezing", 0}};
const BossMon kTeamSabrina[] = {{"kadabra", 0}, {"mr-mime", 0}, {"venomoth", 0}, {"alakazam", 0}};
const BossMon kTeamBlaine[] = {{"growlithe", 0}, {"ponyta", 0}, {"rapidash", 0}, {"arcanine", 0}};
const BossMon kTeamGiovanniGym[] = {
    {"rhyhorn", 0}, {"dugtrio", 0}, {"nidoqueen", 0}, {"nidoking", 0}, {"rhyhorn", 0}};
const BossMon kTeamHideout[] = {{"onix", 0}, {"rhyhorn", 0}, {"kangaskhan", 0}};
const BossMon kTeamSilph[] = {{"nidorino", 0}, {"rhyhorn", 0}, {"kangaskhan", 0}, {"nidoqueen", 0}};
const BossMon kTeamLorelei[] = {
    {"dewgong", 0}, {"cloyster", 0}, {"slowbro", 0}, {"jynx", 0}, {"lapras", 0}};
const BossMon kTeamBruno[] = {
    {"onix", 0}, {"hitmonchan", 0}, {"hitmonlee", 0}, {"onix", 0}, {"machamp", 0}};
const BossMon kTeamAgatha[] = {
    {"gengar", 0}, {"golbat", 0}, {"haunter", 0}, {"arbok", 0}, {"gengar", 0}};
const BossMon kTeamLance[] = {
    {"gyarados", 0}, {"dragonair", 0}, {"dragonair", 0}, {"aerodactyl", 0}, {"dragonite", 0}};
const BossMon kTeamChamp[] = {{"pidgeot", 0}, {"alakazam", 0}, {"rhydon", 0}, {"exeggutor", kGrass},
    {"exeggutor", kFire}, {"gyarados", kGrass}, {"gyarados", kWater}, {"arcanine", kWater},
    {"arcanine", kFire}, {"venusaur", kWater}, {"charizard", kGrass}, {"blastoise", kFire}};

const uint8_t kCountR1 = 3;
const uint8_t kCountR2 = 4;
const uint8_t kCountR3 = 6;
const uint8_t kCountR4 = 6;
const uint8_t kCountR5 = 11;
const uint8_t kCountR6 = 11;
const uint8_t kCountR7 = 12;
const uint8_t kCountBrock = 2;
const uint8_t kCountMisty = 2;
const uint8_t kCountSurge = 3;
const uint8_t kCountErika = 3;
const uint8_t kCountKoga = 4;
const uint8_t kCountSabrina = 4;
const uint8_t kCountBlaine = 4;
const uint8_t kCountGiovanniGym = 5;
const uint8_t kCountHideout = 3;
const uint8_t kCountSilph = 4;
const uint8_t kCountLorelei = 5;
const uint8_t kCountBruno = 5;
const uint8_t kCountAgatha = 5;
const uint8_t kCountLance = 5;
const uint8_t kCountChamp = 12;

}
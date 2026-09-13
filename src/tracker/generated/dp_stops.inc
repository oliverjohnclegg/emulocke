constexpr uint16_t kMet_dp_0[] = {1};
constexpr uint16_t kMet_dp_1[] = {16};
constexpr uint16_t kMet_dp_2[] = {76};
constexpr uint16_t kMet_dp_3[] = {17};
constexpr uint16_t kMet_dp_4[] = {18};
constexpr uint16_t kMet_dp_5[] = {59};
constexpr uint16_t kMet_dp_6[] = {8};
constexpr uint16_t kMet_dp_7[] = {46};
constexpr uint16_t kMet_dp_8[] = {22};
constexpr uint16_t kMet_dp_9[] = {19};
constexpr uint16_t kMet_dp_10[] = {57};
constexpr uint16_t kMet_dp_11[] = {58};
constexpr uint16_t kMet_dp_12[] = {20};
constexpr uint16_t kMet_dp_13[] = {47};
constexpr uint16_t kMet_dp_14[] = {48};
constexpr uint16_t kMet_dp_15[] = {9};
constexpr uint16_t kMet_dp_16[] = {21};
constexpr uint16_t kMet_dp_17[] = {65};
constexpr uint16_t kMet_dp_18[] = {50};
constexpr uint16_t kMet_dp_19[] = {23};
constexpr uint16_t kMet_dp_20[] = {10};
constexpr uint16_t kMet_dp_21[] = {24};
constexpr uint16_t kMet_dp_22[] = {53};
constexpr uint16_t kMet_dp_23[] = {25};
constexpr uint16_t kMet_dp_24[] = {30};
constexpr uint16_t kMet_dp_25[] = {12};
constexpr uint16_t kMet_dp_26[] = {68};
constexpr uint16_t kMet_dp_27[] = {11};
constexpr uint16_t kMet_dp_28[] = {52};
constexpr uint16_t kMet_dp_29[] = {27};
constexpr uint16_t kMet_dp_30[] = {28};
constexpr uint16_t kMet_dp_31[] = {73};
constexpr uint16_t kMet_dp_32[] = {77};
constexpr uint16_t kMet_dp_33[] = {29};
constexpr uint16_t kMet_dp_34[] = {5};
constexpr uint16_t kMet_dp_35[] = {49};
constexpr uint16_t kMet_dp_36[] = {35};
constexpr uint16_t kMet_dp_37[] = {36};
constexpr uint16_t kMet_dp_38[] = {33};
constexpr uint16_t kMet_dp_39[] = {7};
constexpr uint16_t kMet_dp_40[] = {69};
constexpr uint16_t kMet_dp_41[] = {26};
constexpr uint16_t kMet_dp_42[] = {31};
constexpr uint16_t kMet_dp_43[] = {32};
constexpr uint16_t kMet_dp_44[] = {74};
constexpr uint16_t kMet_dp_45[] = {78};
constexpr uint16_t kMet_dp_46[] = {64};
constexpr uint16_t kMet_dp_47[] = {37};
constexpr uint16_t kMet_dp_48[] = {13};
constexpr uint16_t kMet_dp_49[] = {38};
constexpr uint16_t kMet_dp_50[] = {15};
constexpr uint16_t kStarters_dp[] = {387, 390, 393};
constexpr emulocke::TrackerStop kStops_dp[] = {
    {"starter", emulocke::TrackerStopKind::Encounter, "Starter", "", emulocke::BossKind::None, emulocke::CatchKind::Starter, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"twinleaf-town", emulocke::TrackerStopKind::Encounter, "Twinleaf Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_0, 1, nullptr, 0, 0, 0, 0},
    {"route-201", emulocke::TrackerStopKind::Encounter, "Route 201", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_1, 1, nullptr, 0, 0, 0, 0},
    {"lake-verity", emulocke::TrackerStopKind::Encounter, "Lake Verity", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_2, 1, nullptr, 0, 0, 0, 0},
    {"route-202", emulocke::TrackerStopKind::Encounter, "Route 202", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_3, 1, nullptr, 0, 0, 0, 0},
    {"route-203", emulocke::TrackerStopKind::Encounter, "Route 203", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_4, 1, nullptr, 0, 0, 0, 0},
    {"b1", emulocke::TrackerStopKind::Boss, "Barry", "Route 203", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_6, 4, 0, 0, 0},
    {"oreburgh-gate", emulocke::TrackerStopKind::Encounter, "Oreburgh Gate", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_5, 1, nullptr, 0, 0, 0, 0},
    {"oreburgh-city", emulocke::TrackerStopKind::Encounter, "Oreburgh City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_6, 1, nullptr, 0, 0, 0, 0},
    {"gym-1", emulocke::TrackerStopKind::Boss, "Roark", "Oreburgh Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_9, 3, 0, 0, 1},
    {"oreburgh-mine", emulocke::TrackerStopKind::Encounter, "Oreburgh Mine", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_7, 1, nullptr, 0, 0, 0, 0},
    {"route-207", emulocke::TrackerStopKind::Encounter, "Route 207", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_8, 1, nullptr, 0, 0, 0, 0},
    {"route-204", emulocke::TrackerStopKind::Encounter, "Route 204", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_9, 1, nullptr, 0, 0, 0, 0},
    {"ravaged-path", emulocke::TrackerStopKind::Encounter, "Ravaged Path", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_10, 1, nullptr, 0, 0, 0, 0},
    {"floaroma-meadow", emulocke::TrackerStopKind::Encounter, "Floaroma Meadow", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_11, 1, nullptr, 0, 0, 0, 0},
    {"route-205", emulocke::TrackerStopKind::Encounter, "Route 205", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_12, 1, nullptr, 0, 0, 0, 0},
    {"valley-windworks", emulocke::TrackerStopKind::Encounter, "Valley Windworks", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_13, 1, nullptr, 0, 0, 0, 0},
    {"mars1", emulocke::TrackerStopKind::Boss, "Mars", "Valley Windoworks", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_17, 2, 0, 0, 0},
    {"eterna-forest", emulocke::TrackerStopKind::Encounter, "Eterna Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_14, 1, nullptr, 0, 0, 0, 0},
    {"the-old-chateau", emulocke::TrackerStopKind::Encounter, "The Old Chateau", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"eterna-city", emulocke::TrackerStopKind::Encounter, "Eterna City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_15, 1, nullptr, 0, 0, 0, 0},
    {"gym-2", emulocke::TrackerStopKind::Boss, "Gardenia", "Eterna Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_21, 3, 0, 0, 2},
    {"jup1", emulocke::TrackerStopKind::Boss, "Jupiter", "Eterna Building", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_22, 2, 0, 0, 0},
    {"route-206", emulocke::TrackerStopKind::Encounter, "Route 206", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_16, 1, nullptr, 0, 0, 0, 0},
    {"wayward-cave", emulocke::TrackerStopKind::Encounter, "Wayward Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_17, 1, nullptr, 0, 0, 0, 0},
    {"mt-coronet", emulocke::TrackerStopKind::Encounter, "Mt. Coronet", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_18, 1, nullptr, 0, 0, 0, 0},
    {"route-208", emulocke::TrackerStopKind::Encounter, "Route 208", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_19, 1, nullptr, 0, 0, 0, 0},
    {"hearthome-city", emulocke::TrackerStopKind::Encounter, "Hearthome City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_20, 1, nullptr, 0, 0, 0, 0},
    {"b2", emulocke::TrackerStopKind::Boss, "Barry", "Hearthome City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_28, 10, 0, 0, 0},
    {"route-209", emulocke::TrackerStopKind::Encounter, "Route 209", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_21, 1, nullptr, 0, 0, 0, 0},
    {"the-lost-tower", emulocke::TrackerStopKind::Encounter, "The Lost Tower", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"solaceon-ruins", emulocke::TrackerStopKind::Encounter, "Solaceon Ruins", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_22, 1, nullptr, 0, 0, 0, 0},
    {"route-210", emulocke::TrackerStopKind::Encounter, "Route 210", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_23, 1, nullptr, 0, 0, 0, 0},
    {"route-215", emulocke::TrackerStopKind::Encounter, "Route 215", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_24, 1, nullptr, 0, 0, 0, 0},
    {"veilstone-city", emulocke::TrackerStopKind::Encounter, "Veilstone City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_25, 1, nullptr, 0, 0, 0, 0},
    {"gym-3", emulocke::TrackerStopKind::Boss, "Maylene", "Veilstone Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_35, 3, 0, 0, 3},
    {"trophy-garden", emulocke::TrackerStopKind::Encounter, "Trophy Garden", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_26, 1, nullptr, 0, 0, 0, 0},
    {"pastoria-city", emulocke::TrackerStopKind::Encounter, "Pastoria City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_27, 1, nullptr, 0, 0, 0, 0},
    {"great-marsh", emulocke::TrackerStopKind::Encounter, "Great Marsh", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_28, 1, nullptr, 0, 0, 0, 0},
    {"gym-4", emulocke::TrackerStopKind::Boss, "Crasher Wake", "Pastoria Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_39, 3, 0, 0, 4},
    {"b3", emulocke::TrackerStopKind::Boss, "Barry", "Pastoria City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_40, 10, 0, 0, 0},
    {"route-212", emulocke::TrackerStopKind::Encounter, "Route 212", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_29, 1, nullptr, 0, 0, 0, 0},
    {"route-213", emulocke::TrackerStopKind::Encounter, "Route 213", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_30, 1, nullptr, 0, 0, 0, 0},
    {"valor-lakefront", emulocke::TrackerStopKind::Encounter, "Valor Lakefront", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_31, 1, nullptr, 0, 0, 0, 0},
    {"lake-valor", emulocke::TrackerStopKind::Encounter, "Lake Valor", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_32, 1, nullptr, 0, 0, 0, 0},
    {"route-214", emulocke::TrackerStopKind::Encounter, "Route 214", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_33, 1, nullptr, 0, 0, 0, 0},
    {"ruin-maniacs-cave", emulocke::TrackerStopKind::Encounter, "Ruin Maniac's Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"ruin-maniacs-tunnel", emulocke::TrackerStopKind::Encounter, "Ruin Maniac's Tunnel", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"celestic-town", emulocke::TrackerStopKind::Encounter, "Celestic Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_34, 1, nullptr, 0, 0, 0, 0},
    {"gym-5", emulocke::TrackerStopKind::Boss, "Fantina", "Hearthome Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_49, 3, 0, 0, 5},
    {"fuego-ironworks", emulocke::TrackerStopKind::Encounter, "Fuego Ironworks", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_35, 1, nullptr, 0, 0, 0, 0},
    {"routes-219", emulocke::TrackerStopKind::Encounter, "Routes 219", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"route-220", emulocke::TrackerStopKind::Encounter, "Route 220", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_36, 1, nullptr, 0, 0, 0, 0},
    {"route-221", emulocke::TrackerStopKind::Encounter, "Route 221", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_37, 1, nullptr, 0, 0, 0, 0},
    {"route-218", emulocke::TrackerStopKind::Encounter, "Route 218", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_38, 1, nullptr, 0, 0, 0, 0},
    {"b4", emulocke::TrackerStopKind::Boss, "Barry", "Route 218", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_55, 11, 0, 0, 0},
    {"canalave-city", emulocke::TrackerStopKind::Encounter, "Canalave City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_39, 1, nullptr, 0, 0, 0, 0},
    {"iron-island", emulocke::TrackerStopKind::Encounter, "Iron Island", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_40, 1, nullptr, 0, 0, 0, 0},
    {"gym-6", emulocke::TrackerStopKind::Boss, "Byron", "Canalave Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_58, 3, 0, 0, 6},
    {"route-211", emulocke::TrackerStopKind::Encounter, "Route 211", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_41, 1, nullptr, 0, 0, 0, 0},
    {"sat1", emulocke::TrackerStopKind::Boss, "Saturn", "Valor Cavern", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_60, 3, 0, 0, 0},
    {"mars2", emulocke::TrackerStopKind::Boss, "Mars", "Lake Verity", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_61, 3, 0, 0, 0},
    {"route-216", emulocke::TrackerStopKind::Encounter, "Route 216", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_42, 1, nullptr, 0, 0, 0, 0},
    {"route-217", emulocke::TrackerStopKind::Encounter, "Route 217", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_43, 1, nullptr, 0, 0, 0, 0},
    {"acuity-lakefront", emulocke::TrackerStopKind::Encounter, "Acuity Lakefront", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_44, 1, nullptr, 0, 0, 0, 0},
    {"lake-acuity", emulocke::TrackerStopKind::Encounter, "Lake Acuity", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_45, 1, nullptr, 0, 0, 0, 0},
    {"snowpoint-temple", emulocke::TrackerStopKind::Encounter, "Snowpoint Temple", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_46, 1, nullptr, 0, 0, 0, 0},
    {"gym-7", emulocke::TrackerStopKind::Boss, "Candice", "Snowpoint Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_67, 4, 0, 0, 7},
    {"cyr1", emulocke::TrackerStopKind::Boss, "Cyrus", "Galactic HQ", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_68, 3, 0, 0, 0},
    {"sat2", emulocke::TrackerStopKind::Boss, "Saturn", "Galactic HQ", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_69, 3, 0, 0, 0},
    {"mnj", emulocke::TrackerStopKind::Boss, "Mars & Jupiter", "Spear Pillar", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_70, 6, 0, 0, 0},
    {"cyr2", emulocke::TrackerStopKind::Boss, "Cyrus", "Spear Pillar", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_71, 4, 0, 0, 0},
    {"route-222", emulocke::TrackerStopKind::Encounter, "Route 222", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_47, 1, nullptr, 0, 0, 0, 0},
    {"sunyshore-city", emulocke::TrackerStopKind::Encounter, "Sunyshore City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_48, 1, nullptr, 0, 0, 0, 0},
    {"gym-8", emulocke::TrackerStopKind::Boss, "Volkner", "Sunyshore Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_74, 4, 0, 0, 8},
    {"route-223", emulocke::TrackerStopKind::Encounter, "Route 223", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_49, 1, nullptr, 0, 0, 0, 0},
    {"victory-road", emulocke::TrackerStopKind::Encounter, "Victory Road", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"b5", emulocke::TrackerStopKind::Boss, "Barry", "Victory Road", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_77, 12, 0, 0, 0},
    {"pokemon-league", emulocke::TrackerStopKind::Encounter, "Pokémon League", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_dp_50, 1, nullptr, 0, 0, 0, 0},
    {"e1", emulocke::TrackerStopKind::Boss, "Aaron", "Elite Four", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_79, 5, 0, 0, 0},
    {"e2", emulocke::TrackerStopKind::Boss, "Bertha", "Elite Four", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_80, 5, 0, 0, 0},
    {"e3", emulocke::TrackerStopKind::Boss, "Flint", "Elite Four", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_81, 5, 0, 0, 0},
    {"e4", emulocke::TrackerStopKind::Boss, "Lucian", "Elite Four", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_82, 5, 0, 0, 0},
    {"c", emulocke::TrackerStopKind::Boss, "Cynthia", "Champion", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_dp_83, 6, 0, 0, 0}
};

constexpr uint16_t kMet_fro_0[] = {0};
constexpr uint16_t kMet_fro_1[] = {13};
constexpr uint16_t kMet_fro_2[] = {1};
constexpr uint16_t kMet_fro_3[] = {34};
constexpr uint16_t kMet_fro_4[] = {14};
constexpr uint16_t kMet_fro_5[] = {38};
constexpr uint16_t kMet_fro_6[] = {15};
constexpr uint16_t kMet_fro_7[] = {16, 11};
constexpr uint16_t kMet_fro_8[] = {39};
constexpr uint16_t kMet_fro_9[] = {3};
constexpr uint16_t kMet_fro_10[] = {36};
constexpr uint16_t kMet_fro_11[] = {37};
constexpr uint16_t kMet_fro_12[] = {17};
constexpr uint16_t kMet_fro_13[] = {18};
constexpr uint16_t kMet_fro_14[] = {23};
constexpr uint16_t kMet_fro_15[] = {43};
constexpr uint16_t kMet_fro_16[] = {21};
constexpr uint16_t kMet_fro_17[] = {22, 12};
constexpr uint16_t kMet_fro_18[] = {50};
constexpr uint16_t kMet_fro_19[] = {52};
constexpr uint16_t kMet_fro_20[] = {24};
constexpr uint16_t kMet_fro_21[] = {20};
constexpr uint16_t kMet_fro_22[] = {19};
constexpr uint16_t kMet_fro_23[] = {6};
constexpr uint16_t kMet_fro_24[] = {10};
constexpr uint16_t kMet_fro_25[] = {28};
constexpr uint16_t kMet_fro_26[] = {29};
constexpr uint16_t kMet_fro_27[] = {30};
constexpr uint16_t kMet_fro_28[] = {48};
constexpr uint16_t kMet_fro_29[] = {27};
constexpr uint16_t kMet_fro_30[] = {26};
constexpr uint16_t kMet_fro_31[] = {25};
constexpr uint16_t kMet_fro_32[] = {54};
constexpr uint16_t kMet_fro_33[] = {31};
constexpr uint16_t kMet_fro_34[] = {32};
constexpr uint16_t kMet_fro_35[] = {51};
constexpr uint16_t kMet_fro_36[] = {8};
constexpr uint16_t kMet_fro_37[] = {47};
constexpr uint16_t kMet_fro_38[] = {55};
constexpr uint16_t kMet_fro_39[] = {56};
constexpr uint16_t kMet_fro_40[] = {57};
constexpr uint16_t kMet_fro_41[] = {33};
constexpr uint16_t kMet_fro_42[] = {35};
constexpr uint16_t kMet_fro_43[] = {44};
constexpr uint16_t kMet_fro_44[] = {58};
constexpr uint16_t kMet_fro_45[] = {59};
constexpr uint16_t kMet_fro_46[] = {61};
constexpr uint16_t kMet_fro_47[] = {60};
constexpr uint16_t kMet_fro_48[] = {53};
constexpr uint16_t kStarters_fro[] = {1, 4, 7};
constexpr emulocke::TrackerStop kStops_fro[] = {
    {"starter", emulocke::TrackerStopKind::Encounter, "Starter", "", emulocke::BossKind::None, emulocke::CatchKind::Starter, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"pallet-town", emulocke::TrackerStopKind::Encounter, "Pallet Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_0, 1, nullptr, 0, 0, 0, 0},
    {"r1", emulocke::TrackerStopKind::Boss, "Blue", "Rival", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_2, 3, 0, 0, 0},
    {"route-1", emulocke::TrackerStopKind::Encounter, "Route 1", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_1, 1, nullptr, 0, 0, 0, 0},
    {"viridian-city", emulocke::TrackerStopKind::Encounter, "Viridian City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_2, 1, nullptr, 0, 0, 0, 0},
    {"route-22", emulocke::TrackerStopKind::Encounter, "Route 22", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_3, 1, nullptr, 0, 0, 0, 0},
    {"r2", emulocke::TrackerStopKind::Boss, "Blue", "Rival", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_6, 4, 0, 0, 0},
    {"route-2", emulocke::TrackerStopKind::Encounter, "Route 2", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_4, 1, nullptr, 0, 0, 0, 0},
    {"viridian-forest", emulocke::TrackerStopKind::Encounter, "Viridian Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_5, 1, nullptr, 0, 0, 0, 0},
    {"gym-1", emulocke::TrackerStopKind::Boss, "Brock", "Pewter City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_9, 2, 0, 0, 1},
    {"route-3", emulocke::TrackerStopKind::Encounter, "Route 3", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_6, 1, nullptr, 0, 0, 0, 0},
    {"route-4", emulocke::TrackerStopKind::Encounter, "Route 4", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_7, 2, nullptr, 0, 0, 0, 0},
    {"mt-moon", emulocke::TrackerStopKind::Encounter, "Mt. Moon", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_8, 1, nullptr, 0, 0, 0, 0},
    {"cerulean-city", emulocke::TrackerStopKind::Encounter, "Cerulean City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_9, 1, nullptr, 0, 0, 0, 0},
    {"gym-2", emulocke::TrackerStopKind::Boss, "Misty", "Cerulean City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_14, 2, 0, 0, 2},
    {"route-24", emulocke::TrackerStopKind::Encounter, "Route 24", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_10, 1, nullptr, 0, 0, 0, 0},
    {"r3", emulocke::TrackerStopKind::Boss, "Blue", "Rival", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_16, 6, 0, 0, 0},
    {"route-25", emulocke::TrackerStopKind::Encounter, "Route 25", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_11, 1, nullptr, 0, 0, 0, 0},
    {"route-5", emulocke::TrackerStopKind::Encounter, "Route 5", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_12, 1, nullptr, 0, 0, 0, 0},
    {"route-6", emulocke::TrackerStopKind::Encounter, "Route 6", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_13, 1, nullptr, 0, 0, 0, 0},
    {"vermillion-city", emulocke::TrackerStopKind::Encounter, "Vermillion City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"r4", emulocke::TrackerStopKind::Boss, "Blue", "S.S. Anne", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_21, 6, 0, 0, 0},
    {"gym-3", emulocke::TrackerStopKind::Boss, "Lt. Surge", "Vermillion City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_22, 3, 0, 0, 3},
    {"route-11", emulocke::TrackerStopKind::Encounter, "Route 11", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_14, 1, nullptr, 0, 0, 0, 0},
    {"digletts-cave", emulocke::TrackerStopKind::Encounter, "Diglett's Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_15, 1, nullptr, 0, 0, 0, 0},
    {"route-9", emulocke::TrackerStopKind::Encounter, "Route 9", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_16, 1, nullptr, 0, 0, 0, 0},
    {"route-10", emulocke::TrackerStopKind::Encounter, "Route 10", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_17, 2, nullptr, 0, 0, 0, 0},
    {"rock-tunnel", emulocke::TrackerStopKind::Encounter, "Rock Tunnel", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_18, 1, nullptr, 0, 0, 0, 0},
    {"pokemon-tower", emulocke::TrackerStopKind::Encounter, "Pokémon Tower", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_19, 1, nullptr, 0, 0, 0, 0},
    {"route-12", emulocke::TrackerStopKind::Encounter, "Route 12", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_20, 1, nullptr, 0, 0, 0, 0},
    {"route-8", emulocke::TrackerStopKind::Encounter, "Route 8", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_21, 1, nullptr, 0, 0, 0, 0},
    {"route-7", emulocke::TrackerStopKind::Encounter, "Route 7", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_22, 1, nullptr, 0, 0, 0, 0},
    {"celadon-city", emulocke::TrackerStopKind::Encounter, "Celadon City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_23, 1, nullptr, 0, 0, 0, 0},
    {"gym-4", emulocke::TrackerStopKind::Boss, "Erica", "Celadon City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_33, 3, 0, 0, 4},
    {"g1", emulocke::TrackerStopKind::Boss, "Giovanni", "Rocket Hideout", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_34, 3, 0, 0, 0},
    {"r5", emulocke::TrackerStopKind::Boss, "Blue", "Pokemon Tower Rival", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_35, 11, 0, 0, 0},
    {"saffron-city", emulocke::TrackerStopKind::Encounter, "Saffron City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_24, 1, nullptr, 0, 0, 0, 0},
    {"r6", emulocke::TrackerStopKind::Boss, "Blue", "Silph Co. Rival", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_37, 11, 0, 0, 0},
    {"g2", emulocke::TrackerStopKind::Boss, "Giovanni", "Silph Co.", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_38, 4, 0, 0, 0},
    {"gym-6", emulocke::TrackerStopKind::Boss, "Sabrina", "Saffron City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_39, 4, 0, 0, 6},
    {"route-16", emulocke::TrackerStopKind::Encounter, "Route 16", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_25, 1, nullptr, 0, 0, 0, 0},
    {"route-17", emulocke::TrackerStopKind::Encounter, "Route 17", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_26, 1, nullptr, 0, 0, 0, 0},
    {"route-18", emulocke::TrackerStopKind::Encounter, "Route 18", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_27, 1, nullptr, 0, 0, 0, 0},
    {"fuschia-city", emulocke::TrackerStopKind::Encounter, "Fuschia City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"gym-5", emulocke::TrackerStopKind::Boss, "Koga", "Fuschia City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_44, 4, 0, 0, 5},
    {"safari-zone", emulocke::TrackerStopKind::Encounter, "Safari Zone", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_28, 1, nullptr, 0, 0, 0, 0},
    {"route-15", emulocke::TrackerStopKind::Encounter, "Route 15", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_29, 1, nullptr, 0, 0, 0, 0},
    {"route-14", emulocke::TrackerStopKind::Encounter, "Route 14", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_30, 1, nullptr, 0, 0, 0, 0},
    {"route-13", emulocke::TrackerStopKind::Encounter, "Route 13", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_31, 1, nullptr, 0, 0, 0, 0},
    {"power-plant", emulocke::TrackerStopKind::Encounter, "Power Plant", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_32, 1, nullptr, 0, 0, 0, 0},
    {"route-19", emulocke::TrackerStopKind::Encounter, "Route 19", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_33, 1, nullptr, 0, 0, 0, 0},
    {"route-20", emulocke::TrackerStopKind::Encounter, "Route 20", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_34, 1, nullptr, 0, 0, 0, 0},
    {"seafoam-islands", emulocke::TrackerStopKind::Encounter, "Seafoam Islands", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_35, 1, nullptr, 0, 0, 0, 0},
    {"cinnabar-island", emulocke::TrackerStopKind::Encounter, "Cinnabar Island", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_36, 1, nullptr, 0, 0, 0, 0},
    {"pokemon-mansion", emulocke::TrackerStopKind::Encounter, "Pokémon Mansion", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_37, 1, nullptr, 0, 0, 0, 0},
    {"gym-7", emulocke::TrackerStopKind::Boss, "Blaine", "Cinnabar Island Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_55, 4, 0, 0, 7},
    {"one-island", emulocke::TrackerStopKind::Encounter, "One Island", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_38, 1, nullptr, 0, 0, 0, 0},
    {"two-island", emulocke::TrackerStopKind::Encounter, "Two Island", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_39, 1, nullptr, 0, 0, 0, 0},
    {"three-island", emulocke::TrackerStopKind::Encounter, "Three Island", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_40, 1, nullptr, 0, 0, 0, 0},
    {"route-21", emulocke::TrackerStopKind::Encounter, "Route 21", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_41, 1, nullptr, 0, 0, 0, 0},
    {"gym-8", emulocke::TrackerStopKind::Boss, "Giovanni", "Viridian City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_60, 5, 0, 0, 8},
    {"route-23", emulocke::TrackerStopKind::Encounter, "Route 23", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_42, 1, nullptr, 0, 0, 0, 0},
    {"victory-road", emulocke::TrackerStopKind::Encounter, "Victory Road", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_43, 1, nullptr, 0, 0, 0, 0},
    {"r7", emulocke::TrackerStopKind::Boss, "Blue", "Rival", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_63, 12, 0, 0, 0},
    {"e1", emulocke::TrackerStopKind::Boss, "Lorelei", "Indigo Plateau", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_64, 5, 0, 0, 0},
    {"e2", emulocke::TrackerStopKind::Boss, "Bruno", "Indigo Plateau", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_65, 5, 0, 0, 0},
    {"e3", emulocke::TrackerStopKind::Boss, "Agatha", "Indigo Plateau", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_66, 5, 0, 0, 0},
    {"e4", emulocke::TrackerStopKind::Boss, "Lance", "Indigo Plateau", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_67, 5, 0, 0, 0},
    {"c", emulocke::TrackerStopKind::Boss, "Blue", "Champion", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_fro_68, 12, 0, 0, 0},
    {"four-island", emulocke::TrackerStopKind::Encounter, "Four Island", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_44, 1, nullptr, 0, 0, 0, 0},
    {"five-island", emulocke::TrackerStopKind::Encounter, "Five Island", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_45, 1, nullptr, 0, 0, 0, 0},
    {"six-island", emulocke::TrackerStopKind::Encounter, "Six Island", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_46, 1, nullptr, 0, 0, 0, 0},
    {"seven-island", emulocke::TrackerStopKind::Encounter, "Seven Island", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_47, 1, nullptr, 0, 0, 0, 0},
    {"cerulean-cave", emulocke::TrackerStopKind::Encounter, "Cerulean Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_fro_48, 1, nullptr, 0, 0, 0, 0}
};

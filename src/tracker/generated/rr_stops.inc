constexpr uint16_t kMet_rr_0[] = {0};
constexpr uint16_t kMet_rr_1[] = {13};
constexpr uint16_t kMet_rr_2[] = {1};
constexpr uint16_t kMet_rr_3[] = {34};
constexpr uint16_t kMet_rr_4[] = {14};
constexpr uint16_t kMet_rr_5[] = {38};
constexpr uint16_t kMet_rr_6[] = {2};
constexpr uint16_t kMet_rr_7[] = {15};
constexpr uint16_t kMet_rr_8[] = {16, 11};
constexpr uint16_t kMet_rr_9[] = {39};
constexpr uint16_t kMet_rr_10[] = {36};
constexpr uint16_t kMet_rr_11[] = {37};
constexpr uint16_t kMet_rr_12[] = {3};
constexpr uint16_t kMet_rr_13[] = {17};
constexpr uint16_t kMet_rr_14[] = {18};
constexpr uint16_t kMet_rr_15[] = {43};
constexpr uint16_t kMet_rr_16[] = {40};
constexpr uint16_t kMet_rr_17[] = {23};
constexpr uint16_t kMet_rr_18[] = {21};
constexpr uint16_t kMet_rr_19[] = {50};
constexpr uint16_t kMet_rr_20[] = {22, 12};
constexpr uint16_t kMet_rr_21[] = {52};
constexpr uint16_t kMet_rr_22[] = {24};
constexpr uint16_t kMet_rr_23[] = {20};
constexpr uint16_t kMet_rr_24[] = {19};
constexpr uint16_t kMet_rr_25[] = {6};
constexpr uint16_t kMet_rr_26[] = {10};
constexpr uint16_t kMet_rr_27[] = {28};
constexpr uint16_t kMet_rr_28[] = {29};
constexpr uint16_t kMet_rr_29[] = {30};
constexpr uint16_t kMet_rr_30[] = {48};
constexpr uint16_t kMet_rr_31[] = {27};
constexpr uint16_t kMet_rr_32[] = {26};
constexpr uint16_t kMet_rr_33[] = {25};
constexpr uint16_t kMet_rr_34[] = {54};
constexpr uint16_t kMet_rr_35[] = {31};
constexpr uint16_t kMet_rr_36[] = {32};
constexpr uint16_t kMet_rr_37[] = {51};
constexpr uint16_t kMet_rr_38[] = {8};
constexpr uint16_t kMet_rr_39[] = {47};
constexpr uint16_t kMet_rr_40[] = {33};
constexpr uint16_t kMet_rr_41[] = {35};
constexpr uint16_t kMet_rr_42[] = {44};
constexpr uint16_t kMet_rr_43[] = {57};
constexpr uint16_t kMet_rr_44[] = {53};
constexpr uint16_t kStarters_rr[] = {1, 7, 4, 152, 155, 158, 252, 255, 258, 387, 390, 393, 495, 498, 501, 650, 653, 656, 722, 725, 728, 810, 813, 816, 909, 906, 912};
constexpr emulocke::TrackerStop kStops_rr[] = {
    {"starter", emulocke::TrackerStopKind::Encounter, "Starter", "", emulocke::BossKind::None, emulocke::CatchKind::Starter, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"pallet-town", emulocke::TrackerStopKind::Encounter, "Pallet Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_0, 1, nullptr, 0, 0, 0, 0},
    {"r1", emulocke::TrackerStopKind::Boss, "Gary", "Oak's Laboratory", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_2, 24, 600, 0, 0},
    {"route-1", emulocke::TrackerStopKind::Encounter, "Route 1", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_1, 1, nullptr, 0, 0, 0, 0},
    {"r2", emulocke::TrackerStopKind::Boss, "Gary", "Route 1", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_4, 25, 0, 0, 0},
    {"viridian-city", emulocke::TrackerStopKind::Encounter, "Viridian City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_2, 1, nullptr, 0, 0, 0, 0},
    {"route-22", emulocke::TrackerStopKind::Encounter, "Route 22", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_3, 1, nullptr, 0, 0, 0, 0},
    {"route-2", emulocke::TrackerStopKind::Encounter, "Route 2", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_4, 1, nullptr, 0, 0, 0, 0},
    {"viridian-forest", emulocke::TrackerStopKind::Encounter, "Viridian Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_5, 1, nullptr, 0, 0, 0, 0},
    {"b1", emulocke::TrackerStopKind::Boss, "Brendan", "Virdian Forest", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_9, 2, 0, 0, 0},
    {"mb1", emulocke::TrackerStopKind::Boss, "Falkner", "Pewter City Museum", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_10, 3, 0, 0, 0},
    {"gym-1", emulocke::TrackerStopKind::Boss, "Brock", "Pewter City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_11, 4, 0, 0, 1},
    {"pewter-city", emulocke::TrackerStopKind::Encounter, "Pewter City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_6, 1, nullptr, 0, 0, 0, 0},
    {"route-3", emulocke::TrackerStopKind::Encounter, "Route 3", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_7, 1, nullptr, 0, 0, 0, 0},
    {"route-4", emulocke::TrackerStopKind::Encounter, "Route 4", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_8, 2, nullptr, 0, 0, 0, 0},
    {"mt-moon", emulocke::TrackerStopKind::Encounter, "Mt. Moon", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_9, 1, nullptr, 0, 0, 0, 0},
    {"ev1", emulocke::TrackerStopKind::Boss, "Admin Archer", "Mt. Moon", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_16, 3, 0, 0, 0},
    {"route-24", emulocke::TrackerStopKind::Encounter, "Route 24", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_10, 1, nullptr, 0, 0, 0, 0},
    {"r3", emulocke::TrackerStopKind::Boss, "Gary", "Route 24", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_18, 27, 0, 0, 0},
    {"route-25", emulocke::TrackerStopKind::Encounter, "Route 25", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_11, 1, nullptr, 0, 0, 0, 0},
    {"mb2", emulocke::TrackerStopKind::Boss, "Bugsy", "Bill's House", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_20, 4, 0, 0, 0},
    {"cerulean-city", emulocke::TrackerStopKind::Encounter, "Cerulean City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_12, 1, nullptr, 0, 0, 0, 0},
    {"gym-2", emulocke::TrackerStopKind::Boss, "Misty", "Cerulean City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_22, 4, 0, 0, 2},
    {"route-5", emulocke::TrackerStopKind::Encounter, "Route 5", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_13, 1, nullptr, 0, 0, 0, 0},
    {"route-6", emulocke::TrackerStopKind::Encounter, "Route 6", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_14, 1, nullptr, 0, 0, 0, 0},
    {"vermillion-city", emulocke::TrackerStopKind::Encounter, "Vermillion City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"gym-3", emulocke::TrackerStopKind::Boss, "Lt. Surge", "Vermillion City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_26, 5, 0, 0, 3},
    {"digletts-cave", emulocke::TrackerStopKind::Encounter, "Digletts Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_15, 1, nullptr, 0, 0, 0, 0},
    {"ss-anne", emulocke::TrackerStopKind::Encounter, "S.S. Anne", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_16, 1, nullptr, 0, 0, 0, 0},
    {"b2", emulocke::TrackerStopKind::Boss, "Brendan", "S.S. Anne", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_29, 2, 0, 0, 0},
    {"route-11", emulocke::TrackerStopKind::Encounter, "Route 11", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_17, 1, nullptr, 0, 0, 0, 0},
    {"mb3", emulocke::TrackerStopKind::Boss, "Whitney", "Route 11", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_31, 5, 0, 0, 0},
    {"route-9", emulocke::TrackerStopKind::Encounter, "Route 9", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_18, 1, nullptr, 0, 0, 0, 0},
    {"rock-tunnel", emulocke::TrackerStopKind::Encounter, "Rock Tunnel", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_19, 1, nullptr, 0, 0, 0, 0},
    {"route-10", emulocke::TrackerStopKind::Encounter, "Route 10", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_20, 2, nullptr, 0, 0, 0, 0},
    {"mb4", emulocke::TrackerStopKind::Boss, "Morty", "Lavender Town", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_35, 6, 0, 0, 0},
    {"pokemon-tower", emulocke::TrackerStopKind::Encounter, "Pokémon Tower", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_21, 1, nullptr, 0, 0, 0, 0},
    {"route-12", emulocke::TrackerStopKind::Encounter, "Route 12", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_22, 1, nullptr, 0, 0, 0, 0},
    {"route-8", emulocke::TrackerStopKind::Encounter, "Route 8", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_23, 1, nullptr, 0, 0, 0, 0},
    {"route-7", emulocke::TrackerStopKind::Encounter, "Route 7", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_24, 1, nullptr, 0, 0, 0, 0},
    {"celadon-city", emulocke::TrackerStopKind::Encounter, "Celadon City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_25, 1, nullptr, 0, 0, 0, 0},
    {"gym-4", emulocke::TrackerStopKind::Boss, "Erika", "Celadon City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_41, 5, 0, 0, 4},
    {"ev2", emulocke::TrackerStopKind::Boss, "Giovanni", "Celadon City Game Corner", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_42, 6, 0, 0, 0},
    {"saffron-city", emulocke::TrackerStopKind::Encounter, "Saffron City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_26, 1, nullptr, 0, 0, 0, 0},
    {"r4", emulocke::TrackerStopKind::Boss, "Gary", "Silph Co. Rival", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_44, 97, 0, 0, 0},
    {"ev3", emulocke::TrackerStopKind::Boss, "Archer & Ariana", "Silph Co.", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_45, 4, 0, 0, 0},
    {"evg2", emulocke::TrackerStopKind::Boss, "Giovanni", "Silph Co.", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_46, 6, 0, 0, 0},
    {"mb5", emulocke::TrackerStopKind::Boss, "Chuck", "Saffron City Dojo", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_47, 6, 0, 0, 0},
    {"gym-5", emulocke::TrackerStopKind::Boss, "Sabrina", "Saffron City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_48, 6, 0, 0, 5},
    {"route-16", emulocke::TrackerStopKind::Encounter, "Route 16", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_27, 1, nullptr, 0, 0, 0, 0},
    {"route-17", emulocke::TrackerStopKind::Encounter, "Route 17", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_28, 1, nullptr, 0, 0, 0, 0},
    {"route-18", emulocke::TrackerStopKind::Encounter, "Route 18", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_29, 1, nullptr, 0, 0, 0, 0},
    {"fuschia-city", emulocke::TrackerStopKind::Encounter, "Fuschia City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"b3", emulocke::TrackerStopKind::Boss, "Brendan", "Safari Zone", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_53, 2, 0, 0, 0},
    {"gym-6", emulocke::TrackerStopKind::Boss, "Koga", "Fuschia City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_54, 6, 0, 0, 6},
    {"safari-zone", emulocke::TrackerStopKind::Encounter, "Safari Zone", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_30, 1, nullptr, 0, 0, 0, 0},
    {"route-15", emulocke::TrackerStopKind::Encounter, "Route 15", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_31, 1, nullptr, 0, 0, 0, 0},
    {"route-14", emulocke::TrackerStopKind::Encounter, "Route 14", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_32, 1, nullptr, 0, 0, 0, 0},
    {"route-13", emulocke::TrackerStopKind::Encounter, "Route 13", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_33, 1, nullptr, 0, 0, 0, 0},
    {"power-plant", emulocke::TrackerStopKind::Encounter, "Power Plant", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_34, 1, nullptr, 0, 0, 0, 0},
    {"route-19", emulocke::TrackerStopKind::Encounter, "Route 19", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_35, 1, nullptr, 0, 0, 0, 0},
    {"route-20", emulocke::TrackerStopKind::Encounter, "Route 20", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_36, 1, nullptr, 0, 0, 0, 0},
    {"seafoam-islands", emulocke::TrackerStopKind::Encounter, "Seafoam Islands", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_37, 1, nullptr, 0, 0, 0, 0},
    {"mb6a", emulocke::TrackerStopKind::Boss, "Pryce (Team A)", "Seafoam Islands", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_63, 6, 0, 0, 0},
    {"mb6b", emulocke::TrackerStopKind::Boss, "Pryce (Team B)", "Seafoam Islands", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_64, 6, 0, 0, 0},
    {"mb6c", emulocke::TrackerStopKind::Boss, "Pryce (Team C)", "Seafoam Islands", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_65, 6, 0, 0, 0},
    {"cinnabar-island", emulocke::TrackerStopKind::Encounter, "Cinnabar Island", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_38, 1, nullptr, 0, 0, 0, 0},
    {"mb7a", emulocke::TrackerStopKind::Boss, "Jasmine (Team A)", "Cinnabar Island", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_67, 6, 0, 0, 0},
    {"mb7b", emulocke::TrackerStopKind::Boss, "Jasmine (Team B)", "Cinnabar Island", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_68, 6, 0, 0, 0},
    {"mb7c", emulocke::TrackerStopKind::Boss, "Jasmine (Team C)", "Cinnabar Island", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_69, 6, 0, 0, 0},
    {"m1", emulocke::TrackerStopKind::Boss, "May", "Pokémon Mansion Entrance", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_70, 6, 0, 0, 0},
    {"pokemon-mansion", emulocke::TrackerStopKind::Encounter, "Pokémon Mansion", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_39, 1, nullptr, 0, 0, 0, 0},
    {"gym-7", emulocke::TrackerStopKind::Boss, "Blaine", "Cinnabar Island Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_72, 6, 0, 0, 7},
    {"route-21", emulocke::TrackerStopKind::Encounter, "Route 21", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_40, 1, nullptr, 0, 0, 0, 0},
    {"gym-8", emulocke::TrackerStopKind::Boss, "Clair", "Viridian City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_74, 6, 0, 0, 8},
    {"r5", emulocke::TrackerStopKind::Boss, "Gary", "Route 22", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_75, 75, 0, 0, 0},
    {"route-23", emulocke::TrackerStopKind::Encounter, "Route 23", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_41, 1, nullptr, 0, 0, 0, 0},
    {"victory-road", emulocke::TrackerStopKind::Encounter, "Victory Road", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_42, 1, nullptr, 0, 0, 0, 0},
    {"b4", emulocke::TrackerStopKind::Boss, "Brendan", "Indigo Plateau", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_78, 2, 0, 0, 0},
    {"e1a", emulocke::TrackerStopKind::Boss, "Lorelei (Team A)", "Indigo Plateau", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_79, 6, 0, 0, 0},
    {"e1b", emulocke::TrackerStopKind::Boss, "Lorelei (Team B)", "Indigo Plateau", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_80, 6, 0, 0, 0},
    {"e2a", emulocke::TrackerStopKind::Boss, "Bruno (Team A)", "Indigo Plateau", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_81, 6, 0, 0, 0},
    {"e2b", emulocke::TrackerStopKind::Boss, "Bruno (Team B)", "Indigo Plateau", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_82, 6, 0, 0, 0},
    {"e3a", emulocke::TrackerStopKind::Boss, "Agatha (Team A)", "Indigo Plateau", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_83, 6, 0, 0, 0},
    {"e3b", emulocke::TrackerStopKind::Boss, "Agatha (Team B)", "Indigo Plateau", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_84, 6, 0, 0, 0},
    {"e4a", emulocke::TrackerStopKind::Boss, "Lance (Team A)", "Indigo Plateau", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_85, 6, 0, 0, 0},
    {"e4b", emulocke::TrackerStopKind::Boss, "Lance (Team B)", "Indigo Plateau", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_86, 6, 0, 0, 0},
    {"ec", emulocke::TrackerStopKind::Boss, "Gary", "Champion", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_87, 6, 0, 0, 0},
    {"three-island", emulocke::TrackerStopKind::Encounter, "Three Island", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_43, 1, nullptr, 0, 0, 0, 0},
    {"mt-ember", emulocke::TrackerStopKind::Encounter, "Mt. Ember", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"treasure-beach", emulocke::TrackerStopKind::Encounter, "Treasure Beach", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"berry-forest", emulocke::TrackerStopKind::Encounter, "Berry Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"bond-bridge", emulocke::TrackerStopKind::Encounter, "Bond Bridge", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"cape-brink", emulocke::TrackerStopKind::Encounter, "Cape Brink", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"kindle-road", emulocke::TrackerStopKind::Encounter, "Kindle Road", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"1r", emulocke::TrackerStopKind::Boss, "Brock Rematch", "Pewter City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_95, 6, 0, 0, 0},
    {"2r", emulocke::TrackerStopKind::Boss, "Misty Rematch", "Cerulean City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_96, 6, 0, 0, 0},
    {"3r", emulocke::TrackerStopKind::Boss, "Lt. Surge Rematch", "Vermillion City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_97, 6, 0, 0, 0},
    {"4r", emulocke::TrackerStopKind::Boss, "Erika Rematch", "Celadon City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_98, 6, 0, 0, 0},
    {"cerulean-cave", emulocke::TrackerStopKind::Encounter, "Cerulean Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_44, 1, nullptr, 0, 0, 0, 0},
    {"ev4", emulocke::TrackerStopKind::Boss, "Admin Archer", "Cerulean Cave", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_100, 3, 0, 0, 0},
    {"ev5", emulocke::TrackerStopKind::Boss, "Admin Ariana", "Cerulean Cave", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_101, 4, 0, 0, 0},
    {"ev6", emulocke::TrackerStopKind::Boss, "Giovanni", "Cerulean Cave", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_102, 6, 0, 0, 0}
};

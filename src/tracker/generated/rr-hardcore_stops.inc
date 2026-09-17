constexpr uint16_t kMet_rr_hardcore_0[] = {0};
constexpr uint16_t kMet_rr_hardcore_1[] = {13};
constexpr uint16_t kMet_rr_hardcore_2[] = {1};
constexpr uint16_t kMet_rr_hardcore_3[] = {34};
constexpr uint16_t kMet_rr_hardcore_4[] = {14};
constexpr uint16_t kMet_rr_hardcore_5[] = {38};
constexpr uint16_t kMet_rr_hardcore_6[] = {2};
constexpr uint16_t kMet_rr_hardcore_7[] = {15};
constexpr uint16_t kMet_rr_hardcore_8[] = {16, 11};
constexpr uint16_t kMet_rr_hardcore_9[] = {39};
constexpr uint16_t kMet_rr_hardcore_10[] = {36};
constexpr uint16_t kMet_rr_hardcore_11[] = {37};
constexpr uint16_t kMet_rr_hardcore_12[] = {3};
constexpr uint16_t kMet_rr_hardcore_13[] = {17};
constexpr uint16_t kMet_rr_hardcore_14[] = {18};
constexpr uint16_t kMet_rr_hardcore_15[] = {43};
constexpr uint16_t kMet_rr_hardcore_16[] = {23};
constexpr uint16_t kMet_rr_hardcore_17[] = {21};
constexpr uint16_t kMet_rr_hardcore_18[] = {50};
constexpr uint16_t kMet_rr_hardcore_19[] = {22, 12};
constexpr uint16_t kMet_rr_hardcore_20[] = {52};
constexpr uint16_t kMet_rr_hardcore_21[] = {24};
constexpr uint16_t kMet_rr_hardcore_22[] = {20};
constexpr uint16_t kMet_rr_hardcore_23[] = {19};
constexpr uint16_t kMet_rr_hardcore_24[] = {6};
constexpr uint16_t kMet_rr_hardcore_25[] = {10};
constexpr uint16_t kMet_rr_hardcore_26[] = {28};
constexpr uint16_t kMet_rr_hardcore_27[] = {29};
constexpr uint16_t kMet_rr_hardcore_28[] = {30};
constexpr uint16_t kMet_rr_hardcore_29[] = {48};
constexpr uint16_t kMet_rr_hardcore_30[] = {27};
constexpr uint16_t kMet_rr_hardcore_31[] = {26};
constexpr uint16_t kMet_rr_hardcore_32[] = {25};
constexpr uint16_t kMet_rr_hardcore_33[] = {54};
constexpr uint16_t kMet_rr_hardcore_34[] = {31};
constexpr uint16_t kMet_rr_hardcore_35[] = {32};
constexpr uint16_t kMet_rr_hardcore_36[] = {51};
constexpr uint16_t kMet_rr_hardcore_37[] = {8};
constexpr uint16_t kMet_rr_hardcore_38[] = {47};
constexpr uint16_t kMet_rr_hardcore_39[] = {33};
constexpr uint16_t kMet_rr_hardcore_40[] = {35};
constexpr uint16_t kMet_rr_hardcore_41[] = {44};
constexpr uint16_t kMet_rr_hardcore_42[] = {57};
constexpr uint16_t kMet_rr_hardcore_43[] = {53};
constexpr uint16_t kStarters_rr_hardcore[] = {1, 7, 4, 152, 155, 158, 252, 255, 258, 387, 390, 393, 495, 498, 501, 650, 653, 656, 722, 725, 728, 810, 813, 816, 909, 906, 912};
constexpr emulocke::TrackerStop kStops_rr_hardcore[] = {
    {"starter", emulocke::TrackerStopKind::Encounter, "Starter", "", emulocke::BossKind::None, emulocke::CatchKind::Starter, nullptr, 0, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"pallet-town", emulocke::TrackerStopKind::Encounter, "Pallet Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_0, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"r1", emulocke::TrackerStopKind::Boss, "Gary", "Oak's Laboratory", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_2, 24, 600, 0, 0, 5, 1, false, "", "", false},
    {"route-1", emulocke::TrackerStopKind::Encounter, "Route 1", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_1, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"r2-hard", emulocke::TrackerStopKind::Boss, "Gary", "Route 1", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_4, 42, 1609, 3, 0, 0, 1, false, "", "", false},
    {"viridian-city", emulocke::TrackerStopKind::Encounter, "Viridian City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_2, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-22", emulocke::TrackerStopKind::Encounter, "Route 22", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_3, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-2", emulocke::TrackerStopKind::Encounter, "Route 2", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_4, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"viridian-forest", emulocke::TrackerStopKind::Encounter, "Viridian Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_5, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"b1-hard", emulocke::TrackerStopKind::Boss, "Brendan", "Virdian Forest", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_9, 4, 1306, 3, 0, 0, 1, false, "", "", false},
    {"mb1-hard", emulocke::TrackerStopKind::Boss, "Falkner", "Pewter City Museum", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_10, 5, 1323, 0, 0, 0, 1, false, "", "", false},
    {"gym-1", emulocke::TrackerStopKind::Boss, "Brock", "Pewter City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_11, 6, 0, 0, 1, 16, 1, false, "sandstorm", "", false},
    {"pewter-city", emulocke::TrackerStopKind::Encounter, "Pewter City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_6, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-3", emulocke::TrackerStopKind::Encounter, "Route 3", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_7, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-4", emulocke::TrackerStopKind::Encounter, "Route 4", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_8, 2, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"mt-moon", emulocke::TrackerStopKind::Encounter, "Mt. Moon", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_9, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"ev1-hard", emulocke::TrackerStopKind::Boss, "Admin Archer", "Mt. Moon", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_16, 5, 1322, 0, 0, 0, 1, false, "", "", false},
    {"route-24", emulocke::TrackerStopKind::Encounter, "Route 24", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_10, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"r3-hard", emulocke::TrackerStopKind::Boss, "Gary", "Route 24", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_18, 75, 1612, 3, 0, 0, 1, false, "", "", false},
    {"route-25", emulocke::TrackerStopKind::Encounter, "Route 25", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_11, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"mb2-hard", emulocke::TrackerStopKind::Boss, "Bugsy", "Bill's House", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_20, 6, 1288, 0, 0, 0, 1, false, "rain", "", false},
    {"cerulean-city", emulocke::TrackerStopKind::Encounter, "Cerulean City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_12, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-2", emulocke::TrackerStopKind::Boss, "Misty", "Cerulean City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_22, 6, 0, 0, 2, 28, 1, false, "rain", "", false},
    {"route-5", emulocke::TrackerStopKind::Encounter, "Route 5", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_13, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-6", emulocke::TrackerStopKind::Encounter, "Route 6", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_14, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"vermillion-city", emulocke::TrackerStopKind::Encounter, "Vermillion City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-3", emulocke::TrackerStopKind::Boss, "Lt. Surge", "Vermillion City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_26, 6, 0, 0, 3, 36, 1, false, "electric-terrain", "", false},
    {"digletts-cave", emulocke::TrackerStopKind::Encounter, "Digletts Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_15, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"b2-hard", emulocke::TrackerStopKind::Boss, "Brendan", "S.S. Anne", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_28, 4, 1306, 3, 0, 0, 1, false, "", "", false},
    {"route-11", emulocke::TrackerStopKind::Encounter, "Route 11", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_16, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"mb3-hard", emulocke::TrackerStopKind::Boss, "Whitney", "Route 11", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_30, 6, 1329, 0, 0, 0, 1, false, "", "", false},
    {"route-9", emulocke::TrackerStopKind::Encounter, "Route 9", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_17, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"rock-tunnel", emulocke::TrackerStopKind::Encounter, "Rock Tunnel", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_18, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-10", emulocke::TrackerStopKind::Encounter, "Route 10", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_19, 2, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"mb4-hard", emulocke::TrackerStopKind::Boss, "Morty", "Lavender Town", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_34, 6, 1308, 0, 0, 0, 1, false, "", "", false},
    {"pokemon-tower", emulocke::TrackerStopKind::Encounter, "Pokémon Tower", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_20, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-12", emulocke::TrackerStopKind::Encounter, "Route 12", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_21, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-8", emulocke::TrackerStopKind::Encounter, "Route 8", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_22, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-7", emulocke::TrackerStopKind::Encounter, "Route 7", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_23, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"celadon-city", emulocke::TrackerStopKind::Encounter, "Celadon City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_24, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-4", emulocke::TrackerStopKind::Boss, "Erika", "Celadon City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_40, 6, 0, 0, 4, 44, 1, false, "grassy-terrain", "", false},
    {"ev2-hard", emulocke::TrackerStopKind::Boss, "Giovanni", "Celadon City Game Corner", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_41, 6, 1349, 0, 0, 47, 1, false, "", "", false},
    {"saffron-city", emulocke::TrackerStopKind::Encounter, "Saffron City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_25, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"r4-hard", emulocke::TrackerStopKind::Boss, "Gary", "Silph Co. Rival", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_43, 75, 1712, 3, 0, 0, 1, false, "", "", false},
    {"ev3-hard", emulocke::TrackerStopKind::Boss, "Archer & Ariana", "Silph Co.", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_44, 4, 1321, 0, 0, 55, 2, true, "", "", false},
    {"ev4-hard", emulocke::TrackerStopKind::Boss, "Giovanni", "Silph Co.", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_45, 6, 1349, 0, 0, 57, 1, false, "", "", false},
    {"mb5-hard", emulocke::TrackerStopKind::Boss, "Chuck", "Saffron City Dojo", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_46, 6, 1597, 0, 0, 0, 1, false, "", "Fighting Spirit Chuck's Pokemon will Endure a hit if above 75% of max HP", false},
    {"gym-5", emulocke::TrackerStopKind::Boss, "Sabrina", "Saffron City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_47, 6, 0, 0, 5, 59, 2, false, "", "Trick Room There is a permanent Trick Room effect on the field", false},
    {"route-16", emulocke::TrackerStopKind::Encounter, "Route 16", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_26, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-17", emulocke::TrackerStopKind::Encounter, "Route 17", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_27, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-18", emulocke::TrackerStopKind::Encounter, "Route 18", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_28, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"fuschia-city", emulocke::TrackerStopKind::Encounter, "Fuschia City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"b3-hard", emulocke::TrackerStopKind::Boss, "Brendan", "Safari Zone", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_52, 4, 1306, 3, 0, 0, 1, false, "", "", false},
    {"gym-6", emulocke::TrackerStopKind::Boss, "Koga", "Fuschia City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_53, 6, 0, 0, 6, 68, 1, false, "", "Tailwind There is a permanent tailwind effect on Koga's side of the field", false},
    {"safari-zone", emulocke::TrackerStopKind::Encounter, "Safari Zone", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_29, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-15", emulocke::TrackerStopKind::Encounter, "Route 15", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_30, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-14", emulocke::TrackerStopKind::Encounter, "Route 14", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_31, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-13", emulocke::TrackerStopKind::Encounter, "Route 13", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_32, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"power-plant", emulocke::TrackerStopKind::Encounter, "Power Plant", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_33, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-19", emulocke::TrackerStopKind::Encounter, "Route 19", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_34, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-20", emulocke::TrackerStopKind::Encounter, "Route 20", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_35, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"seafoam-islands", emulocke::TrackerStopKind::Encounter, "Seafoam Islands", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_36, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"mb6a-hard", emulocke::TrackerStopKind::Boss, "Pryce (Team A)", "Seafoam Islands", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_62, 6, 1338, 0, 0, 0, 1, false, "hail", "Hard ice All Pryce's Pokemon have a +50% Defense boost", false},
    {"mb6b-hard", emulocke::TrackerStopKind::Boss, "Pryce (Team B)", "Seafoam Islands", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_63, 6, 1338, 0, 0, 0, 1, false, "hail", "Hard ice All Pryce's Pokemon have a +50% Defense boost", false},
    {"mb6c-hard", emulocke::TrackerStopKind::Boss, "Pryce (Team C)", "Seafoam Islands", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_64, 6, 1338, 0, 0, 0, 1, false, "hail", "Hard ice All Pryce's Pokemon have a +50% Defense boost", false},
    {"cinnabar-island", emulocke::TrackerStopKind::Encounter, "Cinnabar Island", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_37, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"mb7-hard", emulocke::TrackerStopKind::Boss, "Jasmine", "Cinnabar Island", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_66, 6, 1309, 0, 0, 0, 1, false, "", "Tempered steel Jasmine's Pokemon are immune to Fire type attacks", false},
    {"m1-hard", emulocke::TrackerStopKind::Boss, "May", "Pokémon Mansion Entrance", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_67, 6, 1341, 3, 0, 73, 1, false, "", "", false},
    {"pokemon-mansion", emulocke::TrackerStopKind::Encounter, "Pokémon Mansion", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_38, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-7", emulocke::TrackerStopKind::Boss, "Blaine", "Cinnabar Island Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_69, 6, 0, 0, 7, 76, 1, false, "sunlight", "", false},
    {"route-21", emulocke::TrackerStopKind::Encounter, "Route 21", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_39, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-8", emulocke::TrackerStopKind::Boss, "Clair", "Viridian City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_71, 6, 0, 0, 8, 81, 1, false, "", "Purist Unable to bring fairy types into the Fight Sticky terrain You can't remove hazards from the field", false},
    {"r5-hard", emulocke::TrackerStopKind::Boss, "Gary", "Route 22", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_72, 144, 1715, 3, 0, 0, 1, false, "", "", false},
    {"route-23", emulocke::TrackerStopKind::Encounter, "Route 23", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_40, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"victory-road", emulocke::TrackerStopKind::Encounter, "Victory Road", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_41, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"b4-hard", emulocke::TrackerStopKind::Boss, "Brendan", "Indigo Plateau", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_75, 4, 1306, 3, 0, 0, 1, false, "", "", false},
    {"e1a-hard", emulocke::TrackerStopKind::Boss, "Lorelei (Team A)", "Indigo Plateau", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_76, 6, 1357, 0, 0, 0, 2, false, "rain", "Heavy rain Lorelei's Pokemon are immune to Fire type attacks", false},
    {"e1b-hard", emulocke::TrackerStopKind::Boss, "Lorelei (Team B)", "Indigo Plateau", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_77, 6, 1357, 0, 0, 0, 2, false, "hail", "", false},
    {"e2a-hard", emulocke::TrackerStopKind::Boss, "Bruno (Team A)", "Indigo Plateau", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_78, 6, 1360, 0, 0, 0, 1, false, "misty-terrain", "", false},
    {"e2b-hard", emulocke::TrackerStopKind::Boss, "Bruno (Team B)", "Indigo Plateau", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_79, 6, 1360, 0, 0, 0, 1, false, "", "", false},
    {"e3-hard", emulocke::TrackerStopKind::Boss, "Agatha", "Indigo Plateau", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_80, 6, 1363, 0, 0, 0, 1, false, "psychic-terrain", "", false},
    {"e4a-hard", emulocke::TrackerStopKind::Boss, "Lance (Team A)", "Indigo Plateau", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_81, 6, 1319, 0, 0, 0, 1, false, "", "Sticky terrain You can't remove hazards from the field", false},
    {"e4b-hard", emulocke::TrackerStopKind::Boss, "Lance (Team B)", "Indigo Plateau", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_82, 6, 1319, 0, 0, 0, 1, false, "", "Sticky terrain You can't remove hazards from the field", false},
    {"ec-hard", emulocke::TrackerStopKind::Boss, "Gary", "Champion", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_83, 144, 1718, 3, 0, 0, 1, false, "", "", false},
    {"three-island", emulocke::TrackerStopKind::Encounter, "Three Island", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_42, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"mt-ember", emulocke::TrackerStopKind::Encounter, "Mt. Ember", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"treasure-beach", emulocke::TrackerStopKind::Encounter, "Treasure Beach", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"berry-forest", emulocke::TrackerStopKind::Encounter, "Berry Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"bond-bridge", emulocke::TrackerStopKind::Encounter, "Bond Bridge", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"cape-brink", emulocke::TrackerStopKind::Encounter, "Cape Brink", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"kindle-road", emulocke::TrackerStopKind::Encounter, "Kindle Road", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"1r-hard", emulocke::TrackerStopKind::Boss, "Brock Rematch", "Pewter City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_91, 6, 1336, 0, 0, 0, 1, false, "sandstorm", "Cushioning Super Effective moves deal 1/3 less damage to Brock's Pokemon", false},
    {"2r-hard", emulocke::TrackerStopKind::Boss, "Misty Rematch", "Cerulean City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_92, 6, 1312, 0, 0, 0, 1, false, "rain", "", false},
    {"3r-hard", emulocke::TrackerStopKind::Boss, "Lt. Surge Rematch", "Vermillion City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_93, 6, 1440, 0, 0, 0, 1, false, "electric-terrain", "Magnet Rise Lt. Surge's Pokemon are immune to Ground type attacks", false},
    {"4r-hard", emulocke::TrackerStopKind::Boss, "Erika Rematch", "Celadon City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_94, 6, 1345, 0, 0, 0, 1, false, "grassy-terrain", "", false},
    {"cerulean-cave", emulocke::TrackerStopKind::Encounter, "Cerulean Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rr_hardcore_43, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"ev5-hard", emulocke::TrackerStopKind::Boss, "Admin Archer", "Cerulean Cave", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_96, 5, 1322, 0, 0, 0, 1, false, "", "", false},
    {"ev6-hard", emulocke::TrackerStopKind::Boss, "Admin Ariana", "Cerulean Cave", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_97, 4, 1321, 0, 0, 0, 1, false, "", "", false},
    {"ev7-hard", emulocke::TrackerStopKind::Boss, "Giovanni", "Cerulean Cave", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_rr_hardcore_98, 6, 1349, 0, 0, 80, 2, false, "", "", false}
};

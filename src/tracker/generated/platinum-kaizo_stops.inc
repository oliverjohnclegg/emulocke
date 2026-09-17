constexpr uint16_t kMet_platinum_kaizo_0[] = {1};
constexpr uint16_t kMet_platinum_kaizo_1[] = {16};
constexpr uint16_t kMet_platinum_kaizo_2[] = {76};
constexpr uint16_t kMet_platinum_kaizo_3[] = {17};
constexpr uint16_t kMet_platinum_kaizo_4[] = {18};
constexpr uint16_t kMet_platinum_kaizo_5[] = {59};
constexpr uint16_t kMet_platinum_kaizo_6[] = {8};
constexpr uint16_t kMet_platinum_kaizo_7[] = {46};
constexpr uint16_t kMet_platinum_kaizo_8[] = {22};
constexpr uint16_t kMet_platinum_kaizo_9[] = {19};
constexpr uint16_t kMet_platinum_kaizo_10[] = {57};
constexpr uint16_t kMet_platinum_kaizo_11[] = {58};
constexpr uint16_t kMet_platinum_kaizo_12[] = {20};
constexpr uint16_t kMet_platinum_kaizo_13[] = {47};
constexpr uint16_t kMet_platinum_kaizo_14[] = {48};
constexpr uint16_t kMet_platinum_kaizo_15[] = {9};
constexpr uint16_t kMet_platinum_kaizo_16[] = {21};
constexpr uint16_t kMet_platinum_kaizo_17[] = {65};
constexpr uint16_t kMet_platinum_kaizo_18[] = {50};
constexpr uint16_t kMet_platinum_kaizo_19[] = {23};
constexpr uint16_t kMet_platinum_kaizo_20[] = {10};
constexpr uint16_t kMet_platinum_kaizo_21[] = {24};
constexpr uint16_t kMet_platinum_kaizo_22[] = {53};
constexpr uint16_t kMet_platinum_kaizo_23[] = {25};
constexpr uint16_t kMet_platinum_kaizo_24[] = {30};
constexpr uint16_t kMet_platinum_kaizo_25[] = {12};
constexpr uint16_t kMet_platinum_kaizo_26[] = {29};
constexpr uint16_t kMet_platinum_kaizo_27[] = {73};
constexpr uint16_t kMet_platinum_kaizo_28[] = {11};
constexpr uint16_t kMet_platinum_kaizo_29[] = {52};
constexpr uint16_t kMet_platinum_kaizo_30[] = {27};
constexpr uint16_t kMet_platinum_kaizo_31[] = {28};
constexpr uint16_t kMet_platinum_kaizo_32[] = {5};
constexpr uint16_t kMet_platinum_kaizo_33[] = {49};
constexpr uint16_t kMet_platinum_kaizo_34[] = {35};
constexpr uint16_t kMet_platinum_kaizo_35[] = {36};
constexpr uint16_t kMet_platinum_kaizo_36[] = {33};
constexpr uint16_t kMet_platinum_kaizo_37[] = {7};
constexpr uint16_t kMet_platinum_kaizo_38[] = {69};
constexpr uint16_t kMet_platinum_kaizo_39[] = {26};
constexpr uint16_t kMet_platinum_kaizo_40[] = {31};
constexpr uint16_t kMet_platinum_kaizo_41[] = {32};
constexpr uint16_t kMet_platinum_kaizo_42[] = {74};
constexpr uint16_t kMet_platinum_kaizo_43[] = {78};
constexpr uint16_t kMet_platinum_kaizo_44[] = {117};
constexpr uint16_t kMet_platinum_kaizo_45[] = {37};
constexpr uint16_t kMet_platinum_kaizo_46[] = {13};
constexpr uint16_t kMet_platinum_kaizo_47[] = {38};
constexpr uint16_t kMet_platinum_kaizo_48[] = {15};
constexpr uint16_t kMet_platinum_kaizo_49[] = {64};
constexpr uint16_t kStarters_platinum_kaizo[] = {387, 390, 393};
constexpr emulocke::TrackerStop kStops_platinum_kaizo[] = {
    {"starter", emulocke::TrackerStopKind::Encounter, "Starter", "", emulocke::BossKind::None, emulocke::CatchKind::Starter, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"twinleaf-town", emulocke::TrackerStopKind::Encounter, "Twinleaf Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_0, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-201", emulocke::TrackerStopKind::Encounter, "Route 201", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_1, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"b1", emulocke::TrackerStopKind::Boss, "Barry", "Route 201", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_3, 3, 2030, 3, 0, 1, false, "", "", false},
    {"lake-verity", emulocke::TrackerStopKind::Encounter, "Lake Verity", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_2, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-202", emulocke::TrackerStopKind::Encounter, "Route 202", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_3, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-203", emulocke::TrackerStopKind::Encounter, "Route 203", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_4, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"b2", emulocke::TrackerStopKind::Boss, "Barry", "Route 203", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_7, 4, 1427, 3, 0, 1, false, "", "", false},
    {"oreburgh-gate", emulocke::TrackerStopKind::Encounter, "Oreburgh Gate", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_5, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"oreburgh-city", emulocke::TrackerStopKind::Encounter, "Oreburgh City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_6, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-1", emulocke::TrackerStopKind::Boss, "Roark", "Oreburgh Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_10, 3, 0, 0, 1, 1, false, "", "", false},
    {"oreburgh-mine", emulocke::TrackerStopKind::Encounter, "Oreburgh Mine", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_7, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-207", emulocke::TrackerStopKind::Encounter, "Route 207", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_8, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-204", emulocke::TrackerStopKind::Encounter, "Route 204", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_9, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"ravaged-path", emulocke::TrackerStopKind::Encounter, "Ravaged Path", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_10, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"floaroma-meadow", emulocke::TrackerStopKind::Encounter, "Floaroma Meadow", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_11, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-205", emulocke::TrackerStopKind::Encounter, "Route 205", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_12, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"valley-windworks", emulocke::TrackerStopKind::Encounter, "Valley Windworks", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_13, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"mars1", emulocke::TrackerStopKind::Boss, "Mars", "Valley Windoworks", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_18, 2, 1475, 0, 0, 1, false, "", "", false},
    {"eterna-forest", emulocke::TrackerStopKind::Encounter, "Eterna Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_14, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"the-old-chateau", emulocke::TrackerStopKind::Encounter, "The Old Chateau", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"eterna-city", emulocke::TrackerStopKind::Encounter, "Eterna City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_15, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-2", emulocke::TrackerStopKind::Boss, "Gardenia", "Eterna Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_22, 3, 0, 0, 2, 1, false, "", "", false},
    {"jup1", emulocke::TrackerStopKind::Boss, "Jupiter", "Eterna Building", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_23, 2, 1586, 0, 0, 1, false, "", "", false},
    {"route-206", emulocke::TrackerStopKind::Encounter, "Route 206", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_16, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"wayward-cave", emulocke::TrackerStopKind::Encounter, "Wayward Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_17, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"mt-coronet", emulocke::TrackerStopKind::Encounter, "Mt. Coronet", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_18, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-208", emulocke::TrackerStopKind::Encounter, "Route 208", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_19, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"hearthome-city", emulocke::TrackerStopKind::Encounter, "Hearthome City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_20, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-3", emulocke::TrackerStopKind::Boss, "Fantina", "Hearthome Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_29, 3, 0, 0, 3, 1, false, "", "", false},
    {"route-209", emulocke::TrackerStopKind::Encounter, "Route 209", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_21, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"b3", emulocke::TrackerStopKind::Boss, "Barry", "Route 209", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_31, 10, 1650, 3, 0, 1, false, "", "", false},
    {"the-lost-tower", emulocke::TrackerStopKind::Encounter, "The Lost Tower", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"solaceon-ruins", emulocke::TrackerStopKind::Encounter, "Solaceon Ruins", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_22, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-210", emulocke::TrackerStopKind::Encounter, "Route 210", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_23, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-215", emulocke::TrackerStopKind::Encounter, "Route 215", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_24, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"veilstone-city", emulocke::TrackerStopKind::Encounter, "Veilstone City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_25, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-4", emulocke::TrackerStopKind::Boss, "Maylene", "Veilstone Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_37, 3, 0, 0, 4, 1, false, "", "", false},
    {"route-214", emulocke::TrackerStopKind::Encounter, "Route 214", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_26, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"ruin-maniacs-cave", emulocke::TrackerStopKind::Encounter, "Ruin Maniac's Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"ruin-maniacs-tunnel", emulocke::TrackerStopKind::Encounter, "Ruin Maniac's Tunnel", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"valor-lakefront", emulocke::TrackerStopKind::Encounter, "Valor Lakefront", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_27, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"pastoria-city", emulocke::TrackerStopKind::Encounter, "Pastoria City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_28, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"great-marsh", emulocke::TrackerStopKind::Encounter, "Great Marsh", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_29, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"b4", emulocke::TrackerStopKind::Boss, "Barry", "Pastoria City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_44, 10, 1653, 3, 0, 1, false, "", "", false},
    {"gym-5", emulocke::TrackerStopKind::Boss, "Crasher Wake", "Pastoria Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_45, 3, 0, 0, 5, 1, false, "", "", false},
    {"route-212", emulocke::TrackerStopKind::Encounter, "Route 212", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_30, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-213", emulocke::TrackerStopKind::Encounter, "Route 213", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_31, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"celestic-town", emulocke::TrackerStopKind::Encounter, "Celestic Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_32, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"cyr1", emulocke::TrackerStopKind::Boss, "Cyrus", "Celestic Town", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_49, 3, 2093, 0, 0, 1, false, "", "", false},
    {"fuego-ironworks", emulocke::TrackerStopKind::Encounter, "Fuego Ironworks", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_33, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"routes-219", emulocke::TrackerStopKind::Encounter, "Routes 219", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-220", emulocke::TrackerStopKind::Encounter, "Route 220", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_34, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-221", emulocke::TrackerStopKind::Encounter, "Route 221", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_35, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-218", emulocke::TrackerStopKind::Encounter, "Route 218", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_36, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"canalave-city", emulocke::TrackerStopKind::Encounter, "Canalave City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_37, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"b5", emulocke::TrackerStopKind::Boss, "Barry", "Canalave City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_56, 11, 1656, 3, 0, 1, false, "", "", false},
    {"gym-6", emulocke::TrackerStopKind::Boss, "Byron", "Canalave Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_57, 3, 0, 0, 6, 1, false, "", "", false},
    {"iron-island", emulocke::TrackerStopKind::Encounter, "Iron Island", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_38, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-211", emulocke::TrackerStopKind::Encounter, "Route 211", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_39, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"sat1", emulocke::TrackerStopKind::Boss, "Saturn", "Valor Cavern", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_60, 3, 227, 0, 0, 1, false, "", "", false},
    {"mars2", emulocke::TrackerStopKind::Boss, "Mars", "Lake Verity", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_61, 3, 1585, 0, 0, 1, false, "", "", false},
    {"route-216", emulocke::TrackerStopKind::Encounter, "Route 216", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_40, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-217", emulocke::TrackerStopKind::Encounter, "Route 217", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_41, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"acuity-lakefront", emulocke::TrackerStopKind::Encounter, "Acuity Lakefront", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_42, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"lake-acuity", emulocke::TrackerStopKind::Encounter, "Lake Acuity", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_43, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-7", emulocke::TrackerStopKind::Boss, "Candice", "Snowpoint Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_66, 4, 0, 0, 7, 1, false, "", "", false},
    {"cyr2", emulocke::TrackerStopKind::Boss, "Cyrus", "Galactic HQ", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_67, 3, 1583, 0, 0, 1, false, "", "", false},
    {"sat2", emulocke::TrackerStopKind::Boss, "Saturn", "Galactic HQ", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_68, 3, 90, 0, 0, 1, false, "", "", false},
    {"mnj", emulocke::TrackerStopKind::Boss, "Mars & Jupiter", "Spear Pillar", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_69, 6, 1587, 0, 0, 1, false, "", "", false},
    {"cyr3", emulocke::TrackerStopKind::Boss, "Cyrus", "Distortion World", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_70, 5, 1584, 0, 0, 1, false, "", "", false},
    {"distortion-world", emulocke::TrackerStopKind::Encounter, "Distortion World", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_44, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-222", emulocke::TrackerStopKind::Encounter, "Route 222", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_45, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"sunyshore-city", emulocke::TrackerStopKind::Encounter, "Sunyshore City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_46, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-8", emulocke::TrackerStopKind::Boss, "Volkner", "Sunyshore Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_74, 4, 0, 0, 8, 1, false, "", "", false},
    {"route-223", emulocke::TrackerStopKind::Encounter, "Route 223", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_47, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"victory-road", emulocke::TrackerStopKind::Encounter, "Victory Road", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"pokemon-league", emulocke::TrackerStopKind::Encounter, "Pokémon League", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_48, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"b6", emulocke::TrackerStopKind::Boss, "Barry", "Pokémon League", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_78, 12, 1659, 3, 0, 1, false, "", "", false},
    {"e1", emulocke::TrackerStopKind::Boss, "Aaron", "Elite Four", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_79, 5, 1441, 0, 0, 1, false, "", "", false},
    {"e2", emulocke::TrackerStopKind::Boss, "Bertha", "Elite Four", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_80, 5, 1442, 0, 0, 1, false, "", "", false},
    {"e3", emulocke::TrackerStopKind::Boss, "Flint", "Elite Four", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_81, 5, 1443, 0, 0, 1, false, "", "", false},
    {"e4", emulocke::TrackerStopKind::Boss, "Lucian", "Elite Four", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_82, 5, 1444, 0, 0, 1, false, "", "", false},
    {"c", emulocke::TrackerStopKind::Boss, "Cynthia", "Champion", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_platinum_kaizo_83, 6, 1447, 0, 0, 1, false, "", "", false},
    {"snowpoint-temple", emulocke::TrackerStopKind::Encounter, "Snowpoint Temple", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_platinum_kaizo_49, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false}
};

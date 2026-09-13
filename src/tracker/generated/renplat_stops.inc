constexpr uint16_t kMet_renplat_0[] = {1};
constexpr uint16_t kMet_renplat_1[] = {16};
constexpr uint16_t kMet_renplat_2[] = {76};
constexpr uint16_t kMet_renplat_3[] = {17};
constexpr uint16_t kMet_renplat_4[] = {18};
constexpr uint16_t kMet_renplat_5[] = {59};
constexpr uint16_t kMet_renplat_6[] = {8};
constexpr uint16_t kMet_renplat_7[] = {46};
constexpr uint16_t kMet_renplat_8[] = {22};
constexpr uint16_t kMet_renplat_9[] = {19};
constexpr uint16_t kMet_renplat_10[] = {6};
constexpr uint16_t kMet_renplat_11[] = {57};
constexpr uint16_t kMet_renplat_12[] = {3};
constexpr uint16_t kMet_renplat_13[] = {58};
constexpr uint16_t kMet_renplat_14[] = {20};
constexpr uint16_t kMet_renplat_15[] = {47};
constexpr uint16_t kMet_renplat_16[] = {48};
constexpr uint16_t kMet_renplat_17[] = {9};
constexpr uint16_t kMet_renplat_18[] = {21};
constexpr uint16_t kMet_renplat_19[] = {65};
constexpr uint16_t kMet_renplat_20[] = {50};
constexpr uint16_t kMet_renplat_21[] = {23};
constexpr uint16_t kMet_renplat_22[] = {24};
constexpr uint16_t kMet_renplat_23[] = {53};
constexpr uint16_t kMet_renplat_24[] = {25};
constexpr uint16_t kMet_renplat_25[] = {30};
constexpr uint16_t kMet_renplat_26[] = {12};
constexpr uint16_t kMet_renplat_27[] = {29};
constexpr uint16_t kMet_renplat_28[] = {73};
constexpr uint16_t kMet_renplat_29[] = {11};
constexpr uint16_t kMet_renplat_30[] = {52};
constexpr uint16_t kMet_renplat_31[] = {27};
constexpr uint16_t kMet_renplat_32[] = {28};
constexpr uint16_t kMet_renplat_33[] = {5};
constexpr uint16_t kMet_renplat_34[] = {49};
constexpr uint16_t kMet_renplat_35[] = {34};
constexpr uint16_t kMet_renplat_36[] = {35};
constexpr uint16_t kMet_renplat_37[] = {36};
constexpr uint16_t kMet_renplat_38[] = {33};
constexpr uint16_t kMet_renplat_39[] = {7};
constexpr uint16_t kMet_renplat_40[] = {69};
constexpr uint16_t kMet_renplat_41[] = {26};
constexpr uint16_t kMet_renplat_42[] = {31};
constexpr uint16_t kMet_renplat_43[] = {32};
constexpr uint16_t kMet_renplat_44[] = {74};
constexpr uint16_t kMet_renplat_45[] = {78};
constexpr uint16_t kMet_renplat_46[] = {64};
constexpr uint16_t kMet_renplat_47[] = {37};
constexpr uint16_t kMet_renplat_48[] = {13};
constexpr uint16_t kMet_renplat_49[] = {38};
constexpr uint16_t kMet_renplat_50[] = {15};
constexpr uint16_t kMet_renplat_51[] = {39};
constexpr uint16_t kStarters_renplat[] = {393, 387, 390};
constexpr emulocke::TrackerStop kStops_renplat[] = {
    {"starter", emulocke::TrackerStopKind::Encounter, "Starter", "", emulocke::BossKind::None, emulocke::CatchKind::Starter, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"twinleaf-town", emulocke::TrackerStopKind::Encounter, "Twinleaf Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_0, 1, nullptr, 0, 0, 0, 0},
    {"route-201", emulocke::TrackerStopKind::Encounter, "Route 201", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_1, 1, nullptr, 0, 0, 0, 0},
    {"b1", emulocke::TrackerStopKind::Boss, "Barry", "Route 201", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_3, 3, 0, 0, 0},
    {"lake-verity", emulocke::TrackerStopKind::Encounter, "Lake Verity", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_2, 1, nullptr, 0, 0, 0, 0},
    {"route-202", emulocke::TrackerStopKind::Encounter, "Route 202", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_3, 1, nullptr, 0, 0, 0, 0},
    {"route-203", emulocke::TrackerStopKind::Encounter, "Route 203", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_4, 1, nullptr, 0, 0, 0, 0},
    {"b2", emulocke::TrackerStopKind::Boss, "Barry", "Route 203", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_7, 5, 0, 0, 0},
    {"oreburgh-gate", emulocke::TrackerStopKind::Encounter, "Oreburgh Gate", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_5, 1, nullptr, 0, 0, 0, 0},
    {"oreburgh-city", emulocke::TrackerStopKind::Encounter, "Oreburgh City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_6, 1, nullptr, 0, 0, 0, 0},
    {"gym-1", emulocke::TrackerStopKind::Boss, "Roark", "Oreburgh Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_10, 6, 0, 0, 1},
    {"oreburgh-mine", emulocke::TrackerStopKind::Encounter, "Oreburgh Mine", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_7, 1, nullptr, 0, 0, 0, 0},
    {"route-207", emulocke::TrackerStopKind::Encounter, "Route 207", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_8, 1, nullptr, 0, 0, 0, 0},
    {"route-204", emulocke::TrackerStopKind::Encounter, "Route 204", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_9, 1, nullptr, 0, 0, 0, 0},
    {"jubilife-city", emulocke::TrackerStopKind::Encounter, "Jubilife City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_10, 1, nullptr, 0, 0, 0, 0},
    {"ravaged-path", emulocke::TrackerStopKind::Encounter, "Ravaged Path", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_11, 1, nullptr, 0, 0, 0, 0},
    {"floaroma-town", emulocke::TrackerStopKind::Encounter, "Floaroma Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_12, 1, nullptr, 0, 0, 0, 0},
    {"floaroma-meadow", emulocke::TrackerStopKind::Encounter, "Floaroma Meadow", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_13, 1, nullptr, 0, 0, 0, 0},
    {"route-205", emulocke::TrackerStopKind::Encounter, "Route 205", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_14, 1, nullptr, 0, 0, 0, 0},
    {"valley-windworks", emulocke::TrackerStopKind::Encounter, "Valley Windworks", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_15, 1, nullptr, 0, 0, 0, 0},
    {"mars1", emulocke::TrackerStopKind::Boss, "Mars", "Valley Windoworks", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_20, 4, 0, 0, 0},
    {"eterna-forest", emulocke::TrackerStopKind::Encounter, "Eterna Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_16, 1, nullptr, 0, 0, 0, 0},
    {"cheryl", emulocke::TrackerStopKind::Boss, "Cheryl", "Eterna Forest", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_22, 4, 0, 0, 0},
    {"the-old-chateau", emulocke::TrackerStopKind::Encounter, "The Old Chateau", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"eterna-city", emulocke::TrackerStopKind::Encounter, "Eterna City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_17, 1, nullptr, 0, 0, 0, 0},
    {"gym-2", emulocke::TrackerStopKind::Boss, "Gardenia", "Eterna Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_25, 6, 0, 0, 2},
    {"jup1", emulocke::TrackerStopKind::Boss, "Jupiter", "Eterna Building", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_26, 4, 0, 0, 0},
    {"eterna-building", emulocke::TrackerStopKind::Encounter, "Eterna Building", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"l1", emulocke::TrackerStopKind::Boss, "Lucas", "Route 207", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_28, 6, 0, 0, 0},
    {"d1", emulocke::TrackerStopKind::Boss, "Dawn", "Route 207", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_29, 6, 0, 0, 0},
    {"route-206", emulocke::TrackerStopKind::Encounter, "Route 206", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_18, 1, nullptr, 0, 0, 0, 0},
    {"wayward-cave", emulocke::TrackerStopKind::Encounter, "Wayward Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_19, 1, nullptr, 0, 0, 0, 0},
    {"mira", emulocke::TrackerStopKind::Boss, "Mira", "Wayward Cave", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_32, 4, 0, 0, 0},
    {"mt-coronet", emulocke::TrackerStopKind::Encounter, "Mt. Coronet", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_20, 1, nullptr, 0, 0, 0, 0},
    {"route-208", emulocke::TrackerStopKind::Encounter, "Route 208", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_21, 1, nullptr, 0, 0, 0, 0},
    {"aaron", emulocke::TrackerStopKind::Boss, "Aaron", "Route 208", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_35, 5, 0, 0, 0},
    {"gym-3", emulocke::TrackerStopKind::Boss, "Fantina", "Hearthome Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_36, 6, 0, 0, 3},
    {"b3", emulocke::TrackerStopKind::Boss, "Barry", "Hearthome City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_37, 6, 0, 0, 0},
    {"sat1", emulocke::TrackerStopKind::Boss, "Saturn & Gentleman Backlot", "Route 212", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_38, 6, 0, 0, 0},
    {"route-209", emulocke::TrackerStopKind::Encounter, "Route 209", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_22, 1, nullptr, 0, 0, 0, 0},
    {"the-lost-tower", emulocke::TrackerStopKind::Encounter, "The Lost Tower", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"solaceon-ruins", emulocke::TrackerStopKind::Encounter, "Solaceon Ruins", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_23, 1, nullptr, 0, 0, 0, 0},
    {"route-210", emulocke::TrackerStopKind::Encounter, "Route 210", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_24, 1, nullptr, 0, 0, 0, 0},
    {"route-215", emulocke::TrackerStopKind::Encounter, "Route 215", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_25, 1, nullptr, 0, 0, 0, 0},
    {"veilstone-city", emulocke::TrackerStopKind::Encounter, "Veilstone City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_26, 1, nullptr, 0, 0, 0, 0},
    {"gym-4", emulocke::TrackerStopKind::Boss, "Maylene", "Veilstone Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_45, 6, 0, 0, 4},
    {"d2", emulocke::TrackerStopKind::Boss, "Dawn", "Route 210", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_46, 10, 0, 0, 0},
    {"l2", emulocke::TrackerStopKind::Boss, "Lucas", "Route 210", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_47, 10, 0, 0, 0},
    {"route-214", emulocke::TrackerStopKind::Encounter, "Route 214", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_27, 1, nullptr, 0, 0, 0, 0},
    {"ruin-maniacs-cave", emulocke::TrackerStopKind::Encounter, "Ruin Maniac's Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"ruin-maniacs-tunnel", emulocke::TrackerStopKind::Encounter, "Ruin Maniac's Tunnel", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"valor-lakefront", emulocke::TrackerStopKind::Encounter, "Valor Lakefront", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_28, 1, nullptr, 0, 0, 0, 0},
    {"pastoria-city", emulocke::TrackerStopKind::Encounter, "Pastoria City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_29, 1, nullptr, 0, 0, 0, 0},
    {"great-marsh", emulocke::TrackerStopKind::Encounter, "Great Marsh", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_30, 1, nullptr, 0, 0, 0, 0},
    {"b4", emulocke::TrackerStopKind::Boss, "Barry", "Pastoria City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_54, 12, 0, 0, 0},
    {"gym-5", emulocke::TrackerStopKind::Boss, "Crasher Wake", "Pastoria Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_55, 6, 0, 0, 5},
    {"route-212", emulocke::TrackerStopKind::Encounter, "Route 212", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_31, 1, nullptr, 0, 0, 0, 0},
    {"route-213", emulocke::TrackerStopKind::Encounter, "Route 213", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_32, 1, nullptr, 0, 0, 0, 0},
    {"celestic-town", emulocke::TrackerStopKind::Encounter, "Celestic Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_33, 1, nullptr, 0, 0, 0, 0},
    {"cyr1", emulocke::TrackerStopKind::Boss, "Cyrus", "Celestic Town", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_59, 4, 0, 0, 0},
    {"fuego-ironworks", emulocke::TrackerStopKind::Encounter, "Fuego Ironworks", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_34, 1, nullptr, 0, 0, 0, 0},
    {"route-219", emulocke::TrackerStopKind::Encounter, "Route 219", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_35, 1, nullptr, 0, 0, 0, 0},
    {"route-220", emulocke::TrackerStopKind::Encounter, "Route 220", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_36, 1, nullptr, 0, 0, 0, 0},
    {"route-221", emulocke::TrackerStopKind::Encounter, "Route 221", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_37, 1, nullptr, 0, 0, 0, 0},
    {"darach", emulocke::TrackerStopKind::Boss, "Castle Valet Darach", "Pal Park", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_64, 6, 0, 0, 0},
    {"route-218", emulocke::TrackerStopKind::Encounter, "Route 218", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_38, 1, nullptr, 0, 0, 0, 0},
    {"canalave-city", emulocke::TrackerStopKind::Encounter, "Canalave City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_39, 1, nullptr, 0, 0, 0, 0},
    {"b5", emulocke::TrackerStopKind::Boss, "Barry", "Canalave City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_67, 12, 0, 0, 0},
    {"iron-island", emulocke::TrackerStopKind::Encounter, "Iron Island", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_40, 1, nullptr, 0, 0, 0, 0},
    {"riley", emulocke::TrackerStopKind::Boss, "Riley", "Iron Island", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_69, 6, 0, 0, 0},
    {"gym-6", emulocke::TrackerStopKind::Boss, "Byron", "Canalave Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_70, 6, 0, 0, 6},
    {"route-211", emulocke::TrackerStopKind::Encounter, "Route 211", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_41, 1, nullptr, 0, 0, 0, 0},
    {"sat2", emulocke::TrackerStopKind::Boss, "Saturn", "Valor Cavern", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_72, 5, 0, 0, 0},
    {"mars2", emulocke::TrackerStopKind::Boss, "Mars", "Lake Verity", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_73, 5, 0, 0, 0},
    {"route-216", emulocke::TrackerStopKind::Encounter, "Route 216", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_42, 1, nullptr, 0, 0, 0, 0},
    {"route-217", emulocke::TrackerStopKind::Encounter, "Route 217", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_43, 1, nullptr, 0, 0, 0, 0},
    {"acuity-lakefront", emulocke::TrackerStopKind::Encounter, "Acuity Lakefront", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_44, 1, nullptr, 0, 0, 0, 0},
    {"lake-acuity", emulocke::TrackerStopKind::Encounter, "Lake Acuity", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_45, 1, nullptr, 0, 0, 0, 0},
    {"snowpoint-temple", emulocke::TrackerStopKind::Encounter, "Snowpoint Temple", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_46, 1, nullptr, 0, 0, 0, 0},
    {"gym-7", emulocke::TrackerStopKind::Boss, "Candice", "Snowpoint Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_79, 6, 0, 0, 7},
    {"cyr2", emulocke::TrackerStopKind::Boss, "Cyrus", "Galactic HQ", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_80, 5, 0, 0, 0},
    {"sat3", emulocke::TrackerStopKind::Boss, "Saturn", "Galactic HQ", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_81, 6, 0, 0, 0},
    {"mnj", emulocke::TrackerStopKind::Boss, "Mars & Jupiter", "Spear Pillar", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_82, 12, 0, 0, 0},
    {"cyr3", emulocke::TrackerStopKind::Boss, "Cyrus", "Distortion World", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_83, 2, 0, 0, 0},
    {"cyr4", emulocke::TrackerStopKind::Boss, "Cyrus", "Distortion World", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_84, 6, 0, 0, 0},
    {"route-222", emulocke::TrackerStopKind::Encounter, "Route 222", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_47, 1, nullptr, 0, 0, 0, 0},
    {"sunyshore-city", emulocke::TrackerStopKind::Encounter, "Sunyshore City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_48, 1, nullptr, 0, 0, 0, 0},
    {"dahlia", emulocke::TrackerStopKind::Boss, "Arcade Star Dahlia", "Sunyshore City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_87, 6, 0, 0, 0},
    {"gym-8", emulocke::TrackerStopKind::Boss, "Volkner", "Sunyshore Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_88, 6, 0, 0, 8},
    {"route-223", emulocke::TrackerStopKind::Encounter, "Route 223", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_49, 1, nullptr, 0, 0, 0, 0},
    {"pokemon-league", emulocke::TrackerStopKind::Encounter, "Pokémon League", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_50, 1, nullptr, 0, 0, 0, 0},
    {"route-224", emulocke::TrackerStopKind::Encounter, "Route 224", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_renplat_51, 1, nullptr, 0, 0, 0, 0},
    {"l3", emulocke::TrackerStopKind::Boss, "Lucas", "Route 224", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_92, 10, 0, 0, 0},
    {"d3", emulocke::TrackerStopKind::Boss, "Dawn", "Route 224", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_93, 10, 0, 0, 0},
    {"victory-road", emulocke::TrackerStopKind::Encounter, "Victory Road", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"b6", emulocke::TrackerStopKind::Boss, "Barry", "Victory Road", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_95, 12, 0, 0, 0},
    {"e1a", emulocke::TrackerStopKind::Boss, "Aaron (Team A)", "Pokémon League - Round 1", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_96, 6, 0, 0, 0},
    {"e1b", emulocke::TrackerStopKind::Boss, "Aaron (Team B)", "Pokémon League - Round 1", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_97, 6, 0, 0, 0},
    {"e1c", emulocke::TrackerStopKind::Boss, "Aaron (Team C)", "Pokémon League - Round 1", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_98, 6, 0, 0, 0},
    {"e1d", emulocke::TrackerStopKind::Boss, "Aaron (Team D)", "Pokémon League - Round 1", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_99, 6, 0, 0, 0},
    {"e2a", emulocke::TrackerStopKind::Boss, "Bertha (Team A)", "Pokémon League - Round 2", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_100, 6, 0, 0, 0},
    {"e2b", emulocke::TrackerStopKind::Boss, "Bertha (Team B)", "Pokémon League - Round 2", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_101, 6, 0, 0, 0},
    {"e2c", emulocke::TrackerStopKind::Boss, "Bertha (Team C)", "Pokémon League - Round 2", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_102, 6, 0, 0, 0},
    {"e2d", emulocke::TrackerStopKind::Boss, "Bertha (Team D)", "Pokémon League - Round 2", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_103, 6, 0, 0, 0},
    {"e3a", emulocke::TrackerStopKind::Boss, "Flint (Team A)", "Pokémon League - Round 3", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_104, 6, 0, 0, 0},
    {"e3b", emulocke::TrackerStopKind::Boss, "Flint (Team B)", "Pokémon League - Round 3", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_105, 6, 0, 0, 0},
    {"e3c", emulocke::TrackerStopKind::Boss, "Flint (Team C)", "Pokémon League - Round 3", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_106, 6, 0, 0, 0},
    {"e3d", emulocke::TrackerStopKind::Boss, "Flint (Team D)", "Pokémon League - Round 3", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_107, 6, 0, 0, 0},
    {"e4a", emulocke::TrackerStopKind::Boss, "Lucian (Team A)", "Pokémon League - Round 4", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_108, 6, 0, 0, 0},
    {"e4b", emulocke::TrackerStopKind::Boss, "Lucian (Team B)", "Pokémon League - Round 4", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_109, 6, 0, 0, 0},
    {"e4c", emulocke::TrackerStopKind::Boss, "Lucian (Team C)", "Pokémon League - Round 4", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_110, 6, 0, 0, 0},
    {"e4d", emulocke::TrackerStopKind::Boss, "Lucian (Team D)", "Pokémon League - Round 4", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_111, 6, 0, 0, 0},
    {"ca", emulocke::TrackerStopKind::Boss, "Cynthia (Team A)", "Pokémon League - Champion", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_112, 6, 0, 0, 0},
    {"cb", emulocke::TrackerStopKind::Boss, "Cynthia (Team B)", "Pokémon League - Champion", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_113, 6, 0, 0, 0},
    {"cc", emulocke::TrackerStopKind::Boss, "Cynthia (Team C)", "Pokémon League - Champion", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_114, 6, 0, 0, 0},
    {"cd", emulocke::TrackerStopKind::Boss, "Cynthia (Team D)", "Pokémon League - Champion", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_renplat_115, 6, 0, 0, 0}
};

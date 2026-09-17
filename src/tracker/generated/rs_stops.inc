constexpr uint16_t kMet_rs_0[] = {0};
constexpr uint16_t kMet_rs_1[] = {16};
constexpr uint16_t kMet_rs_2[] = {18};
constexpr uint16_t kMet_rs_3[] = {17};
constexpr uint16_t kMet_rs_4[] = {7};
constexpr uint16_t kMet_rs_5[] = {19};
constexpr uint16_t kMet_rs_6[] = {59};
constexpr uint16_t kMet_rs_7[] = {10};
constexpr uint16_t kMet_rs_8[] = {31};
constexpr uint16_t kMet_rs_9[] = {60};
constexpr uint16_t kMet_rs_10[] = {20};
constexpr uint16_t kMet_rs_11[] = {2};
constexpr uint16_t kMet_rs_12[] = {21};
constexpr uint16_t kMet_rs_13[] = {55};
constexpr uint16_t kMet_rs_14[] = {22};
constexpr uint16_t kMet_rs_15[] = {24};
constexpr uint16_t kMet_rs_16[] = {8};
constexpr uint16_t kMet_rs_17[] = {25};
constexpr uint16_t kMet_rs_18[] = {183, 210};
constexpr uint16_t kMet_rs_19[] = {62};
constexpr uint16_t kMet_rs_20[] = {32};
constexpr uint16_t kMet_rs_21[] = {27};
constexpr uint16_t kMet_rs_22[] = {28};
constexpr uint16_t kMet_rs_23[] = {29};
constexpr uint16_t kMet_rs_24[] = {209};
constexpr uint16_t kMet_rs_25[] = {63, 64};
constexpr uint16_t kMet_rs_26[] = {30};
constexpr uint16_t kMet_rs_27[] = {76, 77};
constexpr uint16_t kMet_rs_28[] = {3};
constexpr uint16_t kMet_rs_29[] = {74, 75};
constexpr uint16_t kMet_rs_30[] = {26};
constexpr uint16_t kMet_rs_31[] = {199};
constexpr uint16_t kMet_rs_32[] = {33};
constexpr uint16_t kMet_rs_33[] = {34};
constexpr uint16_t kMet_rs_34[] = {11};
constexpr uint16_t kMet_rs_35[] = {35};
constexpr uint16_t kMet_rs_36[] = {36};
constexpr uint16_t kMet_rs_37[] = {57, 136};
constexpr uint16_t kMet_rs_38[] = {37};
constexpr uint16_t kMet_rs_39[] = {65};
constexpr uint16_t kMet_rs_40[] = {38};
constexpr uint16_t kMet_rs_41[] = {12};
constexpr uint16_t kMet_rs_42[] = {39};
constexpr uint16_t kMet_rs_43[] = {13};
constexpr uint16_t kMet_rs_44[] = {40};
constexpr uint16_t kMet_rs_45[] = {67};
constexpr uint16_t kMet_rs_46[] = {42};
constexpr uint16_t kMet_rs_47[] = {43};
constexpr uint16_t kMet_rs_48[] = {68};
constexpr uint16_t kMet_rs_49[] = {41};
constexpr uint16_t kMet_rs_50[] = {14};
constexpr uint16_t kMet_rs_51[] = {72};
constexpr uint16_t kMet_rs_52[] = {23};
constexpr uint16_t kMet_rs_53[] = {61};
constexpr uint16_t kMet_rs_54[] = {44};
constexpr uint16_t kMet_rs_55[] = {45};
constexpr uint16_t kMet_rs_56[] = {71};
constexpr uint16_t kMet_rs_57[] = {46};
constexpr uint16_t kMet_rs_58[] = {6};
constexpr uint16_t kMet_rs_59[] = {47};
constexpr uint16_t kMet_rs_60[] = {48};
constexpr uint16_t kMet_rs_61[] = {49};
constexpr uint16_t kMet_rs_62[] = {15};
constexpr uint16_t kMet_rs_63[] = {70, 132};
constexpr uint16_t kMet_rs_64[] = {85};
constexpr uint16_t kMet_rs_65[] = {202};
constexpr uint16_t kStarters_rs[] = {252, 258, 255};
constexpr emulocke::TrackerStop kStops_rs[] = {
    {"starter", emulocke::TrackerStopKind::Encounter, "Starter", "", emulocke::BossKind::None, emulocke::CatchKind::Starter, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"littleroot-town", emulocke::TrackerStopKind::Encounter, "Littleroot Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_0, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-101", emulocke::TrackerStopKind::Encounter, "Route 101", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_1, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-103", emulocke::TrackerStopKind::Encounter, "Route 103", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_2, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"r1", emulocke::TrackerStopKind::Boss, "May", "Route 103", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_4, 3, 130, 3, 0, 1, false, "", "", false},
    {"route-102", emulocke::TrackerStopKind::Encounter, "Route 102", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_3, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"petalburg-city", emulocke::TrackerStopKind::Encounter, "Petalburg City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_4, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-104", emulocke::TrackerStopKind::Encounter, "Route 104", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_5, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"petalburg-woods", emulocke::TrackerStopKind::Encounter, "Petalburg Woods", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_6, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"rustboro-city", emulocke::TrackerStopKind::Encounter, "Rustboro City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_7, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-1", emulocke::TrackerStopKind::Boss, "Roxanne", "Rustboro Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_10, 2, 2055, 0, 1, 1, false, "", "", false},
    {"route-116", emulocke::TrackerStopKind::Encounter, "Route 116", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_8, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"rusturf-tunnel", emulocke::TrackerStopKind::Encounter, "Rusturf Tunnel", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_9, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-105", emulocke::TrackerStopKind::Encounter, "Route 105", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_10, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"dewford-town", emulocke::TrackerStopKind::Encounter, "Dewford Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_11, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-2", emulocke::TrackerStopKind::Boss, "Brawly", "Dewford Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_15, 2, 2056, 0, 2, 1, false, "", "", false},
    {"route-106", emulocke::TrackerStopKind::Encounter, "Route 106", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_12, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"granite-cave", emulocke::TrackerStopKind::Encounter, "Granite Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_13, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-107", emulocke::TrackerStopKind::Encounter, "Route 107", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_14, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-109", emulocke::TrackerStopKind::Encounter, "Route 109", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_15, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"slateport-city", emulocke::TrackerStopKind::Encounter, "Slateport City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_16, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-110", emulocke::TrackerStopKind::Encounter, "Route 110", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_17, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"r2", emulocke::TrackerStopKind::Boss, "May", "Route 110", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_22, 9, 125, 3, 0, 1, false, "", "", false},
    {"altering-cave", emulocke::TrackerStopKind::Encounter, "Altering Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_18, 2, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"new-mauville", emulocke::TrackerStopKind::Encounter, "New Mauville", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_19, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"w1", emulocke::TrackerStopKind::Boss, "Wally", "Mauville City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_25, 1, 190, 0, 0, 1, false, "", "", false},
    {"gym-3", emulocke::TrackerStopKind::Boss, "Wattson", "Mauville City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_26, 3, 2057, 0, 3, 1, false, "", "", false},
    {"route-117", emulocke::TrackerStopKind::Encounter, "Route 117", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_20, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-112", emulocke::TrackerStopKind::Encounter, "Route 112", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_21, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-113", emulocke::TrackerStopKind::Encounter, "Route 113", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_22, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-114", emulocke::TrackerStopKind::Encounter, "Route 114", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_23, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"desert-underpass", emulocke::TrackerStopKind::Encounter, "Desert Underpass", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_24, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"meteor-falls", emulocke::TrackerStopKind::Encounter, "Meteor Falls", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_25, 2, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-115", emulocke::TrackerStopKind::Encounter, "Route 115", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_26, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"jagged-pass", emulocke::TrackerStopKind::Encounter, "Jagged Pass", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_27, 2, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"ruby1", emulocke::TrackerStopKind::Boss, "Tabitha", "Mt. Chimney", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_35, 3, 139, 0, 0, 1, false, "", "", false},
    {"max1", emulocke::TrackerStopKind::Boss, "Maxie", "Mt. Chimney", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_36, 3, 139, 0, 0, 1, false, "", "", false},
    {"lavaridge-town", emulocke::TrackerStopKind::Encounter, "Lavaridge Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_28, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-4", emulocke::TrackerStopKind::Boss, "Flannery", "Lavaridge Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_38, 3, 2058, 0, 4, 1, false, "", "", false},
    {"fiery-path", emulocke::TrackerStopKind::Encounter, "Fiery Path", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_29, 2, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-111", emulocke::TrackerStopKind::Encounter, "Route 111", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_30, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"mirage-tower", emulocke::TrackerStopKind::Encounter, "Mirage Tower", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_31, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-5", emulocke::TrackerStopKind::Boss, "Norman", "Petalburg Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_42, 3, 2059, 0, 5, 1, false, "", "", false},
    {"route-118", emulocke::TrackerStopKind::Encounter, "Route 118", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_32, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-119", emulocke::TrackerStopKind::Encounter, "Route 119", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_33, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"ruby2", emulocke::TrackerStopKind::Boss, "Courtney", "Weather Institute", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_45, 2, 893, 0, 0, 1, false, "", "", false},
    {"r3", emulocke::TrackerStopKind::Boss, "May", "Weather Institute", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_46, 9, 851, 0, 0, 1, false, "", "", false},
    {"fortree-city", emulocke::TrackerStopKind::Encounter, "Fortree City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_34, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-6", emulocke::TrackerStopKind::Boss, "Winona", "Fortree City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_48, 4, 2060, 0, 6, 1, false, "", "", false},
    {"route-120", emulocke::TrackerStopKind::Encounter, "Route 120", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_35, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-121", emulocke::TrackerStopKind::Encounter, "Route 121", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_36, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"safari-zone", emulocke::TrackerStopKind::Encounter, "Safari Zone", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_37, 2, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-122", emulocke::TrackerStopKind::Encounter, "Route 122", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_38, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"mt-pyre", emulocke::TrackerStopKind::Encounter, "Mt. Pyre", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_39, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-123", emulocke::TrackerStopKind::Encounter, "Route 123", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_40, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"lilycove-city", emulocke::TrackerStopKind::Encounter, "Lilycove City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_41, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"r4", emulocke::TrackerStopKind::Boss, "May", "Lilycove City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_56, 10, 971, 0, 0, 1, false, "", "", false},
    {"ruby3", emulocke::TrackerStopKind::Boss, "Tabitha", "Team Magma Hideout", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_57, 3, 139, 0, 0, 1, false, "", "", false},
    {"route-124", emulocke::TrackerStopKind::Encounter, "Route 124", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_42, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"mossdeep-city", emulocke::TrackerStopKind::Encounter, "Mossdeep City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_43, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-7", emulocke::TrackerStopKind::Boss, "Tate & Liza", "Mossdeep City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_60, 2, 2061, 0, 7, 2, false, "", "", false},
    {"route-125", emulocke::TrackerStopKind::Encounter, "Route 125", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_44, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"shoal-cave", emulocke::TrackerStopKind::Encounter, "Shoal Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_45, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-127", emulocke::TrackerStopKind::Encounter, "Route 127", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_46, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-128", emulocke::TrackerStopKind::Encounter, "Route 128", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_47, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"seafloor-cavern", emulocke::TrackerStopKind::Encounter, "Seafloor Cavern", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_48, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"ruby4", emulocke::TrackerStopKind::Boss, "Courtney", "Seafloor Cavern", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_66, 2, 829, 0, 0, 1, false, "", "", false},
    {"max2", emulocke::TrackerStopKind::Boss, "Maxie", "Seafloor Cavern", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_67, 3, 829, 0, 0, 1, false, "", "", false},
    {"route-126", emulocke::TrackerStopKind::Encounter, "Route 126", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_49, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"sootopolis-city", emulocke::TrackerStopKind::Encounter, "Sootopolis City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_50, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"cave-of-origin", emulocke::TrackerStopKind::Encounter, "Cave of Origin", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_51, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-8", emulocke::TrackerStopKind::Boss, "Wallace", "Sootopolis Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_71, 5, 2062, 0, 8, 1, false, "", "", false},
    {"route-108", emulocke::TrackerStopKind::Encounter, "Route 108", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_52, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"abandoned-ship", emulocke::TrackerStopKind::Encounter, "Abandoned Ship", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_53, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-129", emulocke::TrackerStopKind::Encounter, "Route 129", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_54, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-130", emulocke::TrackerStopKind::Encounter, "Route 130", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_55, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"mirage-island", emulocke::TrackerStopKind::Encounter, "Mirage Island", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_56, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-131", emulocke::TrackerStopKind::Encounter, "Route 131", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_57, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"pacifidlog-town", emulocke::TrackerStopKind::Encounter, "Pacifidlog Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_58, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-132", emulocke::TrackerStopKind::Encounter, "Route 132", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_59, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-133", emulocke::TrackerStopKind::Encounter, "Route 133", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_60, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-134", emulocke::TrackerStopKind::Encounter, "Route 134", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_61, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"ever-grande-city", emulocke::TrackerStopKind::Encounter, "Ever Grande City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_62, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"victory-road", emulocke::TrackerStopKind::Encounter, "Victory Road", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_63, 2, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"w2", emulocke::TrackerStopKind::Boss, "Wally", "Victory Road", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_84, 5, 126, 0, 0, 1, false, "", "", false},
    {"e1", emulocke::TrackerStopKind::Boss, "Sidney", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_85, 5, 1245, 0, 0, 1, false, "", "", false},
    {"e2", emulocke::TrackerStopKind::Boss, "Phoebe", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_86, 5, 1246, 0, 0, 1, false, "", "", false},
    {"e3", emulocke::TrackerStopKind::Boss, "Glacia", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_87, 5, 1247, 0, 0, 1, false, "", "", false},
    {"e4", emulocke::TrackerStopKind::Boss, "Drake", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_88, 5, 1248, 0, 0, 1, false, "", "", false},
    {"c", emulocke::TrackerStopKind::Boss, "Steven", "Pokémon League Champion", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_rs_89, 6, 2148, 0, 0, 1, false, "", "", false},
    {"sky-pillar", emulocke::TrackerStopKind::Encounter, "Sky Pillar", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_64, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"artisan-cave", emulocke::TrackerStopKind::Encounter, "Artisan Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_rs_65, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false}
};

constexpr uint16_t kMet_em_0[] = {0};
constexpr uint16_t kMet_em_1[] = {16};
constexpr uint16_t kMet_em_2[] = {18};
constexpr uint16_t kMet_em_3[] = {17};
constexpr uint16_t kMet_em_4[] = {7};
constexpr uint16_t kMet_em_5[] = {19};
constexpr uint16_t kMet_em_6[] = {59};
constexpr uint16_t kMet_em_7[] = {10};
constexpr uint16_t kMet_em_8[] = {20};
constexpr uint16_t kMet_em_9[] = {31};
constexpr uint16_t kMet_em_10[] = {60};
constexpr uint16_t kMet_em_11[] = {2};
constexpr uint16_t kMet_em_12[] = {21};
constexpr uint16_t kMet_em_13[] = {55};
constexpr uint16_t kMet_em_14[] = {22};
constexpr uint16_t kMet_em_15[] = {8};
constexpr uint16_t kMet_em_16[] = {25};
constexpr uint16_t kMet_em_17[] = {183, 210};
constexpr uint16_t kMet_em_18[] = {32};
constexpr uint16_t kMet_em_19[] = {27};
constexpr uint16_t kMet_em_20[] = {28};
constexpr uint16_t kMet_em_21[] = {29};
constexpr uint16_t kMet_em_22[] = {209};
constexpr uint16_t kMet_em_23[] = {63, 64};
constexpr uint16_t kMet_em_24[] = {30};
constexpr uint16_t kMet_em_25[] = {76, 77};
constexpr uint16_t kMet_em_26[] = {3};
constexpr uint16_t kMet_em_27[] = {74, 75};
constexpr uint16_t kMet_em_28[] = {26};
constexpr uint16_t kMet_em_29[] = {199};
constexpr uint16_t kMet_em_30[] = {62};
constexpr uint16_t kMet_em_31[] = {33};
constexpr uint16_t kMet_em_32[] = {34};
constexpr uint16_t kMet_em_33[] = {11};
constexpr uint16_t kMet_em_34[] = {35};
constexpr uint16_t kMet_em_35[] = {36};
constexpr uint16_t kMet_em_36[] = {57, 136};
constexpr uint16_t kMet_em_37[] = {37};
constexpr uint16_t kMet_em_38[] = {65};
constexpr uint16_t kMet_em_39[] = {38};
constexpr uint16_t kMet_em_40[] = {12};
constexpr uint16_t kMet_em_41[] = {39};
constexpr uint16_t kMet_em_42[] = {13};
constexpr uint16_t kMet_em_43[] = {40};
constexpr uint16_t kMet_em_44[] = {67};
constexpr uint16_t kMet_em_45[] = {42};
constexpr uint16_t kMet_em_46[] = {43};
constexpr uint16_t kMet_em_47[] = {68};
constexpr uint16_t kMet_em_48[] = {41};
constexpr uint16_t kMet_em_49[] = {14};
constexpr uint16_t kMet_em_50[] = {72};
constexpr uint16_t kMet_em_51[] = {44};
constexpr uint16_t kMet_em_52[] = {45};
constexpr uint16_t kMet_em_53[] = {46};
constexpr uint16_t kMet_em_54[] = {85};
constexpr uint16_t kMet_em_55[] = {6};
constexpr uint16_t kMet_em_56[] = {71};
constexpr uint16_t kMet_em_57[] = {23};
constexpr uint16_t kMet_em_58[] = {61};
constexpr uint16_t kMet_em_59[] = {24};
constexpr uint16_t kMet_em_60[] = {47};
constexpr uint16_t kMet_em_61[] = {48};
constexpr uint16_t kMet_em_62[] = {49};
constexpr uint16_t kMet_em_63[] = {15};
constexpr uint16_t kMet_em_64[] = {70, 132};
constexpr uint16_t kMet_em_65[] = {58};
constexpr uint16_t kMet_em_66[] = {202};
constexpr uint16_t kStarters_em[] = {252, 258, 255};
constexpr emulocke::TrackerStop kStops_em[] = {
    {"starter", emulocke::TrackerStopKind::Encounter, "Starter", "", emulocke::BossKind::None, emulocke::CatchKind::Starter, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"littleroot-town", emulocke::TrackerStopKind::Encounter, "Littleroot Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_0, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-101", emulocke::TrackerStopKind::Encounter, "Route 101", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_1, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-103", emulocke::TrackerStopKind::Encounter, "Route 103", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_2, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"r1", emulocke::TrackerStopKind::Boss, "May", "Route 103", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_em_4, 3, 125, 3, 0, 1, false, "", "", false},
    {"route-102", emulocke::TrackerStopKind::Encounter, "Route 102", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_3, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"petalburg-city", emulocke::TrackerStopKind::Encounter, "Petalburg City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_4, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-104", emulocke::TrackerStopKind::Encounter, "Route 104", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_5, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"petalburg-woods", emulocke::TrackerStopKind::Encounter, "Petalburg Woods", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_6, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"rustboro-city", emulocke::TrackerStopKind::Encounter, "Rustboro City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_7, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-1", emulocke::TrackerStopKind::Boss, "Roxanne", "Rustboro Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_em_10, 3, 2151, 0, 1, 1, false, "", "", false},
    {"r2", emulocke::TrackerStopKind::Boss, "May", "Rustboro City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_em_11, 6, 211, 3, 0, 1, false, "", "", false},
    {"route-105", emulocke::TrackerStopKind::Encounter, "Route 105", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_8, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-116", emulocke::TrackerStopKind::Encounter, "Route 116", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_9, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"rusturf-tunnel", emulocke::TrackerStopKind::Encounter, "Rusturf Tunnel", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_10, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"dewford-town", emulocke::TrackerStopKind::Encounter, "Dewford Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_11, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-2", emulocke::TrackerStopKind::Boss, "Brawly", "Dewford Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_em_16, 3, 2152, 0, 2, 1, false, "", "", false},
    {"route-106", emulocke::TrackerStopKind::Encounter, "Route 106", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_12, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"granite-cave", emulocke::TrackerStopKind::Encounter, "Granite Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_13, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-107", emulocke::TrackerStopKind::Encounter, "Route 107", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_14, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"slateport-city", emulocke::TrackerStopKind::Encounter, "Slateport City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_15, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-110", emulocke::TrackerStopKind::Encounter, "Route 110", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_16, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"r3", emulocke::TrackerStopKind::Boss, "May", "Route 110", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_em_22, 9, 125, 3, 0, 1, false, "", "", false},
    {"altering-cave", emulocke::TrackerStopKind::Encounter, "Altering Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_17, 2, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"w1", emulocke::TrackerStopKind::Boss, "Wally", "Mauville City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_em_24, 1, 190, 0, 0, 1, false, "", "", false},
    {"gym-3", emulocke::TrackerStopKind::Boss, "Wattson", "Mauville City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_em_25, 4, 2153, 0, 3, 1, false, "", "", false},
    {"route-117", emulocke::TrackerStopKind::Encounter, "Route 117", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_18, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-112", emulocke::TrackerStopKind::Encounter, "Route 112", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_19, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"mt1", emulocke::TrackerStopKind::Boss, "Tabitha", "Mt. Chimney", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_em_28, 4, 139, 0, 0, 1, false, "", "", false},
    {"route-113", emulocke::TrackerStopKind::Encounter, "Route 113", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_20, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-114", emulocke::TrackerStopKind::Encounter, "Route 114", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_21, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"desert-underpass", emulocke::TrackerStopKind::Encounter, "Desert Underpass", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_22, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"meteor-falls", emulocke::TrackerStopKind::Encounter, "Meteor Falls", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_23, 2, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-115", emulocke::TrackerStopKind::Encounter, "Route 115", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_24, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"jagged-pass", emulocke::TrackerStopKind::Encounter, "Jagged Pass", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_25, 2, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"lavaridge-town", emulocke::TrackerStopKind::Encounter, "Lavaridge Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_26, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-4", emulocke::TrackerStopKind::Boss, "Flannery", "Lavaridge Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_em_36, 4, 2154, 0, 4, 1, false, "", "", false},
    {"fiery-path", emulocke::TrackerStopKind::Encounter, "Fiery Path", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_27, 2, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-111", emulocke::TrackerStopKind::Encounter, "Route 111", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_28, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"mirage-tower", emulocke::TrackerStopKind::Encounter, "Mirage Tower", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_29, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-5", emulocke::TrackerStopKind::Boss, "Norman", "Petalburg Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_em_40, 4, 2155, 0, 5, 1, false, "", "", false},
    {"new-mauville", emulocke::TrackerStopKind::Encounter, "New Mauville", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_30, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-118", emulocke::TrackerStopKind::Encounter, "Route 118", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_31, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-119", emulocke::TrackerStopKind::Encounter, "Route 119", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_32, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"as1", emulocke::TrackerStopKind::Boss, "Shelly", "Weather Institute", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_em_44, 2, 1312, 0, 0, 1, false, "", "", false},
    {"r4", emulocke::TrackerStopKind::Boss, "May", "Weather Institute", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_em_45, 9, 851, 0, 0, 1, false, "", "", false},
    {"fortree-city", emulocke::TrackerStopKind::Encounter, "Fortree City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_33, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-120", emulocke::TrackerStopKind::Encounter, "Route 120", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_34, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-6", emulocke::TrackerStopKind::Boss, "Winona", "Fortree City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_em_48, 5, 2156, 0, 6, 1, false, "", "", false},
    {"route-121", emulocke::TrackerStopKind::Encounter, "Route 121", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_35, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"safari-zone", emulocke::TrackerStopKind::Encounter, "Safari Zone", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_36, 2, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-122", emulocke::TrackerStopKind::Encounter, "Route 122", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_37, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"mt-pyre", emulocke::TrackerStopKind::Encounter, "Mt. Pyre", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_38, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-123", emulocke::TrackerStopKind::Encounter, "Route 123", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_39, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"team-magma-hideout", emulocke::TrackerStopKind::Encounter, "Team Magma Hideout", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"mt2", emulocke::TrackerStopKind::Boss, "Tabitha", "Team Magma Hideout", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_em_55, 4, 117, 0, 0, 1, false, "", "", false},
    {"mtmax", emulocke::TrackerStopKind::Boss, "Maxie", "Team Magma Hideout", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_em_56, 3, 117, 0, 0, 1, false, "", "", false},
    {"lilycove-city", emulocke::TrackerStopKind::Encounter, "Lilycove City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_40, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"r5", emulocke::TrackerStopKind::Boss, "May", "Lilycove City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_em_58, 10, 971, 0, 0, 1, false, "", "", false},
    {"am1", emulocke::TrackerStopKind::Boss, "Matt", "Team Aqua Hideout", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_em_59, 3, 452, 0, 0, 1, false, "", "", false},
    {"route-124", emulocke::TrackerStopKind::Encounter, "Route 124", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_41, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"mossdeep-city", emulocke::TrackerStopKind::Encounter, "Mossdeep City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_42, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-7", emulocke::TrackerStopKind::Boss, "Tate & Liza", "Mossdeep City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_em_62, 4, 2157, 0, 7, 2, false, "", "", false},
    {"mtmaxt", emulocke::TrackerStopKind::Boss, "Maxie & Tabitha", "Mossdeep Space Center", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_em_63, 6, 117, 0, 0, 1, false, "", "", false},
    {"route-125", emulocke::TrackerStopKind::Encounter, "Route 125", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_43, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"shoal-cave", emulocke::TrackerStopKind::Encounter, "Shoal Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_44, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-127", emulocke::TrackerStopKind::Encounter, "Route 127", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_45, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-128", emulocke::TrackerStopKind::Encounter, "Route 128", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_46, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"seafloor-cavern", emulocke::TrackerStopKind::Encounter, "Seafloor Cavern", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_47, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"as2", emulocke::TrackerStopKind::Boss, "Shelly", "Seafloor Cavern", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_em_69, 2, 1313, 0, 0, 1, false, "", "", false},
    {"aqarc", emulocke::TrackerStopKind::Boss, "Archie", "Seafloor Cavern", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_em_70, 3, 1314, 0, 0, 1, false, "", "", false},
    {"route-126", emulocke::TrackerStopKind::Encounter, "Route 126", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_48, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"sootopolis-city", emulocke::TrackerStopKind::Encounter, "Sootopolis City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_49, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-8", emulocke::TrackerStopKind::Boss, "Juan", "Sootopolis Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_em_73, 5, 2158, 0, 8, 1, false, "", "", false},
    {"cave-of-origin", emulocke::TrackerStopKind::Encounter, "Cave of Origin", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_50, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-129", emulocke::TrackerStopKind::Encounter, "Route 129", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_51, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-130", emulocke::TrackerStopKind::Encounter, "Route 130", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_52, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-131", emulocke::TrackerStopKind::Encounter, "Route 131", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_53, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"sky-pillar", emulocke::TrackerStopKind::Encounter, "Sky Pillar", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_54, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"pacifidlog-town", emulocke::TrackerStopKind::Encounter, "Pacifidlog Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_55, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"mirage-island", emulocke::TrackerStopKind::Encounter, "Mirage Island", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_56, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-108", emulocke::TrackerStopKind::Encounter, "Route 108", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_57, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"abandoned-ship", emulocke::TrackerStopKind::Encounter, "Abandoned Ship", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_58, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-109", emulocke::TrackerStopKind::Encounter, "Route 109", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_59, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-132", emulocke::TrackerStopKind::Encounter, "Route 132", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_60, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-133", emulocke::TrackerStopKind::Encounter, "Route 133", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_61, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-134", emulocke::TrackerStopKind::Encounter, "Route 134", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_62, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"ever-grande-city", emulocke::TrackerStopKind::Encounter, "Ever Grande City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_63, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"victory-road", emulocke::TrackerStopKind::Encounter, "Victory Road", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_64, 2, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"w2", emulocke::TrackerStopKind::Boss, "Wally", "Victory Road", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_em_89, 5, 126, 0, 0, 1, false, "", "", false},
    {"e1", emulocke::TrackerStopKind::Boss, "Sidney", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_em_90, 5, 1275, 0, 0, 1, false, "", "", false},
    {"e2", emulocke::TrackerStopKind::Boss, "Phoebe", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_em_91, 5, 1276, 0, 0, 1, false, "", "", false},
    {"e3", emulocke::TrackerStopKind::Boss, "Glacia", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_em_92, 5, 1277, 0, 0, 1, false, "", "", false},
    {"e4", emulocke::TrackerStopKind::Boss, "Drake", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_em_93, 5, 1278, 0, 0, 1, false, "", "", false},
    {"c1", emulocke::TrackerStopKind::Boss, "Wallace", "Pokémon League Champion", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_em_94, 6, 2148, 0, 0, 1, false, "", "", false},
    {"c2", emulocke::TrackerStopKind::Boss, "Steven", "Meteor Falls Champion", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_em_95, 6, 1272, 0, 0, 1, false, "", "", false},
    {"ss-tidal", emulocke::TrackerStopKind::Encounter, "S.S. Tidal", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"battle-frontier", emulocke::TrackerStopKind::Encounter, "Battle Frontier", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_65, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"artisan-cave", emulocke::TrackerStopKind::Encounter, "Artisan Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_em_66, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false}
};

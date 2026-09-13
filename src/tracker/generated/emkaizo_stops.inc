constexpr uint16_t kMet_emkaizo_0[] = {0};
constexpr uint16_t kMet_emkaizo_1[] = {18};
constexpr uint16_t kMet_emkaizo_2[] = {1};
constexpr uint16_t kMet_emkaizo_3[] = {17};
constexpr uint16_t kMet_emkaizo_4[] = {7};
constexpr uint16_t kMet_emkaizo_5[] = {59};
constexpr uint16_t kMet_emkaizo_6[] = {10};
constexpr uint16_t kMet_emkaizo_7[] = {30};
constexpr uint16_t kMet_emkaizo_8[] = {31};
constexpr uint16_t kMet_emkaizo_9[] = {60};
constexpr uint16_t kMet_emkaizo_10[] = {21};
constexpr uint16_t kMet_emkaizo_11[] = {22};
constexpr uint16_t kMet_emkaizo_12[] = {2};
constexpr uint16_t kMet_emkaizo_13[] = {55};
constexpr uint16_t kMet_emkaizo_14[] = {24};
constexpr uint16_t kMet_emkaizo_15[] = {9};
constexpr uint16_t kMet_emkaizo_16[] = {25};
constexpr uint16_t kMet_emkaizo_17[] = {33};
constexpr uint16_t kMet_emkaizo_18[] = {8};
constexpr uint16_t kMet_emkaizo_19[] = {32};
constexpr uint16_t kMet_emkaizo_20[] = {5};
constexpr uint16_t kMet_emkaizo_21[] = {74, 75};
constexpr uint16_t kMet_emkaizo_22[] = {28};
constexpr uint16_t kMet_emkaizo_23[] = {4};
constexpr uint16_t kMet_emkaizo_24[] = {29};
constexpr uint16_t kMet_emkaizo_25[] = {76, 77};
constexpr uint16_t kMet_emkaizo_26[] = {3};
constexpr uint16_t kMet_emkaizo_27[] = {26};
constexpr uint16_t kMet_emkaizo_28[] = {199};
constexpr uint16_t kMet_emkaizo_29[] = {20};
constexpr uint16_t kMet_emkaizo_30[] = {23};
constexpr uint16_t kMet_emkaizo_31[] = {49};
constexpr uint16_t kMet_emkaizo_32[] = {62};
constexpr uint16_t kMet_emkaizo_33[] = {34};
constexpr uint16_t kMet_emkaizo_34[] = {35};
constexpr uint16_t kMet_emkaizo_35[] = {80};
constexpr uint16_t kMet_emkaizo_36[] = {36};
constexpr uint16_t kMet_emkaizo_37[] = {12};
constexpr uint16_t kMet_emkaizo_38[] = {57, 136};
constexpr uint16_t kMet_emkaizo_39[] = {37};
constexpr uint16_t kMet_emkaizo_40[] = {65};
constexpr uint16_t kMet_emkaizo_41[] = {198};
constexpr uint16_t kMet_emkaizo_42[] = {39};
constexpr uint16_t kMet_emkaizo_43[] = {13};
constexpr uint16_t kMet_emkaizo_44[] = {40};
constexpr uint16_t kMet_emkaizo_45[] = {67};
constexpr uint16_t kMet_emkaizo_46[] = {42};
constexpr uint16_t kMet_emkaizo_47[] = {43};
constexpr uint16_t kMet_emkaizo_48[] = {68};
constexpr uint16_t kMet_emkaizo_49[] = {41};
constexpr uint16_t kMet_emkaizo_50[] = {14};
constexpr uint16_t kMet_emkaizo_51[] = {44};
constexpr uint16_t kMet_emkaizo_52[] = {45};
constexpr uint16_t kMet_emkaizo_53[] = {46};
constexpr uint16_t kMet_emkaizo_54[] = {6};
constexpr uint16_t kMet_emkaizo_55[] = {85};
constexpr uint16_t kMet_emkaizo_56[] = {63, 64};
constexpr uint16_t kMet_emkaizo_57[] = {47};
constexpr uint16_t kMet_emkaizo_58[] = {48};
constexpr uint16_t kMet_emkaizo_59[] = {38};
constexpr uint16_t kMet_emkaizo_60[] = {15};
constexpr uint16_t kMet_emkaizo_61[] = {70, 132};
constexpr uint16_t kStarters_emkaizo[] = {252, 258, 255};
constexpr emulocke::TrackerStop kStops_emkaizo[] = {
    {"starter", emulocke::TrackerStopKind::Encounter, "Starter", "", emulocke::BossKind::None, emulocke::CatchKind::Starter, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"littleroot-town", emulocke::TrackerStopKind::Encounter, "Littleroot Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_0, 1, nullptr, 0, 0, 0, 0},
    {"route-103", emulocke::TrackerStopKind::Encounter, "Route 103", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_1, 1, nullptr, 0, 0, 0, 0},
    {"oldale-town", emulocke::TrackerStopKind::Encounter, "Oldale Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_2, 1, nullptr, 0, 0, 0, 0},
    {"route-102", emulocke::TrackerStopKind::Encounter, "Route 102", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_3, 1, nullptr, 0, 0, 0, 0},
    {"petalburg-city", emulocke::TrackerStopKind::Encounter, "Petalburg City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_4, 1, nullptr, 0, 0, 0, 0},
    {"route-104-south", emulocke::TrackerStopKind::Encounter, "Route 104 (South)", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"red1", emulocke::TrackerStopKind::Boss, "Red", "Route 104 (North)", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_7, 5, 0, 0, 0},
    {"petalburg-woods", emulocke::TrackerStopKind::Encounter, "Petalburg Woods", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_5, 1, nullptr, 0, 0, 0, 0},
    {"rustboro-city", emulocke::TrackerStopKind::Encounter, "Rustboro City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_6, 1, nullptr, 0, 0, 0, 0},
    {"b0", emulocke::TrackerStopKind::Boss, "Brandan (optional)", "Rustboro City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_10, 12, 0, 0, 0},
    {"r0", emulocke::TrackerStopKind::Boss, "May (optional)", "Rustboro City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_11, 12, 0, 0, 0},
    {"gym-1", emulocke::TrackerStopKind::Boss, "Roxanne", "Rustboro Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_12, 6, 2151, 0, 1},
    {"route-115", emulocke::TrackerStopKind::Encounter, "Route 115", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_7, 1, nullptr, 0, 0, 0, 0},
    {"mt1", emulocke::TrackerStopKind::Boss, "Magma Admin Tabitha", "Mt. Chimney", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_14, 6, 0, 0, 0},
    {"mtmax1", emulocke::TrackerStopKind::Boss, "Magma Leader Maxie", "Mt. Chimney", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_15, 6, 0, 0, 0},
    {"route-116", emulocke::TrackerStopKind::Encounter, "Route 116", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_8, 1, nullptr, 0, 0, 0, 0},
    {"rusturf-tunnel", emulocke::TrackerStopKind::Encounter, "Rusturf Tunnel", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_9, 1, nullptr, 0, 0, 0, 0},
    {"route-106", emulocke::TrackerStopKind::Encounter, "Route 106", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_10, 1, nullptr, 0, 0, 0, 0},
    {"route-107", emulocke::TrackerStopKind::Encounter, "Route 107", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_11, 1, nullptr, 0, 0, 0, 0},
    {"dewford-town", emulocke::TrackerStopKind::Encounter, "Dewford Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_12, 1, nullptr, 0, 0, 0, 0},
    {"gym-2", emulocke::TrackerStopKind::Boss, "Brawly", "Dewford Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_21, 6, 2152, 0, 2},
    {"granite-cave", emulocke::TrackerStopKind::Encounter, "Granite Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_13, 1, nullptr, 0, 0, 0, 0},
    {"route-109", emulocke::TrackerStopKind::Encounter, "Route 109", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_14, 1, nullptr, 0, 0, 0, 0},
    {"mauville-city", emulocke::TrackerStopKind::Encounter, "Mauville City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_15, 1, nullptr, 0, 0, 0, 0},
    {"w1", emulocke::TrackerStopKind::Boss, "Wally", "Mauville City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_25, 1, 0, 0, 0},
    {"gym-3", emulocke::TrackerStopKind::Boss, "Wattson", "Mauville Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_26, 6, 2153, 0, 3},
    {"route-110", emulocke::TrackerStopKind::Encounter, "Route 110", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_16, 1, nullptr, 0, 0, 0, 0},
    {"b1", emulocke::TrackerStopKind::Boss, "Brendan", "Route 110", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_28, 12, 0, 0, 0},
    {"r1", emulocke::TrackerStopKind::Boss, "May", "Route 110", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_29, 12, 0, 0, 0},
    {"route-118", emulocke::TrackerStopKind::Encounter, "Route 118", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_17, 1, nullptr, 0, 0, 0, 0},
    {"slateport-city", emulocke::TrackerStopKind::Encounter, "Slateport City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_18, 1, nullptr, 0, 0, 0, 0},
    {"route-117", emulocke::TrackerStopKind::Encounter, "Route 117", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_19, 1, nullptr, 0, 0, 0, 0},
    {"verdanturf-town", emulocke::TrackerStopKind::Encounter, "Verdanturf Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_20, 1, nullptr, 0, 0, 0, 0},
    {"route-112-south", emulocke::TrackerStopKind::Encounter, "Route 112 (South)", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"fiery-path", emulocke::TrackerStopKind::Encounter, "Fiery Path", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_21, 2, nullptr, 0, 0, 0, 0},
    {"route-113", emulocke::TrackerStopKind::Encounter, "Route 113", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_22, 1, nullptr, 0, 0, 0, 0},
    {"red2", emulocke::TrackerStopKind::Boss, "Red", "Route 113", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_37, 6, 0, 0, 0},
    {"fallarbor-town", emulocke::TrackerStopKind::Encounter, "Fallarbor Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_23, 1, nullptr, 0, 0, 0, 0},
    {"route-114", emulocke::TrackerStopKind::Encounter, "Route 114", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_24, 1, nullptr, 0, 0, 0, 0},
    {"jagged-pass", emulocke::TrackerStopKind::Encounter, "Jagged Pass", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_25, 2, nullptr, 0, 0, 0, 0},
    {"lavaridge-town", emulocke::TrackerStopKind::Encounter, "Lavaridge Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_26, 1, nullptr, 0, 0, 0, 0},
    {"gym-4", emulocke::TrackerStopKind::Boss, "Flannery", "Lavaridge Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_42, 6, 2154, 0, 4},
    {"route-111", emulocke::TrackerStopKind::Encounter, "Route 111", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_27, 1, nullptr, 0, 0, 0, 0},
    {"mirage-tower", emulocke::TrackerStopKind::Encounter, "Mirage Tower", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_28, 1, nullptr, 0, 0, 0, 0},
    {"gym-5", emulocke::TrackerStopKind::Boss, "Norman", "Petalburg Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_45, 6, 2155, 0, 5},
    {"route-105", emulocke::TrackerStopKind::Encounter, "Route 105", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_29, 1, nullptr, 0, 0, 0, 0},
    {"route-108", emulocke::TrackerStopKind::Encounter, "Route 108", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_30, 1, nullptr, 0, 0, 0, 0},
    {"route-134", emulocke::TrackerStopKind::Encounter, "Route 134", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_31, 1, nullptr, 0, 0, 0, 0},
    {"new-mauville", emulocke::TrackerStopKind::Encounter, "New Mauville", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_32, 1, nullptr, 0, 0, 0, 0},
    {"route-119", emulocke::TrackerStopKind::Encounter, "Route 119", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_33, 1, nullptr, 0, 0, 0, 0},
    {"as1", emulocke::TrackerStopKind::Boss, "Aqua Admin Shelly", "Weather Institute", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_51, 6, 0, 0, 0},
    {"b2", emulocke::TrackerStopKind::Boss, "Brendan", "Weather Institute", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_52, 9, 0, 0, 0},
    {"r2", emulocke::TrackerStopKind::Boss, "May", "Weather Institute", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_53, 9, 0, 0, 0},
    {"foretree-city", emulocke::TrackerStopKind::Encounter, "Foretree City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"route-120", emulocke::TrackerStopKind::Encounter, "Route 120", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_34, 1, nullptr, 0, 0, 0, 0},
    {"gym-6", emulocke::TrackerStopKind::Boss, "Winona", "Foretree Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_56, 6, 2156, 0, 6},
    {"scorched-slab", emulocke::TrackerStopKind::Encounter, "Scorched Slab", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_35, 1, nullptr, 0, 0, 0, 0},
    {"route-121", emulocke::TrackerStopKind::Encounter, "Route 121", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_36, 1, nullptr, 0, 0, 0, 0},
    {"lilycove-city", emulocke::TrackerStopKind::Encounter, "Lilycove City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_37, 1, nullptr, 0, 0, 0, 0},
    {"b3", emulocke::TrackerStopKind::Boss, "Brendan", "Lilycove City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_60, 12, 0, 0, 0},
    {"r3", emulocke::TrackerStopKind::Boss, "May", "Lilycove City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_61, 12, 0, 0, 0},
    {"safari-zone", emulocke::TrackerStopKind::Encounter, "Safari Zone", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_38, 2, nullptr, 0, 0, 0, 0},
    {"route-122", emulocke::TrackerStopKind::Encounter, "Route 122", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_39, 1, nullptr, 0, 0, 0, 0},
    {"mt-pyre", emulocke::TrackerStopKind::Encounter, "Mt. Pyre", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_40, 1, nullptr, 0, 0, 0, 0},
    {"am1", emulocke::TrackerStopKind::Boss, "Aqua Admin Matt", "Mt. Pyre", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_65, 6, 0, 0, 0},
    {"magma-hideout", emulocke::TrackerStopKind::Encounter, "Magma Hideout", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_41, 1, nullptr, 0, 0, 0, 0},
    {"mc1", emulocke::TrackerStopKind::Boss, "Magma Admin Courtney", "Magma Hideout", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_67, 6, 0, 0, 0},
    {"mtmax2", emulocke::TrackerStopKind::Boss, "Magma Leader Maxie", "Magma Hideout", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_68, 6, 0, 0, 0},
    {"am2", emulocke::TrackerStopKind::Boss, "Aqua Admin Matt", "Aqua Hideout", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_69, 6, 0, 0, 0},
    {"route-124", emulocke::TrackerStopKind::Encounter, "Route 124", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_42, 1, nullptr, 0, 0, 0, 0},
    {"mossdeep-city", emulocke::TrackerStopKind::Encounter, "Mossdeep City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_43, 1, nullptr, 0, 0, 0, 0},
    {"gym-7", emulocke::TrackerStopKind::Boss, "Tate & Liza", "Mossdeep Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_72, 6, 2157, 0, 7},
    {"mc2", emulocke::TrackerStopKind::Boss, "Magma Admin Courtney", "Mossdeep Space Center", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_73, 6, 0, 0, 0},
    {"mtmax3", emulocke::TrackerStopKind::Boss, "Magma Leader Maxie & Admin Tabitha", "Mossdeep Space Center", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_74, 6, 0, 0, 0},
    {"route-125", emulocke::TrackerStopKind::Encounter, "Route 125", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_44, 1, nullptr, 0, 0, 0, 0},
    {"shoal-cave", emulocke::TrackerStopKind::Encounter, "Shoal Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_45, 1, nullptr, 0, 0, 0, 0},
    {"route-127", emulocke::TrackerStopKind::Encounter, "Route 127", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_46, 1, nullptr, 0, 0, 0, 0},
    {"route-128", emulocke::TrackerStopKind::Encounter, "Route 128", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_47, 1, nullptr, 0, 0, 0, 0},
    {"seafloor-cavern", emulocke::TrackerStopKind::Encounter, "Seafloor Cavern", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_48, 1, nullptr, 0, 0, 0, 0},
    {"as2", emulocke::TrackerStopKind::Boss, "Aqua Admin Shelly", "Seafloor Cavern", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_80, 6, 0, 0, 0},
    {"aqarc", emulocke::TrackerStopKind::Boss, "Aqua Leader Archie", "Seafloor Cavern", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_81, 6, 0, 0, 0},
    {"route-126", emulocke::TrackerStopKind::Encounter, "Route 126", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_49, 1, nullptr, 0, 0, 0, 0},
    {"sootopolis-city", emulocke::TrackerStopKind::Encounter, "Sootopolis City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_50, 1, nullptr, 0, 0, 0, 0},
    {"8a", emulocke::TrackerStopKind::Boss, "Wallace", "Sootopolis Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_84, 6, 0, 0, 0},
    {"8b", emulocke::TrackerStopKind::Boss, "Juan", "Sootopolis Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_85, 6, 0, 0, 0},
    {"cave-of-origins", emulocke::TrackerStopKind::Encounter, "Cave of Origins", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"route-129", emulocke::TrackerStopKind::Encounter, "Route 129", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_51, 1, nullptr, 0, 0, 0, 0},
    {"route-130", emulocke::TrackerStopKind::Encounter, "Route 130", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_52, 1, nullptr, 0, 0, 0, 0},
    {"route-131", emulocke::TrackerStopKind::Encounter, "Route 131", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_53, 1, nullptr, 0, 0, 0, 0},
    {"pacifidlog-town", emulocke::TrackerStopKind::Encounter, "Pacifidlog Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_54, 1, nullptr, 0, 0, 0, 0},
    {"sky-pillar", emulocke::TrackerStopKind::Encounter, "Sky Pillar", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_55, 1, nullptr, 0, 0, 0, 0},
    {"meteor-falls", emulocke::TrackerStopKind::Encounter, "Meteor Falls", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_56, 2, nullptr, 0, 0, 0, 0},
    {"route-132", emulocke::TrackerStopKind::Encounter, "Route 132", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_57, 1, nullptr, 0, 0, 0, 0},
    {"route-133", emulocke::TrackerStopKind::Encounter, "Route 133", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_58, 1, nullptr, 0, 0, 0, 0},
    {"route-123", emulocke::TrackerStopKind::Encounter, "Route 123", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_59, 1, nullptr, 0, 0, 0, 0},
    {"ever-grande-city", emulocke::TrackerStopKind::Encounter, "Ever Grande City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_60, 1, nullptr, 0, 0, 0, 0},
    {"victory-road", emulocke::TrackerStopKind::Encounter, "Victory Road", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_emkaizo_61, 2, nullptr, 0, 0, 0, 0},
    {"w2", emulocke::TrackerStopKind::Boss, "Wally", "Victory Road", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_98, 6, 0, 0, 0},
    {"e1", emulocke::TrackerStopKind::Boss, "Sidney", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_99, 6, 1275, 0, 0},
    {"e2", emulocke::TrackerStopKind::Boss, "Phoebe", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_100, 6, 1276, 0, 0},
    {"e3", emulocke::TrackerStopKind::Boss, "Glacia", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_101, 6, 1277, 0, 0},
    {"e4", emulocke::TrackerStopKind::Boss, "Drake", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_102, 6, 1278, 0, 0},
    {"c", emulocke::TrackerStopKind::Boss, "Steven", "Pokémon League Champion", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_emkaizo_103, 6, 0, 0, 0}
};

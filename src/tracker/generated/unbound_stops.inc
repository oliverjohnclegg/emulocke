constexpr uint16_t kMet_unbound_0[] = {2};
constexpr uint16_t kMet_unbound_1[] = {3};
constexpr uint16_t kMet_unbound_2[] = {4};
constexpr uint16_t kMet_unbound_3[] = {5};
constexpr uint16_t kMet_unbound_4[] = {6};
constexpr uint16_t kMet_unbound_5[] = {9};
constexpr uint16_t kMet_unbound_6[] = {10};
constexpr uint16_t kMet_unbound_7[] = {11};
constexpr uint16_t kMet_unbound_8[] = {12};
constexpr uint16_t kMet_unbound_9[] = {13};
constexpr uint16_t kMet_unbound_10[] = {15};
constexpr uint16_t kMet_unbound_11[] = {16};
constexpr uint16_t kMet_unbound_12[] = {17};
constexpr uint16_t kMet_unbound_13[] = {22};
constexpr uint16_t kMet_unbound_14[] = {23};
constexpr uint16_t kMet_unbound_15[] = {24};
constexpr uint16_t kMet_unbound_16[] = {25};
constexpr uint16_t kMet_unbound_17[] = {27};
constexpr uint16_t kMet_unbound_18[] = {28};
constexpr uint16_t kMet_unbound_19[] = {31};
constexpr uint16_t kMet_unbound_20[] = {32};
constexpr uint16_t kMet_unbound_21[] = {35};
constexpr uint16_t kMet_unbound_22[] = {36};
constexpr uint16_t kMet_unbound_23[] = {37};
constexpr uint16_t kMet_unbound_24[] = {38};
constexpr uint16_t kMet_unbound_25[] = {39};
constexpr uint16_t kMet_unbound_26[] = {40};
constexpr uint16_t kMet_unbound_27[] = {43};
constexpr uint16_t kMet_unbound_28[] = {46};
constexpr uint16_t kMet_unbound_29[] = {49};
constexpr uint16_t kMet_unbound_30[] = {50};
constexpr uint16_t kMet_unbound_31[] = {53};
constexpr uint16_t kMet_unbound_32[] = {56};
constexpr uint16_t kMet_unbound_33[] = {57};
constexpr uint16_t kMet_unbound_34[] = {58};
constexpr uint16_t kMet_unbound_35[] = {59};
constexpr uint16_t kMet_unbound_36[] = {60};
constexpr uint16_t kMet_unbound_37[] = {61};
constexpr uint16_t kMet_unbound_38[] = {62};
constexpr uint16_t kMet_unbound_39[] = {63};
constexpr uint16_t kMet_unbound_40[] = {64};
constexpr uint16_t kMet_unbound_41[] = {66};
constexpr uint16_t kMet_unbound_42[] = {67};
constexpr uint16_t kMet_unbound_43[] = {68};
constexpr uint16_t kMet_unbound_44[] = {71};
constexpr uint16_t kMet_unbound_45[] = {72};
constexpr uint16_t kMet_unbound_46[] = {73};
constexpr uint16_t kMet_unbound_47[] = {74};
constexpr uint16_t kMet_unbound_48[] = {77};
constexpr uint16_t kMet_unbound_49[] = {78};
constexpr uint16_t kMet_unbound_50[] = {79};
constexpr uint16_t kMet_unbound_51[] = {82};
constexpr uint16_t kMet_unbound_52[] = {83};
constexpr uint16_t kMet_unbound_53[] = {86};
constexpr uint16_t kMet_unbound_54[] = {87};
constexpr uint16_t kMet_unbound_55[] = {95};
constexpr uint16_t kMet_unbound_56[] = {96};
constexpr uint16_t kMet_unbound_57[] = {97};
constexpr uint16_t kMet_unbound_58[] = {98};
constexpr uint16_t kMet_unbound_59[] = {99};
constexpr uint16_t kStarters_unbound[] = {374, 443, 246};
constexpr emulocke::TrackerStop kStops_unbound[] = {
    {"starter", emulocke::TrackerStopKind::Encounter, "Starter", "", emulocke::BossKind::None, emulocke::CatchKind::Starter, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"r1", emulocke::TrackerStopKind::Boss, "Rival Axelrod", "Frozen Heights", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_1, 3, 0, 0, 0},
    {"route-1", emulocke::TrackerStopKind::Encounter, "Route 1", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_0, 1, nullptr, 0, 0, 0, 0},
    {"bellin-town", emulocke::TrackerStopKind::Encounter, "Bellin Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_1, 1, nullptr, 0, 0, 0, 0},
    {"icicle-cave", emulocke::TrackerStopKind::Encounter, "Icicle Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_2, 1, nullptr, 0, 0, 0, 0},
    {"r2", emulocke::TrackerStopKind::Boss, "Rival Axelrod", "Icicle Cave", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_5, 4, 0, 0, 0},
    {"route-2", emulocke::TrackerStopKind::Encounter, "Route 2", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_3, 1, nullptr, 0, 0, 0, 0},
    {"dresco-town", emulocke::TrackerStopKind::Encounter, "Dresco Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_4, 1, nullptr, 0, 0, 0, 0},
    {"gym-1", emulocke::TrackerStopKind::Boss, "Leader Mirskle", "Dresco Town Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_8, 4, 0, 0, 1},
    {"route-3", emulocke::TrackerStopKind::Encounter, "Route 3", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_5, 1, nullptr, 0, 0, 0, 0},
    {"flower-paradise", emulocke::TrackerStopKind::Encounter, "Flower Paradise", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_6, 1, nullptr, 0, 0, 0, 0},
    {"route-4", emulocke::TrackerStopKind::Encounter, "Route 4", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_7, 1, nullptr, 0, 0, 0, 0},
    {"grim-woods", emulocke::TrackerStopKind::Encounter, "Grim Woods", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_8, 1, nullptr, 0, 0, 0, 0},
    {"cinder-volcano", emulocke::TrackerStopKind::Encounter, "Cinder Volcano", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_9, 1, nullptr, 0, 0, 0, 0},
    {"sh1", emulocke::TrackerStopKind::Boss, "Shadow Admin Marlon & Grunt", "Cinder Volcano", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_14, 4, 0, 0, 0},
    {"route-5", emulocke::TrackerStopKind::Encounter, "Route 5", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_10, 1, nullptr, 0, 0, 0, 0},
    {"crater-town", emulocke::TrackerStopKind::Encounter, "Crater Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_11, 1, nullptr, 0, 0, 0, 0},
    {"kbt-expressway", emulocke::TrackerStopKind::Encounter, "KBT Expressway", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_12, 1, nullptr, 0, 0, 0, 0},
    {"gym-2", emulocke::TrackerStopKind::Boss, "Leader Vega", "Crater Town Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_18, 3, 0, 0, 2},
    {"sh2", emulocke::TrackerStopKind::Boss, "Shadow Admin Ivory", "Cinder Volcano", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_19, 3, 0, 0, 0},
    {"sh3", emulocke::TrackerStopKind::Boss, "Shadow Boss Zeph", "Cinder Volcano", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_20, 1, 0, 0, 0},
    {"valley-cave", emulocke::TrackerStopKind::Encounter, "Valley Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_13, 1, nullptr, 0, 0, 0, 0},
    {"route-6", emulocke::TrackerStopKind::Encounter, "Route 6", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_14, 1, nullptr, 0, 0, 0, 0},
    {"route-7", emulocke::TrackerStopKind::Encounter, "Route 7", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_15, 1, nullptr, 0, 0, 0, 0},
    {"frost-mountain", emulocke::TrackerStopKind::Encounter, "Frost Mountain", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_16, 1, nullptr, 0, 0, 0, 0},
    {"r3", emulocke::TrackerStopKind::Boss, "Rival Axelford", "Frost Mountain", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_25, 5, 0, 0, 0},
    {"route-8", emulocke::TrackerStopKind::Encounter, "Route 8", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_17, 1, nullptr, 0, 0, 0, 0},
    {"blizzard-city", emulocke::TrackerStopKind::Encounter, "Blizzard City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_18, 1, nullptr, 0, 0, 0, 0},
    {"gym-3", emulocke::TrackerStopKind::Boss, "Leader Alice", "Blizzard City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_28, 4, 0, 0, 3},
    {"frozen-forest", emulocke::TrackerStopKind::Encounter, "Frozen Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_19, 1, nullptr, 0, 0, 0, 0},
    {"fallshore-city", emulocke::TrackerStopKind::Encounter, "Fallshore City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_20, 1, nullptr, 0, 0, 0, 0},
    {"gym-4", emulocke::TrackerStopKind::Boss, "Leader Mel", "Fallshore City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_31, 4, 0, 0, 4},
    {"route-11", emulocke::TrackerStopKind::Encounter, "Route 11", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_21, 1, nullptr, 0, 0, 0, 0},
    {"epidimy-town", emulocke::TrackerStopKind::Encounter, "Epidimy Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_22, 1, nullptr, 0, 0, 0, 0},
    {"route-10", emulocke::TrackerStopKind::Encounter, "Route 10", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_23, 1, nullptr, 0, 0, 0, 0},
    {"auburn-waterway", emulocke::TrackerStopKind::Encounter, "Auburn Waterway", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_24, 1, nullptr, 0, 0, 0, 0},
    {"route-9", emulocke::TrackerStopKind::Encounter, "Route 9", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_25, 1, nullptr, 0, 0, 0, 0},
    {"tehl-town", emulocke::TrackerStopKind::Encounter, "Tehl Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_26, 1, nullptr, 0, 0, 0, 0},
    {"sh4", emulocke::TrackerStopKind::Boss, "Shadow Admin Ivory & Grunt", "Underground Passage", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_38, 5, 0, 0, 0},
    {"tarmigan-town", emulocke::TrackerStopKind::Encounter, "Tarmigan Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_27, 1, nullptr, 0, 0, 0, 0},
    {"mb1", emulocke::TrackerStopKind::Boss, "Successor Maxima", "Tramigan Mansion", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_40, 5, 0, 0, 0},
    {"thundercap-mt", emulocke::TrackerStopKind::Encounter, "Thundercap Mt.", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_28, 1, nullptr, 0, 0, 0, 0},
    {"sh5", emulocke::TrackerStopKind::Boss, "Shadow Admin Marlon", "Thunder Cap Mt.", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_42, 5, 0, 0, 0},
    {"route-12", emulocke::TrackerStopKind::Encounter, "Route 12", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_29, 1, nullptr, 0, 0, 0, 0},
    {"r4", emulocke::TrackerStopKind::Boss, "Rival Axelford", "Route 12", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_44, 9, 0, 0, 0},
    {"dehara-city", emulocke::TrackerStopKind::Encounter, "Dehara City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_30, 1, nullptr, 0, 0, 0, 0},
    {"gym-5", emulocke::TrackerStopKind::Boss, "Leader Galavan", "Dehara City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_46, 6, 0, 0, 5},
    {"ruins-of-void", emulocke::TrackerStopKind::Encounter, "Ruins of Void", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_31, 1, nullptr, 0, 0, 0, 0},
    {"lr1", emulocke::TrackerStopKind::Boss, "Ruin Agent Vega & Grunt", "Ruins of Void", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_48, 6, 0, 0, 0},
    {"sh6", emulocke::TrackerStopKind::Boss, "Shadow Boss Zeph", "Shadow Base", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_49, 5, 0, 0, 0},
    {"route-15", emulocke::TrackerStopKind::Encounter, "Route 15", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_32, 1, nullptr, 0, 0, 0, 0},
    {"route-13", emulocke::TrackerStopKind::Encounter, "Route 13", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_33, 1, nullptr, 0, 0, 0, 0},
    {"route-14", emulocke::TrackerStopKind::Encounter, "Route 14", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_34, 1, nullptr, 0, 0, 0, 0},
    {"lost-tunnel", emulocke::TrackerStopKind::Encounter, "Lost Tunnel", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_35, 1, nullptr, 0, 0, 0, 0},
    {"great-desert", emulocke::TrackerStopKind::Encounter, "Great Desert", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_36, 1, nullptr, 0, 0, 0, 0},
    {"gurun-town", emulocke::TrackerStopKind::Encounter, "Gurun Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_37, 1, nullptr, 0, 0, 0, 0},
    {"vivill-woods", emulocke::TrackerStopKind::Encounter, "Vivill Woods", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_38, 1, nullptr, 0, 0, 0, 0},
    {"vivill-town", emulocke::TrackerStopKind::Encounter, "Vivill Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_39, 1, nullptr, 0, 0, 0, 0},
    {"vivill-warehouse", emulocke::TrackerStopKind::Encounter, "Vivill Warehouse", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_40, 1, nullptr, 0, 0, 0, 0},
    {"lr2", emulocke::TrackerStopKind::Boss, "Ruin Leader Aklove", "Vivill Warehouse", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_59, 5, 0, 0, 0},
    {"route-16", emulocke::TrackerStopKind::Encounter, "Route 16", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_41, 1, nullptr, 0, 0, 0, 0},
    {"antisis-city", emulocke::TrackerStopKind::Encounter, "Antisis City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_42, 1, nullptr, 0, 0, 0, 0},
    {"antisis-sewers", emulocke::TrackerStopKind::Encounter, "Antisis Sewers", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_43, 1, nullptr, 0, 0, 0, 0},
    {"gym-6", emulocke::TrackerStopKind::Boss, "Leader Big Mo", "Antisis City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_63, 5, 0, 0, 6},
    {"icy-hole", emulocke::TrackerStopKind::Encounter, "Icy Hole", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_44, 1, nullptr, 0, 0, 0, 0},
    {"seaport-city", emulocke::TrackerStopKind::Encounter, "Seaport City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_45, 1, nullptr, 0, 0, 0, 0},
    {"polder-town", emulocke::TrackerStopKind::Encounter, "Polder Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_46, 1, nullptr, 0, 0, 0, 0},
    {"safari-zone", emulocke::TrackerStopKind::Encounter, "Safari Zone", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_47, 1, nullptr, 0, 0, 0, 0},
    {"gym-7", emulocke::TrackerStopKind::Boss, "Leader Tessy", "Polder Town Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_68, 6, 0, 0, 7},
    {"cootes-bog", emulocke::TrackerStopKind::Encounter, "Cootes Bog", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_48, 1, nullptr, 0, 0, 0, 0},
    {"magnolia-town", emulocke::TrackerStopKind::Encounter, "Magnolia Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_49, 1, nullptr, 0, 0, 0, 0},
    {"r5", emulocke::TrackerStopKind::Boss, "Rival Axelford", "Magnolia Town", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_71, 9, 0, 0, 0},
    {"crystal-peak", emulocke::TrackerStopKind::Encounter, "Crystal Peak", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_50, 1, nullptr, 0, 0, 0, 0},
    {"lr3", emulocke::TrackerStopKind::Boss, "Ruin Admin Ivory", "Crystal Peak", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_73, 5, 0, 0, 0},
    {"lr4", emulocke::TrackerStopKind::Boss, "Ruin Leader Aklove", "Crystal Peak", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_74, 5, 0, 0, 0},
    {"sh7", emulocke::TrackerStopKind::Boss, "Ex-Shadow Admin Marlon", "Crystal Peak", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_75, 5, 0, 0, 0},
    {"magnolia-fields", emulocke::TrackerStopKind::Encounter, "Magnolia Fields", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_51, 1, nullptr, 0, 0, 0, 0},
    {"redwood-village", emulocke::TrackerStopKind::Encounter, "Redwood Village", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_52, 1, nullptr, 0, 0, 0, 0},
    {"gym-8", emulocke::TrackerStopKind::Boss, "Leader Benjamin", "Redwood Village Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_78, 5, 0, 0, 8},
    {"route-18", emulocke::TrackerStopKind::Encounter, "Route 18", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_53, 1, nullptr, 0, 0, 0, 0},
    {"victory-road", emulocke::TrackerStopKind::Encounter, "Victory Road", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_54, 1, nullptr, 0, 0, 0, 0},
    {"e1", emulocke::TrackerStopKind::Boss, "Moleman", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_81, 6, 0, 0, 0},
    {"e2", emulocke::TrackerStopKind::Boss, "Elias", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_82, 5, 0, 0, 0},
    {"e3", emulocke::TrackerStopKind::Boss, "Arabella", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_83, 6, 0, 0, 0},
    {"e4", emulocke::TrackerStopKind::Boss, "Penny", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_84, 6, 0, 0, 0},
    {"c", emulocke::TrackerStopKind::Boss, "Jax", "Pokémon League Champion", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_85, 6, 0, 0, 0},
    {"tomb-of-borrius", emulocke::TrackerStopKind::Encounter, "Tomb of Borrius", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_55, 1, nullptr, 0, 0, 0, 0},
    {"rift-cave", emulocke::TrackerStopKind::Encounter, "Rift Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_56, 1, nullptr, 0, 0, 0, 0},
    {"redwood-forest", emulocke::TrackerStopKind::Encounter, "Redwood Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_57, 1, nullptr, 0, 0, 0, 0},
    {"cliff-cave", emulocke::TrackerStopKind::Encounter, "Cliff Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_58, 1, nullptr, 0, 0, 0, 0},
    {"cube-corp", emulocke::TrackerStopKind::Encounter, "Cube Corp.", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_59, 1, nullptr, 0, 0, 0, 0},
    {"lr5", emulocke::TrackerStopKind::Boss, "Ruin Leader Aklove", "Ruins of Void", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_91, 6, 0, 0, 0}
};

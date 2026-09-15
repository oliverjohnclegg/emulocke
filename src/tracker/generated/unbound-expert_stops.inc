constexpr uint16_t kMet_unbound_expert_0[] = {2};
constexpr uint16_t kMet_unbound_expert_1[] = {3};
constexpr uint16_t kMet_unbound_expert_2[] = {4};
constexpr uint16_t kMet_unbound_expert_3[] = {5};
constexpr uint16_t kMet_unbound_expert_4[] = {6};
constexpr uint16_t kMet_unbound_expert_5[] = {9};
constexpr uint16_t kMet_unbound_expert_6[] = {10};
constexpr uint16_t kMet_unbound_expert_7[] = {11};
constexpr uint16_t kMet_unbound_expert_8[] = {12};
constexpr uint16_t kMet_unbound_expert_9[] = {13};
constexpr uint16_t kMet_unbound_expert_10[] = {15};
constexpr uint16_t kMet_unbound_expert_11[] = {16};
constexpr uint16_t kMet_unbound_expert_12[] = {17};
constexpr uint16_t kMet_unbound_expert_13[] = {22};
constexpr uint16_t kMet_unbound_expert_14[] = {23};
constexpr uint16_t kMet_unbound_expert_15[] = {24};
constexpr uint16_t kMet_unbound_expert_16[] = {25};
constexpr uint16_t kMet_unbound_expert_17[] = {27};
constexpr uint16_t kMet_unbound_expert_18[] = {28};
constexpr uint16_t kMet_unbound_expert_19[] = {31};
constexpr uint16_t kMet_unbound_expert_20[] = {32};
constexpr uint16_t kMet_unbound_expert_21[] = {35};
constexpr uint16_t kMet_unbound_expert_22[] = {36};
constexpr uint16_t kMet_unbound_expert_23[] = {37};
constexpr uint16_t kMet_unbound_expert_24[] = {38};
constexpr uint16_t kMet_unbound_expert_25[] = {39};
constexpr uint16_t kMet_unbound_expert_26[] = {40};
constexpr uint16_t kMet_unbound_expert_27[] = {43};
constexpr uint16_t kMet_unbound_expert_28[] = {46};
constexpr uint16_t kMet_unbound_expert_29[] = {49};
constexpr uint16_t kMet_unbound_expert_30[] = {50};
constexpr uint16_t kMet_unbound_expert_31[] = {53};
constexpr uint16_t kMet_unbound_expert_32[] = {56};
constexpr uint16_t kMet_unbound_expert_33[] = {57};
constexpr uint16_t kMet_unbound_expert_34[] = {58};
constexpr uint16_t kMet_unbound_expert_35[] = {59};
constexpr uint16_t kMet_unbound_expert_36[] = {60};
constexpr uint16_t kMet_unbound_expert_37[] = {61};
constexpr uint16_t kMet_unbound_expert_38[] = {62};
constexpr uint16_t kMet_unbound_expert_39[] = {63};
constexpr uint16_t kMet_unbound_expert_40[] = {64};
constexpr uint16_t kMet_unbound_expert_41[] = {66};
constexpr uint16_t kMet_unbound_expert_42[] = {67};
constexpr uint16_t kMet_unbound_expert_43[] = {68};
constexpr uint16_t kMet_unbound_expert_44[] = {71};
constexpr uint16_t kMet_unbound_expert_45[] = {72};
constexpr uint16_t kMet_unbound_expert_46[] = {73};
constexpr uint16_t kMet_unbound_expert_47[] = {74};
constexpr uint16_t kMet_unbound_expert_48[] = {77};
constexpr uint16_t kMet_unbound_expert_49[] = {78};
constexpr uint16_t kMet_unbound_expert_50[] = {79};
constexpr uint16_t kMet_unbound_expert_51[] = {82};
constexpr uint16_t kMet_unbound_expert_52[] = {83};
constexpr uint16_t kMet_unbound_expert_53[] = {86};
constexpr uint16_t kMet_unbound_expert_54[] = {87};
constexpr uint16_t kMet_unbound_expert_55[] = {95};
constexpr uint16_t kMet_unbound_expert_56[] = {96};
constexpr uint16_t kMet_unbound_expert_57[] = {97};
constexpr uint16_t kMet_unbound_expert_58[] = {98};
constexpr uint16_t kMet_unbound_expert_59[] = {99};
constexpr uint16_t kStarters_unbound_expert[] = {374, 443, 246};
constexpr emulocke::TrackerStop kStops_unbound_expert[] = {
    {"starter", emulocke::TrackerStopKind::Encounter, "Starter", "", emulocke::BossKind::None, emulocke::CatchKind::Starter, nullptr, 0, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"r1-exp", emulocke::TrackerStopKind::Boss, "Rival Axelrod", "Frozen Heights", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_1, 3, 0, 0, 0, 17, 1, false, "", ""},
    {"route-1", emulocke::TrackerStopKind::Encounter, "Route 1", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_0, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"bellin-town", emulocke::TrackerStopKind::Encounter, "Bellin Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_1, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"icicle-cave", emulocke::TrackerStopKind::Encounter, "Icicle Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_2, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"r2-exp", emulocke::TrackerStopKind::Boss, "Rival Axelrod", "Icicle Cave", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_5, 4, 0, 0, 0, 19, 1, false, "", ""},
    {"route-2", emulocke::TrackerStopKind::Encounter, "Route 2", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_3, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"dresco-town", emulocke::TrackerStopKind::Encounter, "Dresco Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_4, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"gym-1", emulocke::TrackerStopKind::Boss, "Leader Mirskle", "Dresco Town Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_8, 4, 0, 0, 1, 21, 2, false, "fog", ""},
    {"route-3", emulocke::TrackerStopKind::Encounter, "Route 3", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_5, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"flower-paradise", emulocke::TrackerStopKind::Encounter, "Flower Paradise", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_6, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"route-4", emulocke::TrackerStopKind::Encounter, "Route 4", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_7, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"grim-woods", emulocke::TrackerStopKind::Encounter, "Grim Woods", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_8, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"cinder-volcano", emulocke::TrackerStopKind::Encounter, "Cinder Volcano", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_9, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"sh1-exp", emulocke::TrackerStopKind::Boss, "Shadow Admin Marlon & Grunt", "Cinder Volcano", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_14, 5, 0, 0, 0, 28, 2, true, "", ""},
    {"route-5", emulocke::TrackerStopKind::Encounter, "Route 5", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_10, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"crater-town", emulocke::TrackerStopKind::Encounter, "Crater Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_11, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"kbt-expressway", emulocke::TrackerStopKind::Encounter, "KBT Expressway", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_12, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"gym-2", emulocke::TrackerStopKind::Boss, "Leader Vega", "Crater Town Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_18, 4, 0, 0, 2, 27, 1, false, "", "Negative Energy A negative energy fills the battlefield and makes every non-Dark, non-Ghost and non-Psychic type Pokemon take 6.25% damage at the end of every turn."},
    {"sh2-exp", emulocke::TrackerStopKind::Boss, "Shadow Admin Ivory", "Cinder Volcano", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_19, 3, 0, 0, 0, 34, 1, false, "", ""},
    {"sh3-exp", emulocke::TrackerStopKind::Boss, "Shadow Boss Zeph", "Cinder Volcano", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_20, 1, 0, 0, 0, 33, 1, false, "", ""},
    {"valley-cave", emulocke::TrackerStopKind::Encounter, "Valley Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_13, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"route-6", emulocke::TrackerStopKind::Encounter, "Route 6", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_14, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"route-7", emulocke::TrackerStopKind::Encounter, "Route 7", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_15, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"frost-mountain", emulocke::TrackerStopKind::Encounter, "Frost Mountain", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_16, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"r3-exp", emulocke::TrackerStopKind::Boss, "Rival Axelford", "Frost Mountain", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_25, 5, 0, 0, 0, 33, 1, false, "", ""},
    {"route-8", emulocke::TrackerStopKind::Encounter, "Route 8", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_17, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"blizzard-city", emulocke::TrackerStopKind::Encounter, "Blizzard City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_18, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"gym-3", emulocke::TrackerStopKind::Boss, "Leader Alice", "Blizzard City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_28, 5, 0, 0, 3, 33, 1, false, "", "Tailwind A permanent tailwind effect for Flying-Types"},
    {"frozen-forest", emulocke::TrackerStopKind::Encounter, "Frozen Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_19, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"fallshore-city", emulocke::TrackerStopKind::Encounter, "Fallshore City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_20, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"gym-4", emulocke::TrackerStopKind::Boss, "Leader Mel", "Fallshore City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_31, 5, 0, 0, 4, 37, 1, false, "", "Inverse Battle Type matchups are reversed and no type is immune to any other type."},
    {"route-11", emulocke::TrackerStopKind::Encounter, "Route 11", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_21, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"epidimy-town", emulocke::TrackerStopKind::Encounter, "Epidimy Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_22, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"route-10", emulocke::TrackerStopKind::Encounter, "Route 10", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_23, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"auburn-waterway", emulocke::TrackerStopKind::Encounter, "Auburn Waterway", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_24, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"route-9", emulocke::TrackerStopKind::Encounter, "Route 9", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_25, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"tehl-town", emulocke::TrackerStopKind::Encounter, "Tehl Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_26, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"sh4-exp", emulocke::TrackerStopKind::Boss, "Shadow Admin Ivory & Grunt", "Underground Passage", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_38, 5, 0, 0, 0, 38, 2, true, "", ""},
    {"tarmigan-town", emulocke::TrackerStopKind::Encounter, "Tarmigan Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_27, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"mb1-exp", emulocke::TrackerStopKind::Boss, "Successor Maxima", "Tramigan Mansion", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_40, 5, 0, 0, 0, 41, 1, false, "", ""},
    {"thundercap-mt", emulocke::TrackerStopKind::Encounter, "Thundercap Mt.", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_28, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"sh5-exp", emulocke::TrackerStopKind::Boss, "Shadow Admin Marlon", "Thunder Cap Mt.", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_42, 5, 0, 0, 0, 41, 1, false, "", ""},
    {"route-12", emulocke::TrackerStopKind::Encounter, "Route 12", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_29, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"r4-exp", emulocke::TrackerStopKind::Boss, "Rival Axelford", "Route 12", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_44, 9, 0, 0, 0, 47, 1, false, "", ""},
    {"dehara-city", emulocke::TrackerStopKind::Encounter, "Dehara City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_30, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"gym-5", emulocke::TrackerStopKind::Boss, "Leader Galavan", "Dehara City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_46, 5, 0, 0, 5, 46, 2, false, "", "Magnet Rise Permanent Magnet Rise effect for Steel-Type & Electric-Types making them immune to Ground type attacks."},
    {"ruins-of-void", emulocke::TrackerStopKind::Encounter, "Ruins of Void", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_31, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"lr1-exp", emulocke::TrackerStopKind::Boss, "Ruin Agent Vega & Grunt", "Ruins of Void", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_48, 6, 0, 0, 0, 47, 2, true, "", ""},
    {"sh6-exp", emulocke::TrackerStopKind::Boss, "Shadow Boss Zeph", "Shadow Base", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_49, 5, 0, 0, 0, 46, 1, false, "", ""},
    {"route-15", emulocke::TrackerStopKind::Encounter, "Route 15", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_32, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"route-13", emulocke::TrackerStopKind::Encounter, "Route 13", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_33, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"route-14", emulocke::TrackerStopKind::Encounter, "Route 14", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_34, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"lost-tunnel", emulocke::TrackerStopKind::Encounter, "Lost Tunnel", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_35, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"great-desert", emulocke::TrackerStopKind::Encounter, "Great Desert", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_36, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"gurun-town", emulocke::TrackerStopKind::Encounter, "Gurun Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_37, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"vivill-woods", emulocke::TrackerStopKind::Encounter, "Vivill Woods", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_38, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"vivill-town", emulocke::TrackerStopKind::Encounter, "Vivill Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_39, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"vivill-warehouse", emulocke::TrackerStopKind::Encounter, "Vivill Warehouse", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_40, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"lr2-exp", emulocke::TrackerStopKind::Boss, "Ruin Leader Aklove", "Vivill Warehouse", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_59, 6, 0, 0, 0, 53, 1, false, "", ""},
    {"route-16", emulocke::TrackerStopKind::Encounter, "Route 16", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_41, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"antisis-city", emulocke::TrackerStopKind::Encounter, "Antisis City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_42, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"antisis-sewers", emulocke::TrackerStopKind::Encounter, "Antisis Sewers", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_43, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"gym-6", emulocke::TrackerStopKind::Boss, "Leader Big Mo", "Antisis City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_63, 5, 0, 0, 6, 53, 1, false, "", "Inverse Gravity Permanent Trick Room effect for weight, heavier Pokemon go first."},
    {"icy-hole", emulocke::TrackerStopKind::Encounter, "Icy Hole", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_44, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"seaport-city", emulocke::TrackerStopKind::Encounter, "Seaport City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_45, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"polder-town", emulocke::TrackerStopKind::Encounter, "Polder Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_46, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"safari-zone", emulocke::TrackerStopKind::Encounter, "Safari Zone", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_47, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"gym-7", emulocke::TrackerStopKind::Boss, "Leader Tessy", "Polder Town Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_68, 6, 0, 0, 7, 58, 1, false, "rain", "Camo-mons The Pokemon's types are that of the types of their first two attacks."},
    {"cootes-bog", emulocke::TrackerStopKind::Encounter, "Cootes Bog", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_48, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"magnolia-town", emulocke::TrackerStopKind::Encounter, "Magnolia Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_49, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"r5-exp", emulocke::TrackerStopKind::Boss, "Rival Axelford", "Magnolia Town", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_71, 14, 0, 0, 0, 65, 1, false, "", ""},
    {"crystal-peak", emulocke::TrackerStopKind::Encounter, "Crystal Peak", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_50, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"lr3-exp", emulocke::TrackerStopKind::Boss, "Ruin Admin Ivory", "Crystal Peak", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_73, 6, 0, 0, 0, 62, 2, true, "", ""},
    {"lr4-exp", emulocke::TrackerStopKind::Boss, "Ruin Leader Aklove", "Crystal Peak", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_74, 6, 0, 0, 0, 62, 1, false, "", ""},
    {"sh7-exp", emulocke::TrackerStopKind::Boss, "Ex-Shadow Admin Marlon", "Crystal Peak", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_75, 6, 0, 0, 0, 62, 1, false, "", ""},
    {"magnolia-fields", emulocke::TrackerStopKind::Encounter, "Magnolia Fields", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_51, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"redwood-village", emulocke::TrackerStopKind::Encounter, "Redwood Village", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_52, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"gym-8", emulocke::TrackerStopKind::Boss, "Leader Benjamin", "Redwood Village Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_78, 6, 0, 0, 8, 62, 1, false, "", "Benjamin Butterfree When a Pokemon is knocked out, instead of fainting it devolves to a previous evolution. The Pokemon finally faints when it can’t devolve anymore."},
    {"route-18", emulocke::TrackerStopKind::Encounter, "Route 18", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_53, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"victory-road", emulocke::TrackerStopKind::Encounter, "Victory Road", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_54, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"e1-exp", emulocke::TrackerStopKind::Boss, "Moleman", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_81, 6, 0, 0, 0, 76, 2, false, "sandstorm", "Vicious Sandstorm Vicious sand causes Pokemon to lose 1/8 of max HP at the end of every turn"},
    {"e2-exp", emulocke::TrackerStopKind::Boss, "Elias", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_82, 6, 0, 0, 0, 76, 1, false, "", "Shadowy Veil Every Ghost-type Pokemon take half damage on full HP. Ghost-types are immune to entry hazards at full HP. Other Types cannot use Safeguard or Substitute."},
    {"e3-exp", emulocke::TrackerStopKind::Boss, "Arabella", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_83, 6, 0, 0, 0, 76, 1, false, "misty-terrain", "Fairy ring All Fairy-Type Pokemon get a +1 boost to their lowest Defense stat on switch in."},
    {"e4-exp", emulocke::TrackerStopKind::Boss, "Penny", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_84, 6, 0, 0, 0, 76, 2, false, "", "Rainbow Battle All Dragon-type Pokemon on the field have their moves' secondary effect chance doubled. This stacks Serene Grace with the exception of flinching moves."},
    {"c-exp", emulocke::TrackerStopKind::Boss, "Jax", "Pokémon League Champion", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_85, 6, 0, 0, 0, 76, 2, false, "", ""},
    {"tomb-of-borrius", emulocke::TrackerStopKind::Encounter, "Tomb of Borrius", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_55, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"rift-cave", emulocke::TrackerStopKind::Encounter, "Rift Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_56, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"redwood-forest", emulocke::TrackerStopKind::Encounter, "Redwood Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_57, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"cliff-cave", emulocke::TrackerStopKind::Encounter, "Cliff Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_58, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"cube-corp", emulocke::TrackerStopKind::Encounter, "Cube Corp.", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_59, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", ""},
    {"lr5-exp", emulocke::TrackerStopKind::Boss, "Ruin Leader Aklove", "Ruins of Void", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_91, 6, 0, 0, 0, 75, 1, false, "", ""}
};

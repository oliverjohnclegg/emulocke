constexpr uint16_t kMet_unbound_expert_0[] = {101};
constexpr uint16_t kMet_unbound_expert_1[] = {89};
constexpr uint16_t kMet_unbound_expert_2[] = {141};
constexpr uint16_t kMet_unbound_expert_3[] = {102};
constexpr uint16_t kMet_unbound_expert_4[] = {90};
constexpr uint16_t kMet_unbound_expert_5[] = {103};
constexpr uint16_t kMet_unbound_expert_6[] = {136};
constexpr uint16_t kMet_unbound_expert_7[] = {99};
constexpr uint16_t kMet_unbound_expert_8[] = {126};
constexpr uint16_t kMet_unbound_expert_9[] = {127};
constexpr uint16_t kMet_unbound_expert_10[] = {105};
constexpr uint16_t kMet_unbound_expert_11[] = {91};
constexpr uint16_t kMet_unbound_expert_12[] = {134};
constexpr uint16_t kMet_unbound_expert_13[] = {131};
constexpr uint16_t kMet_unbound_expert_14[] = {106};
constexpr uint16_t kMet_unbound_expert_15[] = {107};
constexpr uint16_t kMet_unbound_expert_16[] = {130};
constexpr uint16_t kMet_unbound_expert_17[] = {108};
constexpr uint16_t kMet_unbound_expert_18[] = {92};
constexpr uint16_t kMet_unbound_expert_19[] = {153};
constexpr uint16_t kMet_unbound_expert_20[] = {94};
constexpr uint16_t kMet_unbound_expert_21[] = {111};
constexpr uint16_t kMet_unbound_expert_22[] = {95};
constexpr uint16_t kMet_unbound_expert_23[] = {100};
constexpr uint16_t kMet_unbound_expert_24[] = {142};
constexpr uint16_t kMet_unbound_expert_25[] = {109};
constexpr uint16_t kMet_unbound_expert_26[] = {93};
constexpr uint16_t kMet_unbound_expert_27[] = {96};
constexpr uint16_t kMet_unbound_expert_28[] = {138};
constexpr uint16_t kMet_unbound_expert_29[] = {112};
constexpr uint16_t kMet_unbound_expert_30[] = {98};
constexpr uint16_t kMet_unbound_expert_31[] = {104};
constexpr uint16_t kMet_unbound_expert_32[] = {115};
constexpr uint16_t kMet_unbound_expert_33[] = {113};
constexpr uint16_t kMet_unbound_expert_34[] = {114};
constexpr uint16_t kMet_unbound_expert_35[] = {156};
constexpr uint16_t kMet_unbound_expert_36[] = {123};
constexpr uint16_t kMet_unbound_expert_37[] = {122};
constexpr uint16_t kMet_unbound_expert_38[] = {140};
constexpr uint16_t kMet_unbound_expert_39[] = {121};
constexpr uint16_t kMet_unbound_expert_40[] = {124};
constexpr uint16_t kMet_unbound_expert_41[] = {116};
constexpr uint16_t kMet_unbound_expert_42[] = {120};
constexpr uint16_t kMet_unbound_expert_43[] = {143};
constexpr uint16_t kMet_unbound_expert_44[] = {157};
constexpr uint16_t kMet_unbound_expert_45[] = {119};
constexpr uint16_t kMet_unbound_expert_46[] = {144};
constexpr uint16_t kMet_unbound_expert_47[] = {164};
constexpr uint16_t kMet_unbound_expert_48[] = {181};
constexpr uint16_t kMet_unbound_expert_49[] = {145};
constexpr uint16_t kMet_unbound_expert_50[] = {158};
constexpr uint16_t kMet_unbound_expert_51[] = {182};
constexpr uint16_t kMet_unbound_expert_52[] = {146};
constexpr uint16_t kMet_unbound_expert_53[] = {118};
constexpr uint16_t kMet_unbound_expert_54[] = {132};
constexpr uint16_t kMet_unbound_expert_55[] = {192};
constexpr uint16_t kMet_unbound_expert_56[] = {139};
constexpr uint16_t kMet_unbound_expert_57[] = {183};
constexpr uint16_t kMet_unbound_expert_58[] = {185};
constexpr uint16_t kMet_unbound_expert_59[] = {147};
constexpr uint16_t kStarters_unbound_expert[] = {374, 443, 246};
constexpr emulocke::TrackerStop kStops_unbound_expert[] = {
    {"starter", emulocke::TrackerStopKind::Encounter, "Starter", "", emulocke::BossKind::None, emulocke::CatchKind::Starter, nullptr, 0, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"r1-exp", emulocke::TrackerStopKind::Boss, "Rival Axelrod", "Frozen Heights", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_1, 3, 1606, 3, 0, 17, 1, false, "", "", false},
    {"route-1", emulocke::TrackerStopKind::Encounter, "Route 1", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_0, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"bellin-town", emulocke::TrackerStopKind::Encounter, "Bellin Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_1, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"icicle-cave", emulocke::TrackerStopKind::Encounter, "Icicle Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_2, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"r2-exp", emulocke::TrackerStopKind::Boss, "Rival Axelrod", "Icicle Cave", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_5, 4, 1609, 3, 0, 19, 1, false, "", "", false},
    {"route-2", emulocke::TrackerStopKind::Encounter, "Route 2", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_3, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"dresco-town", emulocke::TrackerStopKind::Encounter, "Dresco Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_4, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-1", emulocke::TrackerStopKind::Boss, "Leader Mirskle", "Dresco Town Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_8, 4, 0, 0, 1, 21, 2, false, "fog", "", false},
    {"route-3", emulocke::TrackerStopKind::Encounter, "Route 3", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_5, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"flower-paradise", emulocke::TrackerStopKind::Encounter, "Flower Paradise", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_6, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-4", emulocke::TrackerStopKind::Encounter, "Route 4", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_7, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"grim-woods", emulocke::TrackerStopKind::Encounter, "Grim Woods", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_8, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"cinder-volcano", emulocke::TrackerStopKind::Encounter, "Cinder Volcano", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_9, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"sh1-exp", emulocke::TrackerStopKind::Boss, "Shadow Admin Marlon & Grunt", "Cinder Volcano", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_14, 5, 1294, 0, 0, 28, 2, true, "", "", false},
    {"route-5", emulocke::TrackerStopKind::Encounter, "Route 5", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_10, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"crater-town", emulocke::TrackerStopKind::Encounter, "Crater Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_11, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"kbt-expressway", emulocke::TrackerStopKind::Encounter, "KBT Expressway", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_12, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-2", emulocke::TrackerStopKind::Boss, "Leader Vega", "Crater Town Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_18, 4, 0, 0, 2, 27, 1, false, "", "Negative Energy A negative energy fills the battlefield and makes every non-Dark, non-Ghost and non-Psychic type Pokemon take 6.25% damage at the end of every turn.", false},
    {"sh2-exp", emulocke::TrackerStopKind::Boss, "Shadow Admin Ivory", "Cinder Volcano", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_19, 3, 1306, 0, 0, 34, 1, false, "", "", false},
    {"sh3-exp", emulocke::TrackerStopKind::Boss, "Shadow Boss Zeph", "Cinder Volcano", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_20, 1, 1336, 0, 0, 33, 1, false, "", "", false},
    {"valley-cave", emulocke::TrackerStopKind::Encounter, "Valley Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_13, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-6", emulocke::TrackerStopKind::Encounter, "Route 6", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_14, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-7", emulocke::TrackerStopKind::Encounter, "Route 7", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_15, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"frost-mountain", emulocke::TrackerStopKind::Encounter, "Frost Mountain", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_16, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"r3-exp", emulocke::TrackerStopKind::Boss, "Rival Axelford", "Frost Mountain", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_25, 5, 1612, 3, 0, 33, 1, false, "", "", false},
    {"route-8", emulocke::TrackerStopKind::Encounter, "Route 8", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_17, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"blizzard-city", emulocke::TrackerStopKind::Encounter, "Blizzard City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_18, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-3", emulocke::TrackerStopKind::Boss, "Leader Alice", "Blizzard City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_28, 5, 0, 0, 3, 33, 1, false, "", "Tailwind A permanent tailwind effect for Flying-Types", false},
    {"frozen-forest", emulocke::TrackerStopKind::Encounter, "Frozen Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_19, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"fallshore-city", emulocke::TrackerStopKind::Encounter, "Fallshore City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_20, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-4", emulocke::TrackerStopKind::Boss, "Leader Mel", "Fallshore City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_31, 5, 0, 0, 4, 37, 1, false, "", "Inverse Battle Type matchups are reversed and no type is immune to any other type.", false},
    {"route-11", emulocke::TrackerStopKind::Encounter, "Route 11", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_21, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"epidimy-town", emulocke::TrackerStopKind::Encounter, "Epidimy Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_22, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-10", emulocke::TrackerStopKind::Encounter, "Route 10", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_23, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"auburn-waterway", emulocke::TrackerStopKind::Encounter, "Auburn Waterway", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_24, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-9", emulocke::TrackerStopKind::Encounter, "Route 9", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_25, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"tehl-town", emulocke::TrackerStopKind::Encounter, "Tehl Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_26, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"sh4-exp", emulocke::TrackerStopKind::Boss, "Shadow Admin Ivory & Grunt", "Underground Passage", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_38, 5, 1294, 0, 0, 38, 2, true, "", "", false},
    {"tarmigan-town", emulocke::TrackerStopKind::Encounter, "Tarmigan Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_27, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"mb1-exp", emulocke::TrackerStopKind::Boss, "Successor Maxima", "Tramigan Mansion", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_40, 5, 1304, 0, 0, 41, 1, false, "", "", false},
    {"thundercap-mt", emulocke::TrackerStopKind::Encounter, "Thundercap Mt.", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_28, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"sh5-exp", emulocke::TrackerStopKind::Boss, "Shadow Admin Marlon", "Thunder Cap Mt.", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_42, 5, 1305, 0, 0, 41, 1, false, "", "", false},
    {"route-12", emulocke::TrackerStopKind::Encounter, "Route 12", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_29, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"r4-exp", emulocke::TrackerStopKind::Boss, "Rival Axelford", "Route 12", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_44, 9, 1706, 3, 0, 47, 1, false, "", "", false},
    {"dehara-city", emulocke::TrackerStopKind::Encounter, "Dehara City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_30, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-5", emulocke::TrackerStopKind::Boss, "Leader Galavan", "Dehara City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_46, 5, 0, 0, 5, 46, 2, false, "", "Magnet Rise Permanent Magnet Rise effect for Steel-Type & Electric-Types making them immune to Ground type attacks.", false},
    {"ruins-of-void", emulocke::TrackerStopKind::Encounter, "Ruins of Void", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_31, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"lr1-exp", emulocke::TrackerStopKind::Boss, "Ruin Agent Vega & Grunt", "Ruins of Void", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_48, 6, 1294, 0, 0, 47, 2, true, "", "", false},
    {"sh6-exp", emulocke::TrackerStopKind::Boss, "Shadow Boss Zeph", "Shadow Base", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_49, 5, 1336, 0, 0, 46, 1, false, "", "", false},
    {"route-15", emulocke::TrackerStopKind::Encounter, "Route 15", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_32, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-13", emulocke::TrackerStopKind::Encounter, "Route 13", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_33, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-14", emulocke::TrackerStopKind::Encounter, "Route 14", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_34, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"lost-tunnel", emulocke::TrackerStopKind::Encounter, "Lost Tunnel", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_35, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"great-desert", emulocke::TrackerStopKind::Encounter, "Great Desert", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_36, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"gurun-town", emulocke::TrackerStopKind::Encounter, "Gurun Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_37, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"vivill-woods", emulocke::TrackerStopKind::Encounter, "Vivill Woods", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_38, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"vivill-town", emulocke::TrackerStopKind::Encounter, "Vivill Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_39, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"vivill-warehouse", emulocke::TrackerStopKind::Encounter, "Vivill Warehouse", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_40, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"lr2-exp", emulocke::TrackerStopKind::Boss, "Ruin Leader Aklove", "Vivill Warehouse", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_59, 6, 1307, 0, 0, 53, 1, false, "", "", false},
    {"route-16", emulocke::TrackerStopKind::Encounter, "Route 16", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_41, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"antisis-city", emulocke::TrackerStopKind::Encounter, "Antisis City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_42, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"antisis-sewers", emulocke::TrackerStopKind::Encounter, "Antisis Sewers", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_43, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-6", emulocke::TrackerStopKind::Boss, "Leader Big Mo", "Antisis City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_63, 5, 0, 0, 6, 53, 1, false, "", "Inverse Gravity Permanent Trick Room effect for weight, heavier Pokemon go first.", false},
    {"icy-hole", emulocke::TrackerStopKind::Encounter, "Icy Hole", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_44, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"seaport-city", emulocke::TrackerStopKind::Encounter, "Seaport City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_45, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"polder-town", emulocke::TrackerStopKind::Encounter, "Polder Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_46, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"safari-zone", emulocke::TrackerStopKind::Encounter, "Safari Zone", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_47, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-7", emulocke::TrackerStopKind::Boss, "Leader Tessy", "Polder Town Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_68, 6, 0, 0, 7, 58, 1, false, "rain", "Camo-mons The Pokemon's types are that of the types of their first two attacks.", false},
    {"cootes-bog", emulocke::TrackerStopKind::Encounter, "Cootes Bog", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_48, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"magnolia-town", emulocke::TrackerStopKind::Encounter, "Magnolia Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_49, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"r5-exp", emulocke::TrackerStopKind::Boss, "Rival Axelford", "Magnolia Town", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_71, 14, 1715, 3, 0, 65, 1, false, "", "", false},
    {"crystal-peak", emulocke::TrackerStopKind::Encounter, "Crystal Peak", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_50, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"lr3-exp", emulocke::TrackerStopKind::Boss, "Ruin Admin Ivory", "Crystal Peak", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_73, 6, 1306, 0, 0, 62, 2, true, "", "", false},
    {"lr4-exp", emulocke::TrackerStopKind::Boss, "Ruin Leader Aklove", "Crystal Peak", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_74, 6, 1307, 0, 0, 62, 1, false, "", "", false},
    {"sh7-exp", emulocke::TrackerStopKind::Boss, "Ex-Shadow Admin Marlon", "Crystal Peak", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_75, 6, 1305, 0, 0, 62, 1, false, "", "", false},
    {"magnolia-fields", emulocke::TrackerStopKind::Encounter, "Magnolia Fields", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_51, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"redwood-village", emulocke::TrackerStopKind::Encounter, "Redwood Village", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_52, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-8", emulocke::TrackerStopKind::Boss, "Leader Benjamin", "Redwood Village Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_78, 6, 0, 0, 8, 62, 1, false, "", "Benjamin Butterfree When a Pokemon is knocked out, instead of fainting it devolves to a previous evolution. The Pokemon finally faints when it can’t devolve anymore.", false},
    {"route-18", emulocke::TrackerStopKind::Encounter, "Route 18", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_53, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"victory-road", emulocke::TrackerStopKind::Encounter, "Victory Road", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_54, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"e1-exp", emulocke::TrackerStopKind::Boss, "Moleman", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_81, 6, 1690, 0, 0, 76, 2, false, "sandstorm", "Vicious Sandstorm Vicious sand causes Pokemon to lose 1/8 of max HP at the end of every turn", false},
    {"e2-exp", emulocke::TrackerStopKind::Boss, "Elias", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_82, 6, 1691, 0, 0, 76, 1, false, "", "Shadowy Veil Every Ghost-type Pokemon take half damage on full HP. Ghost-types are immune to entry hazards at full HP. Other Types cannot use Safeguard or Substitute.", false},
    {"e3-exp", emulocke::TrackerStopKind::Boss, "Arabella", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_83, 6, 1692, 0, 0, 76, 1, false, "misty-terrain", "Fairy ring All Fairy-Type Pokemon get a +1 boost to their lowest Defense stat on switch in.", false},
    {"e4-exp", emulocke::TrackerStopKind::Boss, "Penny", "Pokémon League", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_84, 6, 1693, 0, 0, 76, 2, false, "", "Rainbow Battle All Dragon-type Pokemon on the field have their moves' secondary effect chance doubled. This stacks Serene Grace with the exception of flinching moves.", false},
    {"c-exp", emulocke::TrackerStopKind::Boss, "Jax", "Pokémon League Champion", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_85, 6, 1319, 0, 0, 76, 2, false, "", "", false},
    {"tomb-of-borrius", emulocke::TrackerStopKind::Encounter, "Tomb of Borrius", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_55, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"rift-cave", emulocke::TrackerStopKind::Encounter, "Rift Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_56, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"redwood-forest", emulocke::TrackerStopKind::Encounter, "Redwood Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_57, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"cliff-cave", emulocke::TrackerStopKind::Encounter, "Cliff Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_58, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"cube-corp", emulocke::TrackerStopKind::Encounter, "Cube Corp.", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_unbound_expert_59, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"lr5-exp", emulocke::TrackerStopKind::Boss, "Ruin Leader Aklove", "Ruins of Void", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_unbound_expert_91, 6, 1307, 0, 0, 75, 1, false, "", "", false}
};

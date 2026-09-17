constexpr uint16_t kMet_b2w2_0[] = {117};
constexpr uint16_t kMet_b2w2_1[] = {124};
constexpr uint16_t kMet_b2w2_2[] = {122};
constexpr uint16_t kMet_b2w2_3[] = {125};
constexpr uint16_t kMet_b2w2_4[] = {130};
constexpr uint16_t kMet_b2w2_5[] = {118};
constexpr uint16_t kMet_b2w2_6[] = {131};
constexpr uint16_t kMet_b2w2_7[] = {8};
constexpr uint16_t kMet_b2w2_8[] = {129};
constexpr uint16_t kMet_b2w2_9[] = {136};
constexpr uint16_t kMet_b2w2_10[] = {17};
constexpr uint16_t kMet_b2w2_11[] = {34};
constexpr uint16_t kMet_b2w2_12[] = {35};
constexpr uint16_t kMet_b2w2_13[] = {29};
constexpr uint16_t kMet_b2w2_14[] = {72};
constexpr uint16_t kMet_b2w2_15[] = {18};
constexpr uint16_t kMet_b2w2_16[] = {65};
constexpr uint16_t kMet_b2w2_17[] = {10};
constexpr uint16_t kMet_b2w2_18[] = {19};
constexpr uint16_t kMet_b2w2_19[] = {54};
constexpr uint16_t kMet_b2w2_20[] = {37};
constexpr uint16_t kMet_b2w2_21[] = {20};
constexpr uint16_t kMet_b2w2_22[] = {56};
constexpr uint16_t kMet_b2w2_23[] = {132};
constexpr uint16_t kMet_b2w2_24[] = {133};
constexpr uint16_t kMet_b2w2_25[] = {42};
constexpr uint16_t kMet_b2w2_26[] = {71};
constexpr uint16_t kMet_b2w2_27[] = {26};
constexpr uint16_t kMet_b2w2_28[] = {25};
constexpr uint16_t kMet_b2w2_29[] = {67};
constexpr uint16_t kMet_b2w2_30[] = {24};
constexpr uint16_t kMet_b2w2_31[] = {22};
constexpr uint16_t kMet_b2w2_32[] = {141};
constexpr uint16_t kMet_b2w2_33[] = {126};
constexpr uint16_t kMet_b2w2_34[] = {119};
constexpr uint16_t kMet_b2w2_35[] = {127};
constexpr uint16_t kMet_b2w2_36[] = {61};
constexpr uint16_t kMet_b2w2_37[] = {128};
constexpr uint16_t kMet_b2w2_38[] = {68};
constexpr uint16_t kMet_b2w2_39[] = {28};
constexpr uint16_t kMet_b2w2_40[] = {27};
constexpr uint16_t kMet_b2w2_41[] = {70};
constexpr uint16_t kMet_b2w2_42[] = {57};
constexpr uint16_t kMet_b2w2_43[] = {12};
constexpr uint16_t kMet_b2w2_44[] = {39};
constexpr uint16_t kMet_b2w2_45[] = {38};
constexpr uint16_t kMet_b2w2_46[] = {137};
constexpr uint16_t kMet_b2w2_47[] = {149};
constexpr uint16_t kMet_b2w2_48[] = {33};
constexpr uint16_t kMet_b2w2_49[] = {7};
constexpr uint16_t kMet_b2w2_50[] = {16};
constexpr uint16_t kMet_b2w2_51[] = {53};
constexpr uint16_t kMet_b2w2_52[] = {6};
constexpr uint16_t kMet_b2w2_53[] = {32};
constexpr uint16_t kMet_b2w2_54[] = {15};
constexpr uint16_t kMet_b2w2_55[] = {5};
constexpr uint16_t kMet_b2w2_56[] = {14};
constexpr uint16_t kMet_b2w2_57[] = {30};
constexpr uint16_t kMet_b2w2_58[] = {31};
constexpr uint16_t kMet_b2w2_59[] = {63};
constexpr uint16_t kMet_b2w2_60[] = {147};
constexpr uint16_t kStarters_b2w2[] = {495, 498, 501};
constexpr emulocke::TrackerStop kStops_b2w2[] = {
    {"starter", emulocke::TrackerStopKind::Encounter, "Starter", "", emulocke::BossKind::None, emulocke::CatchKind::Starter, nullptr, 0, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"aspertia-city", emulocke::TrackerStopKind::Encounter, "Aspertia City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_0, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"r1", emulocke::TrackerStopKind::Boss, "Hugh", "Aspertia City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_2, 3, 0, 0, 0, 5, 1, false, "", "", true},
    {"route-19", emulocke::TrackerStopKind::Encounter, "Route 19", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_1, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"floccesy-town", emulocke::TrackerStopKind::Encounter, "Floccesy Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_2, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-20", emulocke::TrackerStopKind::Encounter, "Route 20", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_3, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"floccesy-ranch", emulocke::TrackerStopKind::Encounter, "Floccesy Ranch", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_4, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"r2", emulocke::TrackerStopKind::Boss, "Hugh", "Floccesy Ranch", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_7, 3, 0, 0, 0, 8, 1, false, "", "", false},
    {"1n", emulocke::TrackerStopKind::Boss, "Cheren", "Aspertia City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_8, 2, 0, 0, 1, 13, 1, false, "", "", false},
    {"virbank-city", emulocke::TrackerStopKind::Encounter, "Virbank City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_5, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"2n", emulocke::TrackerStopKind::Boss, "Roxie", "Virbank City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_10, 2, 0, 0, 2, 18, 1, false, "", "", false},
    {"virbank-complex", emulocke::TrackerStopKind::Encounter, "Virbank Complex", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_6, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"castelia-city", emulocke::TrackerStopKind::Encounter, "Castelia City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_7, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"castelia-sewers", emulocke::TrackerStopKind::Encounter, "Castelia Sewers", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_8, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"3n", emulocke::TrackerStopKind::Boss, "Burgh", "Castelia City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_14, 3, 0, 0, 3, 24, 1, false, "", "", false},
    {"relic-passage", emulocke::TrackerStopKind::Encounter, "Relic Passage", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_9, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-4", emulocke::TrackerStopKind::Encounter, "Route 4", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_10, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"col1", emulocke::TrackerStopKind::Boss, "Colress", "Route 4", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_17, 2, 0, 0, 0, 23, 1, false, "", "", false},
    {"desert-resort", emulocke::TrackerStopKind::Encounter, "Desert Resort", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_11, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"relic-castle", emulocke::TrackerStopKind::Encounter, "Relic Castle", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_12, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"subway", emulocke::TrackerStopKind::Boss, "Ingo & Emmet", "Nimbasa Subway", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_20, 2, 0, 0, 0, 26, 1, false, "", "", false},
    {"4n", emulocke::TrackerStopKind::Boss, "Elesa", "Nimbasa City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_21, 3, 0, 0, 4, 30, 1, false, "", "", false},
    {"route-16", emulocke::TrackerStopKind::Encounter, "Route 16", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_13, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"lostlorn-forest", emulocke::TrackerStopKind::Encounter, "Lostlorn Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_14, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-5", emulocke::TrackerStopKind::Encounter, "Route 5", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_15, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"driftveil-drawbridge", emulocke::TrackerStopKind::Encounter, "Driftveil Drawbridge", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_16, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"driftveil-city", emulocke::TrackerStopKind::Encounter, "Driftveil City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_17, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"5n", emulocke::TrackerStopKind::Boss, "Clay", "Driftveil City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_27, 3, 0, 0, 5, 33, 1, false, "", "", false},
    {"r3", emulocke::TrackerStopKind::Boss, "Hugh", "Driftveil Tournament Round 1", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_28, 7, 0, 0, 0, 25, 1, false, "", "", false},
    {"ch", emulocke::TrackerStopKind::Boss, "Cheren", "Driftveil Tournament Round 2", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_29, 3, 0, 0, 0, 25, 1, false, "", "", false},
    {"col2", emulocke::TrackerStopKind::Boss, "Colress", "Driftveil Tournament Round 3", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_30, 3, 0, 0, 0, 25, 1, false, "", "", false},
    {"route-6", emulocke::TrackerStopKind::Encounter, "Route 6", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_18, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"mistralton-cave", emulocke::TrackerStopKind::Encounter, "Mistralton Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_19, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"6n", emulocke::TrackerStopKind::Boss, "Skyla", "Mistralton City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_33, 3, 0, 0, 6, 39, 1, false, "", "", false},
    {"chargestone-cave", emulocke::TrackerStopKind::Encounter, "Chargestone Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_20, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-7", emulocke::TrackerStopKind::Encounter, "Route 7", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_21, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"celestial-tower", emulocke::TrackerStopKind::Encounter, "Celestial Tower", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_22, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"reversal-mountain", emulocke::TrackerStopKind::Encounter, "Reversal Mountain", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_23, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"strange-house", emulocke::TrackerStopKind::Encounter, "Strange House", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_24, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"undella-town", emulocke::TrackerStopKind::Encounter, "Undella Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_25, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"r4", emulocke::TrackerStopKind::Boss, "Hugh", "Undella Town", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_40, 7, 0, 0, 0, 41, 1, false, "", "", false},
    {"undella-bay", emulocke::TrackerStopKind::Encounter, "Undella Bay", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_26, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-13", emulocke::TrackerStopKind::Encounter, "Route 13", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_27, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"zinz1", emulocke::TrackerStopKind::Boss, "Zinzolin & Grunt", "Lacunosa Town", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_43, 4, 0, 0, 0, 44, 1, false, "", "", false},
    {"route-12", emulocke::TrackerStopKind::Encounter, "Route 12", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_28, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"village-bridge", emulocke::TrackerStopKind::Encounter, "Village Bridge", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_29, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-11", emulocke::TrackerStopKind::Encounter, "Route 11", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_30, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-9", emulocke::TrackerStopKind::Encounter, "Route 9", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_31, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"7n", emulocke::TrackerStopKind::Boss, "Drayden", "Opelucid City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_48, 3, 0, 0, 7, 48, 1, false, "", "", false},
    {"zinz2", emulocke::TrackerStopKind::Boss, "Zinzolin", "Opelucid City", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_49, 3, 0, 0, 0, 48, 1, false, "", "", false},
    {"shad", emulocke::TrackerStopKind::Boss, "Shadow", "Opelucid City", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_50, 3, 0, 0, 0, 48, 1, false, "", "", false},
    {"seaside-cave", emulocke::TrackerStopKind::Encounter, "Seaside Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_32, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-21", emulocke::TrackerStopKind::Encounter, "Route 21", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_33, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"humilau-city", emulocke::TrackerStopKind::Encounter, "Humilau City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_34, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"8n", emulocke::TrackerStopKind::Boss, "Marlon", "Humilau City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_54, 3, 0, 0, 8, 51, 1, false, "", "", false},
    {"route-22", emulocke::TrackerStopKind::Encounter, "Route 22", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_35, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"zinz3", emulocke::TrackerStopKind::Boss, "Zinzolin & grunt", "Command Center", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_56, 6, 0, 0, 0, 50, 1, false, "", "", false},
    {"zinz4", emulocke::TrackerStopKind::Boss, "Zinzolin", "Kyurem's Location", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_57, 3, 0, 0, 0, 51, 1, false, "", "", false},
    {"col3", emulocke::TrackerStopKind::Boss, "Colress", "Control Room", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_58, 5, 0, 0, 0, 52, 1, false, "", "", false},
    {"giant-chasm", emulocke::TrackerStopKind::Encounter, "Giant Chasm", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_36, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"ghetsis", emulocke::TrackerStopKind::Boss, "Ghetsis", "Giant Chasm", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_60, 6, 2400, 0, 0, 52, 1, false, "", "", false},
    {"route-23", emulocke::TrackerStopKind::Encounter, "Route 23", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_37, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"victory-road", emulocke::TrackerStopKind::Encounter, "Victory Road", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"r5", emulocke::TrackerStopKind::Boss, "Hugh", "Victory Road", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_63, 8, 0, 0, 0, 57, 1, false, "", "", false},
    {"e1n", emulocke::TrackerStopKind::Boss, "Shauntal", "Pokémon League W Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_64, 4, 0, 0, 0, 58, 1, false, "", "", false},
    {"e2n", emulocke::TrackerStopKind::Boss, "Grimsley", "Pokémon League NW Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_65, 4, 0, 0, 0, 58, 1, false, "", "", false},
    {"e3n", emulocke::TrackerStopKind::Boss, "Caitlin", "Pokémon League NE Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_66, 4, 0, 0, 0, 58, 1, false, "", "", false},
    {"e4n", emulocke::TrackerStopKind::Boss, "Marshal", "Pokémon League E Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_67, 4, 0, 0, 0, 58, 1, false, "", "", false},
    {"cn", emulocke::TrackerStopKind::Boss, "Iris", "Pokémon League Champion", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_b2w2_68, 6, 0, 0, 0, 59, 1, false, "", "", false},
    {"marvelous-bridge", emulocke::TrackerStopKind::Encounter, "Marvelous Bridge", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_38, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-15", emulocke::TrackerStopKind::Encounter, "Route 15", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_39, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-14", emulocke::TrackerStopKind::Encounter, "Route 14", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_40, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"abundant-shrine", emulocke::TrackerStopKind::Encounter, "Abundant Shrine", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_41, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"moor-of-icirrus", emulocke::TrackerStopKind::Encounter, "Moor of Icirrus", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_42, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"icirrus-city", emulocke::TrackerStopKind::Encounter, "Icirrus City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_43, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"dragonspiral-tower", emulocke::TrackerStopKind::Encounter, "Dragonspiral Tower", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_44, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"twist-mountain", emulocke::TrackerStopKind::Encounter, "Twist Mountain", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_45, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"clay-tunnel", emulocke::TrackerStopKind::Encounter, "Clay Tunnel", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_46, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"underground-ruins", emulocke::TrackerStopKind::Encounter, "Underground Ruins", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_47, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"pinwheel-forest", emulocke::TrackerStopKind::Encounter, "Pinwheel Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_48, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"nacrene-city", emulocke::TrackerStopKind::Encounter, "Nacrene City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_49, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-3", emulocke::TrackerStopKind::Encounter, "Route 3", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_50, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"wellspring-cave", emulocke::TrackerStopKind::Encounter, "Wellspring Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_51, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"striaton-city", emulocke::TrackerStopKind::Encounter, "Striaton City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_52, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"dreamyard", emulocke::TrackerStopKind::Encounter, "Dreamyard", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_53, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-2", emulocke::TrackerStopKind::Encounter, "Route 2", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_54, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"accumula-town", emulocke::TrackerStopKind::Encounter, "Accumula Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_55, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-1", emulocke::TrackerStopKind::Encounter, "Route 1", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_56, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-17", emulocke::TrackerStopKind::Encounter, "Route 17", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_57, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-18", emulocke::TrackerStopKind::Encounter, "Route 18", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_58, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"p2-laboratory", emulocke::TrackerStopKind::Encounter, "P2 Laboratory", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_59, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false},
    {"nature-preserve", emulocke::TrackerStopKind::Encounter, "Nature Preserve", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_b2w2_60, 1, nullptr, 0, 0, 0, 0, 0, 1, false, "", "", false}
};

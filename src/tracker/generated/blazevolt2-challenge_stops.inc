constexpr uint16_t kMet_blazevolt2_challenge_0[] = {117};
constexpr uint16_t kMet_blazevolt2_challenge_1[] = {124};
constexpr uint16_t kMet_blazevolt2_challenge_2[] = {122};
constexpr uint16_t kMet_blazevolt2_challenge_3[] = {125};
constexpr uint16_t kMet_blazevolt2_challenge_4[] = {130};
constexpr uint16_t kMet_blazevolt2_challenge_5[] = {118};
constexpr uint16_t kMet_blazevolt2_challenge_6[] = {131};
constexpr uint16_t kMet_blazevolt2_challenge_7[] = {8};
constexpr uint16_t kMet_blazevolt2_challenge_8[] = {129};
constexpr uint16_t kMet_blazevolt2_challenge_9[] = {136};
constexpr uint16_t kMet_blazevolt2_challenge_10[] = {17};
constexpr uint16_t kMet_blazevolt2_challenge_11[] = {34};
constexpr uint16_t kMet_blazevolt2_challenge_12[] = {35};
constexpr uint16_t kMet_blazevolt2_challenge_13[] = {43};
constexpr uint16_t kMet_blazevolt2_challenge_14[] = {18};
constexpr uint16_t kMet_blazevolt2_challenge_15[] = {29};
constexpr uint16_t kMet_blazevolt2_challenge_16[] = {72};
constexpr uint16_t kMet_blazevolt2_challenge_17[] = {65};
constexpr uint16_t kMet_blazevolt2_challenge_18[] = {10};
constexpr uint16_t kMet_blazevolt2_challenge_19[] = {19};
constexpr uint16_t kMet_blazevolt2_challenge_20[] = {137};
constexpr uint16_t kMet_blazevolt2_challenge_21[] = {54};
constexpr uint16_t kMet_blazevolt2_challenge_22[] = {37};
constexpr uint16_t kMet_blazevolt2_challenge_23[] = {20};
constexpr uint16_t kMet_blazevolt2_challenge_24[] = {56};
constexpr uint16_t kMet_blazevolt2_challenge_25[] = {132};
constexpr uint16_t kMet_blazevolt2_challenge_26[] = {133};
constexpr uint16_t kMet_blazevolt2_challenge_27[] = {42};
constexpr uint16_t kMet_blazevolt2_challenge_28[] = {71};
constexpr uint16_t kMet_blazevolt2_challenge_29[] = {27};
constexpr uint16_t kMet_blazevolt2_challenge_30[] = {70};
constexpr uint16_t kMet_blazevolt2_challenge_31[] = {141};
constexpr uint16_t kMet_blazevolt2_challenge_32[] = {26};
constexpr uint16_t kMet_blazevolt2_challenge_33[] = {25};
constexpr uint16_t kMet_blazevolt2_challenge_34[] = {67};
constexpr uint16_t kMet_blazevolt2_challenge_35[] = {24};
constexpr uint16_t kMet_blazevolt2_challenge_36[] = {22};
constexpr uint16_t kMet_blazevolt2_challenge_37[] = {126};
constexpr uint16_t kMet_blazevolt2_challenge_38[] = {119};
constexpr uint16_t kMet_blazevolt2_challenge_39[] = {127};
constexpr uint16_t kMet_blazevolt2_challenge_40[] = {128};
constexpr uint16_t kMet_blazevolt2_challenge_41[] = {57};
constexpr uint16_t kMet_blazevolt2_challenge_42[] = {12};
constexpr uint16_t kMet_blazevolt2_challenge_43[] = {39};
constexpr uint16_t kMet_blazevolt2_challenge_44[] = {38};
constexpr uint16_t kMet_blazevolt2_challenge_45[] = {149};
constexpr uint16_t kMet_blazevolt2_challenge_46[] = {28};
constexpr uint16_t kMet_blazevolt2_challenge_47[] = {33};
constexpr uint16_t kMet_blazevolt2_challenge_48[] = {16};
constexpr uint16_t kMet_blazevolt2_challenge_49[] = {53};
constexpr uint16_t kMet_blazevolt2_challenge_50[] = {32};
constexpr uint16_t kMet_blazevolt2_challenge_51[] = {15};
constexpr uint16_t kMet_blazevolt2_challenge_52[] = {14};
constexpr uint16_t kMet_blazevolt2_challenge_53[] = {30};
constexpr uint16_t kMet_blazevolt2_challenge_54[] = {31};
constexpr uint16_t kMet_blazevolt2_challenge_55[] = {63};
constexpr uint16_t kMet_blazevolt2_challenge_56[] = {147};
constexpr uint16_t kStarters_blazevolt2_challenge[] = {495, 498, 501};
constexpr emulocke::TrackerStop kStops_blazevolt2_challenge[] = {
    {"starter", emulocke::TrackerStopKind::Encounter, "Starter", "", emulocke::BossKind::None, emulocke::CatchKind::Starter, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"aspertia-city", emulocke::TrackerStopKind::Encounter, "Aspertia City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_0, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"r0-c", emulocke::TrackerStopKind::Boss, "Hugh", "Aspertia City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_2, 3, 0, 0, 0, 1, false, "", "", true},
    {"route-19", emulocke::TrackerStopKind::Encounter, "Route 19", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_1, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"floccesy-town", emulocke::TrackerStopKind::Encounter, "Floccesy Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_2, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-20", emulocke::TrackerStopKind::Encounter, "Route 20", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_3, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"floccesy-ranch", emulocke::TrackerStopKind::Encounter, "Floccesy Ranch", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_4, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"r1-c", emulocke::TrackerStopKind::Boss, "Hugh", "Floccesy Ranch", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_7, 7, 0, 0, 0, 1, false, "", "", false},
    {"o1-c", emulocke::TrackerStopKind::Boss, "Roxanne", "Aspertia City Trainer School", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_8, 4, 0, 0, 0, 1, false, "", "", false},
    {"gym-1", emulocke::TrackerStopKind::Boss, "Cheren", "Aspertia City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_9, 6, 0, 0, 1, 1, false, "", "", false},
    {"virbank-city", emulocke::TrackerStopKind::Encounter, "Virbank City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_5, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"o2-c", emulocke::TrackerStopKind::Boss, "Brawly", "Virbank City", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_11, 5, 0, 0, 0, 1, false, "", "", false},
    {"gym-2", emulocke::TrackerStopKind::Boss, "Roxie", "Virbank City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_12, 6, 0, 0, 2, 1, false, "", "", false},
    {"gym-3", emulocke::TrackerStopKind::Boss, "Brycen", "Virbank City", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_13, 4, 0, 0, 3, 1, false, "", "", false},
    {"virbank-complex", emulocke::TrackerStopKind::Encounter, "Virbank Complex", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_6, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"castelia-city", emulocke::TrackerStopKind::Encounter, "Castelia City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_7, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"castelia-sewers", emulocke::TrackerStopKind::Encounter, "Castelia Sewers", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_8, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"o3-c", emulocke::TrackerStopKind::Boss, "Wattson", "Café Sonata", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_17, 6, 0, 0, 0, 1, false, "", "", false},
    {"gym-4", emulocke::TrackerStopKind::Boss, "Burgh", "Castelia City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_18, 6, 0, 0, 4, 2, false, "", "", false},
    {"relic-passage", emulocke::TrackerStopKind::Encounter, "Relic Passage", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_9, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-4", emulocke::TrackerStopKind::Encounter, "Route 4", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_10, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"col1", emulocke::TrackerStopKind::Boss, "Colress", "Route 4", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_21, 5, 0, 0, 0, 1, false, "", "", false},
    {"desert-resort", emulocke::TrackerStopKind::Encounter, "Desert Resort", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_11, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"relic-castle", emulocke::TrackerStopKind::Encounter, "Relic Castle", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_12, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-5", emulocke::TrackerStopKind::Boss, "Lenora", "Nimbasa City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_24, 4, 0, 0, 5, 2, false, "", "", false},
    {"emin", emulocke::TrackerStopKind::Boss, "Ingo & Emmet", "Nimbasa Subway", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_25, 4, 0, 0, 0, 1, false, "", "", false},
    {"natros", emulocke::TrackerStopKind::Boss, "Nate & Rosa", "Nimbasa Subway", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_26, 6, 0, 0, 0, 1, false, "", "", false},
    {"anville-town", emulocke::TrackerStopKind::Encounter, "Anville Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_13, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"o4-c", emulocke::TrackerStopKind::Boss, "Flannery", "Big Stadium", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_28, 6, 0, 0, 0, 1, false, "", "", false},
    {"route-5", emulocke::TrackerStopKind::Encounter, "Route 5", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_14, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-16", emulocke::TrackerStopKind::Encounter, "Route 16", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_15, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"lostlorn-forest", emulocke::TrackerStopKind::Encounter, "Lostlorn Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_16, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-6", emulocke::TrackerStopKind::Boss, "Elesa", "Nimbasa City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_32, 6, 0, 0, 6, 1, false, "", "", false},
    {"charles", emulocke::TrackerStopKind::Boss, "Charles", "Nimbasa City", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_33, 6, 0, 0, 0, 1, false, "", "", false},
    {"driftveil-drawbridge", emulocke::TrackerStopKind::Encounter, "Driftveil Drawbridge", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_17, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"driftveil-city", emulocke::TrackerStopKind::Encounter, "Driftveil City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_18, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-6", emulocke::TrackerStopKind::Encounter, "Route 6", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_19, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"rood", emulocke::TrackerStopKind::Boss, "Rood", "Route 6", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_37, 5, 0, 0, 0, 1, false, "", "", false},
    {"o5-c", emulocke::TrackerStopKind::Boss, "Norman", "Route 6", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_38, 6, 0, 0, 0, 1, false, "", "", false},
    {"clay-tunnel", emulocke::TrackerStopKind::Encounter, "Clay Tunnel", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_20, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-7", emulocke::TrackerStopKind::Boss, "Clay", "Driftveil City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_40, 6, 0, 0, 7, 1, false, "sandstorm", "", false},
    {"r2", emulocke::TrackerStopKind::Boss, "Hugh", "Route 6", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_41, 9, 0, 0, 0, 1, false, "", "", false},
    {"mistralton-cave", emulocke::TrackerStopKind::Encounter, "Mistralton Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_21, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"chargestone-cave", emulocke::TrackerStopKind::Encounter, "Chargestone Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_22, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-7", emulocke::TrackerStopKind::Encounter, "Route 7", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_23, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"celestial-tower", emulocke::TrackerStopKind::Encounter, "Celestial Tower", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_24, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"col2-c", emulocke::TrackerStopKind::Boss, "Colress", "Twist Mountain", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"o6-c", emulocke::TrackerStopKind::Boss, "Juan", "Mistralton City", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_47, 6, 0, 0, 0, 2, false, "rain", "", false},
    {"gym-8", emulocke::TrackerStopKind::Boss, "Skyla", "Mistralton City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_48, 6, 0, 0, 8, 1, false, "", "", false},
    {"reversal-mountain", emulocke::TrackerStopKind::Encounter, "Reversal Mountain", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_25, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"bianca-c", emulocke::TrackerStopKind::Boss, "Bianca", "Reversal Mountain", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_50, 6, 0, 0, 0, 2, false, "", "", false},
    {"strange-house", emulocke::TrackerStopKind::Encounter, "Strange House", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_26, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"undella-town", emulocke::TrackerStopKind::Encounter, "Undella Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_27, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"r3-c", emulocke::TrackerStopKind::Boss, "Hugh", "Undella Town", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_53, 12, 0, 0, 0, 1, false, "", "", false},
    {"undella-bay", emulocke::TrackerStopKind::Encounter, "Undella Bay", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_28, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-14", emulocke::TrackerStopKind::Encounter, "Route 14", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_29, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"abundant-shrine", emulocke::TrackerStopKind::Encounter, "Abundant Shrine", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_30, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"seaside-cave", emulocke::TrackerStopKind::Encounter, "Seaside Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_31, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-13", emulocke::TrackerStopKind::Encounter, "Route 13", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_32, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"zinz1", emulocke::TrackerStopKind::Boss, "Zinzolin & Grunt", "Lacunosa Town", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_59, 5, 0, 0, 0, 2, false, "", "", false},
    {"route-12", emulocke::TrackerStopKind::Encounter, "Route 12", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_33, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"benga-c", emulocke::TrackerStopKind::Boss, "Benga", "Route 12", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_61, 6, 0, 0, 0, 1, false, "", "", false},
    {"village-bridge", emulocke::TrackerStopKind::Encounter, "Village Bridge", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_34, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-11", emulocke::TrackerStopKind::Encounter, "Route 11", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_35, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-9", emulocke::TrackerStopKind::Encounter, "Route 9", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_36, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"o7-c", emulocke::TrackerStopKind::Boss, "Winona", "Opelucid City", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_65, 6, 0, 0, 0, 2, false, "rain", "", false},
    {"gym-9", emulocke::TrackerStopKind::Boss, "Drayden", "Opelucid City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_66, 6, 0, 0, 9, 2, false, "", "", false},
    {"zinz2", emulocke::TrackerStopKind::Boss, "Zinzolin & Grunt", "Opelucid City", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_67, 5, 0, 0, 0, 2, false, "", "", false},
    {"route-21", emulocke::TrackerStopKind::Encounter, "Route 21", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_37, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"humilau-city", emulocke::TrackerStopKind::Encounter, "Humilau City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_38, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"o8-c", emulocke::TrackerStopKind::Boss, "Tate & Liza", "Humilau City", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_70, 8, 0, 0, 0, 2, false, "", "", false},
    {"gym-10", emulocke::TrackerStopKind::Boss, "Marlon", "Humilau City Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_71, 6, 0, 0, 10, 2, false, "rain", "", false},
    {"route-22", emulocke::TrackerStopKind::Encounter, "Route 22", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_39, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"team-plasma-safehouse", emulocke::TrackerStopKind::Encounter, "Team Plasma Safehouse", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"zinz3-c", emulocke::TrackerStopKind::Boss, "Zinzolin & grunt", "Containment Room", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_74, 6, 0, 0, 0, 1, false, "", "", false},
    {"zinz4-c", emulocke::TrackerStopKind::Boss, "Zinzolin", "Plasma Frigate", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_75, 6, 0, 0, 0, 1, false, "", "", false},
    {"col3-c", emulocke::TrackerStopKind::Boss, "Colress", "Plasma Frigate", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_76, 6, 0, 0, 0, 1, false, "", "", false},
    {"giants-chasm", emulocke::TrackerStopKind::Encounter, "Giants Chasm", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"ghetsis-c", emulocke::TrackerStopKind::Boss, "Ghetsis", "Giant Chasm", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_78, 6, 2400, 0, 0, 1, false, "", "", false},
    {"route-23", emulocke::TrackerStopKind::Encounter, "Route 23", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_40, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"o9-hail", emulocke::TrackerStopKind::Boss, "Hail Trainer Caroll", "Victory Road", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_80, 6, 0, 0, 0, 1, false, "", "", false},
    {"o9-sun", emulocke::TrackerStopKind::Boss, "Sun Trainer Elmer", "Victory Road", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_81, 6, 0, 0, 0, 1, false, "", "", false},
    {"o9-rain", emulocke::TrackerStopKind::Boss, "Rain Trainer Porta", "Victory Road", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_82, 6, 0, 0, 0, 1, false, "", "", false},
    {"o9-sand", emulocke::TrackerStopKind::Boss, "Sand Trainer Sterling", "Victory Road", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_83, 6, 0, 0, 0, 1, false, "", "", false},
    {"victory-road", emulocke::TrackerStopKind::Encounter, "Victory Road", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"r4-c", emulocke::TrackerStopKind::Boss, "Hugh", "Victory Road", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_85, 12, 0, 0, 0, 1, false, "", "", false},
    {"e1-c", emulocke::TrackerStopKind::Boss, "Shauntal", "Pokémon League W Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_86, 6, 0, 0, 0, 1, false, "", "", false},
    {"e2-c", emulocke::TrackerStopKind::Boss, "Grimsley", "Pokémon League NW Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_87, 6, 0, 0, 0, 1, false, "", "", false},
    {"e3-c", emulocke::TrackerStopKind::Boss, "Caitlin", "Pokémon League NE Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_88, 6, 0, 0, 0, 2, false, "", "", false},
    {"e4-c", emulocke::TrackerStopKind::Boss, "Marshal", "Pokémon League E Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_89, 6, 0, 0, 0, 2, false, "", "", false},
    {"champ-c", emulocke::TrackerStopKind::Boss, "Iris", "Pokémon League Champion", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_blazevolt2_challenge_90, 6, 0, 0, 0, 1, false, "", "", false},
    {"moor-of-icirrus", emulocke::TrackerStopKind::Encounter, "Moor of Icirrus", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_41, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"icirrus-city", emulocke::TrackerStopKind::Encounter, "Icirrus City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_42, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"dragonspiral-tower", emulocke::TrackerStopKind::Encounter, "Dragonspiral Tower", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_43, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"twist-mountain", emulocke::TrackerStopKind::Encounter, "Twist Mountain", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_44, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"underground-ruins", emulocke::TrackerStopKind::Encounter, "Underground Ruins", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_45, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"marvellous-bridge", emulocke::TrackerStopKind::Encounter, "Marvellous Bridge", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-15", emulocke::TrackerStopKind::Encounter, "Route 15", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_46, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"pinwheel-forest", emulocke::TrackerStopKind::Encounter, "Pinwheel Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_47, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-3", emulocke::TrackerStopKind::Encounter, "Route 3", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_48, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"wellspring-cave", emulocke::TrackerStopKind::Encounter, "Wellspring Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_49, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"striation-city", emulocke::TrackerStopKind::Encounter, "Striation City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"dreamyard", emulocke::TrackerStopKind::Encounter, "Dreamyard", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_50, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-2", emulocke::TrackerStopKind::Encounter, "Route 2", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_51, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-1", emulocke::TrackerStopKind::Encounter, "Route 1", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_52, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-17", emulocke::TrackerStopKind::Encounter, "Route 17", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_53, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-18", emulocke::TrackerStopKind::Encounter, "Route 18", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_54, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"p2-laboratory", emulocke::TrackerStopKind::Encounter, "P2 Laboratory", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_55, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"nature-preserve", emulocke::TrackerStopKind::Encounter, "Nature Preserve", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blazevolt2_challenge_56, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false}
};

constexpr uint16_t kMet_blaze_0[] = {14};
constexpr uint16_t kMet_blaze_1[] = {15};
constexpr uint16_t kMet_blaze_2[] = {6};
constexpr uint16_t kMet_blaze_3[] = {32};
constexpr uint16_t kMet_blaze_4[] = {16};
constexpr uint16_t kMet_blaze_5[] = {53};
constexpr uint16_t kMet_blaze_6[] = {7};
constexpr uint16_t kMet_blaze_7[] = {33};
constexpr uint16_t kMet_blaze_8[] = {62};
constexpr uint16_t kMet_blaze_9[] = {17};
constexpr uint16_t kMet_blaze_10[] = {34};
constexpr uint16_t kMet_blaze_11[] = {35};
constexpr uint16_t kMet_blaze_12[] = {29};
constexpr uint16_t kMet_blaze_13[] = {18};
constexpr uint16_t kMet_blaze_14[] = {72};
constexpr uint16_t kMet_blaze_15[] = {10};
constexpr uint16_t kMet_blaze_16[] = {19};
constexpr uint16_t kMet_blaze_17[] = {37};
constexpr uint16_t kMet_blaze_18[] = {20};
constexpr uint16_t kMet_blaze_19[] = {56};
constexpr uint16_t kMet_blaze_20[] = {30};
constexpr uint16_t kMet_blaze_21[] = {31};
constexpr uint16_t kMet_blaze_22[] = {63};
constexpr uint16_t kMet_blaze_23[] = {54};
constexpr uint16_t kMet_blaze_24[] = {38};
constexpr uint16_t kMet_blaze_25[] = {21};
constexpr uint16_t kMet_blaze_26[] = {57};
constexpr uint16_t kMet_blaze_27[] = {39};
constexpr uint16_t kMet_blaze_28[] = {22};
constexpr uint16_t kMet_blaze_29[] = {23};
constexpr uint16_t kMet_blaze_30[] = {45};
constexpr uint16_t kMet_blaze_31[] = {24};
constexpr uint16_t kMet_blaze_32[] = {67};
constexpr uint16_t kMet_blaze_33[] = {25};
constexpr uint16_t kMet_blaze_34[] = {26};
constexpr uint16_t kMet_blaze_35[] = {61};
constexpr uint16_t kMet_blaze_36[] = {42};
constexpr uint16_t kMet_blaze_37[] = {71};
constexpr uint16_t kMet_blaze_38[] = {27};
constexpr uint16_t kMet_blaze_39[] = {70};
constexpr uint16_t kMet_blaze_40[] = {51};
constexpr uint16_t kMet_blaze_41[] = {28};
constexpr uint16_t kMet_blaze_42[] = {68};
constexpr uint16_t kMet_blaze_43[] = {59};
constexpr uint16_t kStarters_blaze[] = {495, 498, 501};
constexpr emulocke::TrackerStop kStops_blaze[] = {
    {"starter", emulocke::TrackerStopKind::Encounter, "Starter", "", emulocke::BossKind::None, emulocke::CatchKind::Starter, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"b1", emulocke::TrackerStopKind::Boss, "Bianca", "Nuvema Town", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_1, 3, 0, 0, 0},
    {"c1", emulocke::TrackerStopKind::Boss, "Cheren", "Nuvema Town", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_2, 3, 0, 0, 0},
    {"route-1", emulocke::TrackerStopKind::Encounter, "Route 1", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_0, 1, nullptr, 0, 0, 0, 0},
    {"n1", emulocke::TrackerStopKind::Boss, "N", "Accumula Town", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_4, 3, 0, 0, 0},
    {"route-2", emulocke::TrackerStopKind::Encounter, "Route 2", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_1, 1, nullptr, 0, 0, 0, 0},
    {"b2", emulocke::TrackerStopKind::Boss, "Bianca", "Route 2", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_6, 4, 0, 0, 0},
    {"striaton-city", emulocke::TrackerStopKind::Encounter, "Striaton City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_2, 1, nullptr, 0, 0, 0, 0},
    {"c2", emulocke::TrackerStopKind::Boss, "Cheren", "Tranier's School", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_8, 4, 0, 0, 0},
    {"gym-1", emulocke::TrackerStopKind::Boss, "Chili, Cress or Cilan", "Striaton Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_9, 18, 0, 0, 1},
    {"dreamyard", emulocke::TrackerStopKind::Encounter, "Dreamyard", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_3, 1, nullptr, 0, 0, 0, 0},
    {"route-3", emulocke::TrackerStopKind::Encounter, "Route 3", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_4, 1, nullptr, 0, 0, 0, 0},
    {"c3", emulocke::TrackerStopKind::Boss, "Cheren", "Preschool", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_12, 8, 0, 0, 0},
    {"wellspring-cave", emulocke::TrackerStopKind::Encounter, "Wellspring Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_5, 1, nullptr, 0, 0, 0, 0},
    {"nacrene-city", emulocke::TrackerStopKind::Encounter, "Nacrene City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_6, 1, nullptr, 0, 0, 0, 0},
    {"n2", emulocke::TrackerStopKind::Boss, "N", "Nacrene City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_15, 5, 0, 0, 0},
    {"gym-2", emulocke::TrackerStopKind::Boss, "Lenora", "Nacrene Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_16, 6, 0, 0, 2},
    {"pinwheel-forest", emulocke::TrackerStopKind::Encounter, "Pinwheel Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_7, 1, nullptr, 0, 0, 0, 0},
    {"liberty-garden", emulocke::TrackerStopKind::Encounter, "Liberty Garden", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_8, 1, nullptr, 0, 0, 0, 0},
    {"gym-3", emulocke::TrackerStopKind::Boss, "Burgh", "Castelia Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_19, 6, 0, 0, 3},
    {"b3", emulocke::TrackerStopKind::Boss, "Bianca", "Castelia City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_20, 8, 0, 0, 0},
    {"route-4", emulocke::TrackerStopKind::Encounter, "Route 4", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_9, 1, nullptr, 0, 0, 0, 0},
    {"c4", emulocke::TrackerStopKind::Boss, "Cheren", "Route 4", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_22, 9, 0, 0, 0},
    {"desert-resort", emulocke::TrackerStopKind::Encounter, "Desert Resort", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_10, 1, nullptr, 0, 0, 0, 0},
    {"relic-castle", emulocke::TrackerStopKind::Encounter, "Relic Castle", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_11, 1, nullptr, 0, 0, 0, 0},
    {"n3", emulocke::TrackerStopKind::Boss, "N", "Nimbasa City", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_25, 6, 0, 0, 0},
    {"gym-4", emulocke::TrackerStopKind::Boss, "Elesa", "Nimbasa Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_26, 6, 0, 0, 4},
    {"route-16", emulocke::TrackerStopKind::Encounter, "Route 16", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_12, 1, nullptr, 0, 0, 0, 0},
    {"route-5", emulocke::TrackerStopKind::Encounter, "Route 5", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_13, 1, nullptr, 0, 0, 0, 0},
    {"c5", emulocke::TrackerStopKind::Boss, "Cheren", "Route 5", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_29, 9, 0, 0, 0},
    {"lostlorn-forest", emulocke::TrackerStopKind::Encounter, "Lostlorn Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_14, 1, nullptr, 0, 0, 0, 0},
    {"cold-storage", emulocke::TrackerStopKind::Encounter, "Cold Storage", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"driftveil-drawbidge", emulocke::TrackerStopKind::Encounter, "Driftveil Drawbidge", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"driftveil-city", emulocke::TrackerStopKind::Encounter, "Driftveil City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_15, 1, nullptr, 0, 0, 0, 0},
    {"gym-5", emulocke::TrackerStopKind::Boss, "Clay", "Driftveil Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_34, 6, 0, 0, 5},
    {"b4", emulocke::TrackerStopKind::Boss, "Bianca", "Driftveil City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_35, 9, 0, 0, 0},
    {"route-6", emulocke::TrackerStopKind::Encounter, "Route 6", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_16, 1, nullptr, 0, 0, 0, 0},
    {"chargestone-cave", emulocke::TrackerStopKind::Encounter, "Chargestone Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_17, 1, nullptr, 0, 0, 0, 0},
    {"n4", emulocke::TrackerStopKind::Boss, "N", "Chargestone Cave", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_38, 6, 0, 0, 0},
    {"route-7", emulocke::TrackerStopKind::Encounter, "Route 7", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_18, 1, nullptr, 0, 0, 0, 0},
    {"celestial-tower", emulocke::TrackerStopKind::Encounter, "Celestial Tower", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_19, 1, nullptr, 0, 0, 0, 0},
    {"gym-6", emulocke::TrackerStopKind::Boss, "Skyla", "Mistralton Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_41, 6, 0, 0, 6},
    {"route-17", emulocke::TrackerStopKind::Encounter, "Route 17", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_20, 1, nullptr, 0, 0, 0, 0},
    {"route-18", emulocke::TrackerStopKind::Encounter, "Route 18", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_21, 1, nullptr, 0, 0, 0, 0},
    {"p2-laboratory", emulocke::TrackerStopKind::Encounter, "P2 Laboratory", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_22, 1, nullptr, 0, 0, 0, 0},
    {"mistralton-cave", emulocke::TrackerStopKind::Encounter, "Mistralton Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_23, 1, nullptr, 0, 0, 0, 0},
    {"twist-mountain", emulocke::TrackerStopKind::Encounter, "Twist Mountain", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_24, 1, nullptr, 0, 0, 0, 0},
    {"c6", emulocke::TrackerStopKind::Boss, "Cheren", "Twist Mountain", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_47, 12, 0, 0, 0},
    {"iccirus-city", emulocke::TrackerStopKind::Encounter, "Iccirus City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"gym-7", emulocke::TrackerStopKind::Boss, "Brycen", "Iccirus Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_49, 6, 0, 0, 7},
    {"route-8", emulocke::TrackerStopKind::Encounter, "Route 8", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_25, 1, nullptr, 0, 0, 0, 0},
    {"b5", emulocke::TrackerStopKind::Boss, "Bianca", "Route 8", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_51, 12, 0, 0, 0},
    {"moor-of-icirrus", emulocke::TrackerStopKind::Encounter, "Moor of Icirrus", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_26, 1, nullptr, 0, 0, 0, 0},
    {"dragonspiral-tower", emulocke::TrackerStopKind::Encounter, "Dragonspiral Tower", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_27, 1, nullptr, 0, 0, 0, 0},
    {"route-9", emulocke::TrackerStopKind::Encounter, "Route 9", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_28, 1, nullptr, 0, 0, 0, 0},
    {"8a", emulocke::TrackerStopKind::Boss, "Drayden", "Opelucid Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_55, 6, 0, 0, 0},
    {"route-10", emulocke::TrackerStopKind::Encounter, "Route 10", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_29, 1, nullptr, 0, 0, 0, 0},
    {"c7", emulocke::TrackerStopKind::Boss, "Cheren", "Route 10", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_57, 12, 0, 0, 0},
    {"victory-road", emulocke::TrackerStopKind::Encounter, "Victory Road", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0},
    {"e1", emulocke::TrackerStopKind::Boss, "Shauntal", "Pokémon League W Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_59, 6, 0, 0, 0},
    {"e2", emulocke::TrackerStopKind::Boss, "Grimsley", "Pokémon League NW Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_60, 6, 0, 0, 0},
    {"e3", emulocke::TrackerStopKind::Boss, "Caitlin", "Pokémon League NE Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_61, 6, 0, 0, 0},
    {"e4", emulocke::TrackerStopKind::Boss, "Caitlin", "Pokémon League E Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_62, 6, 0, 0, 0},
    {"ns-castle", emulocke::TrackerStopKind::Encounter, "N's Castle", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_30, 1, nullptr, 0, 0, 0, 0},
    {"n5a", emulocke::TrackerStopKind::Boss, "N", "N's Castle", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_64, 6, 0, 0, 0},
    {"gh", emulocke::TrackerStopKind::Boss, "Ghetsis", "N's Castle", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_65, 6, 0, 0, 0},
    {"route-11", emulocke::TrackerStopKind::Encounter, "Route 11", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_31, 1, nullptr, 0, 0, 0, 0},
    {"village-bridge", emulocke::TrackerStopKind::Encounter, "Village Bridge", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_32, 1, nullptr, 0, 0, 0, 0},
    {"route-12", emulocke::TrackerStopKind::Encounter, "Route 12", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_33, 1, nullptr, 0, 0, 0, 0},
    {"route-13", emulocke::TrackerStopKind::Encounter, "Route 13", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_34, 1, nullptr, 0, 0, 0, 0},
    {"giant-chasm", emulocke::TrackerStopKind::Encounter, "Giant Chasm", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_35, 1, nullptr, 0, 0, 0, 0},
    {"undella-town", emulocke::TrackerStopKind::Encounter, "Undella Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_36, 1, nullptr, 0, 0, 0, 0},
    {"ch1", emulocke::TrackerStopKind::Boss, "Cynthia", "Undella Town", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_72, 6, 0, 0, 0},
    {"undella-bay", emulocke::TrackerStopKind::Encounter, "Undella Bay", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_37, 1, nullptr, 0, 0, 0, 0},
    {"route-14", emulocke::TrackerStopKind::Encounter, "Route 14", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_38, 1, nullptr, 0, 0, 0, 0},
    {"abundant-shrine", emulocke::TrackerStopKind::Encounter, "Abundant Shrine", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_39, 1, nullptr, 0, 0, 0, 0},
    {"white-forest", emulocke::TrackerStopKind::Encounter, "White Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_40, 1, nullptr, 0, 0, 0, 0},
    {"e5", emulocke::TrackerStopKind::Boss, "Shauntal", "Pokémon League W Room (Round 2)", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_77, 6, 0, 0, 0},
    {"e6", emulocke::TrackerStopKind::Boss, "Grimsley", "Pokémon League NW Room (Round 2)", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_78, 6, 0, 0, 0},
    {"e7", emulocke::TrackerStopKind::Boss, "Caitlin", "Pokémon League NE Room (Round 2)", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_79, 6, 0, 0, 0},
    {"e8", emulocke::TrackerStopKind::Boss, "Marshal", "Pokémon League E Room (Round 2)", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_80, 6, 0, 0, 0},
    {"ch2", emulocke::TrackerStopKind::Boss, "Alder", "Pokémon League Champion", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_blaze_81, 6, 0, 0, 0},
    {"route-15", emulocke::TrackerStopKind::Encounter, "Route 15", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_41, 1, nullptr, 0, 0, 0, 0},
    {"marvelous-bridge", emulocke::TrackerStopKind::Encounter, "Marvelous Bridge", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_42, 1, nullptr, 0, 0, 0, 0},
    {"challengers-cave", emulocke::TrackerStopKind::Encounter, "Challenger's Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_blaze_43, 1, nullptr, 0, 0, 0, 0}
};

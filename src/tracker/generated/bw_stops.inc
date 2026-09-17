constexpr uint16_t kMet_bw_0[] = {14};
constexpr uint16_t kMet_bw_1[] = {15};
constexpr uint16_t kMet_bw_2[] = {6};
constexpr uint16_t kMet_bw_3[] = {32};
constexpr uint16_t kMet_bw_4[] = {16};
constexpr uint16_t kMet_bw_5[] = {53};
constexpr uint16_t kMet_bw_6[] = {7};
constexpr uint16_t kMet_bw_7[] = {33};
constexpr uint16_t kMet_bw_8[] = {8};
constexpr uint16_t kMet_bw_9[] = {17};
constexpr uint16_t kMet_bw_10[] = {34};
constexpr uint16_t kMet_bw_11[] = {35};
constexpr uint16_t kMet_bw_12[] = {18};
constexpr uint16_t kMet_bw_13[] = {65};
constexpr uint16_t kMet_bw_14[] = {10};
constexpr uint16_t kMet_bw_15[] = {19};
constexpr uint16_t kMet_bw_16[] = {54};
constexpr uint16_t kMet_bw_17[] = {37};
constexpr uint16_t kMet_bw_18[] = {20};
constexpr uint16_t kMet_bw_19[] = {30};
constexpr uint16_t kMet_bw_20[] = {31};
constexpr uint16_t kMet_bw_21[] = {63};
constexpr uint16_t kMet_bw_22[] = {56};
constexpr uint16_t kMet_bw_23[] = {38};
constexpr uint16_t kMet_bw_24[] = {39};
constexpr uint16_t kMet_bw_25[] = {21};
constexpr uint16_t kMet_bw_26[] = {57};
constexpr uint16_t kMet_bw_27[] = {22};
constexpr uint16_t kMet_bw_28[] = {23};
constexpr uint16_t kMet_bw_29[] = {24};
constexpr uint16_t kMet_bw_30[] = {67};
constexpr uint16_t kMet_bw_31[] = {25};
constexpr uint16_t kMet_bw_32[] = {26};
constexpr uint16_t kMet_bw_33[] = {42};
constexpr uint16_t kMet_bw_34[] = {71};
constexpr uint16_t kMet_bw_35[] = {27};
constexpr uint16_t kMet_bw_36[] = {70};
constexpr uint16_t kMet_bw_37[] = {51};
constexpr uint16_t kMet_bw_38[] = {28};
constexpr uint16_t kMet_bw_39[] = {68};
constexpr uint16_t kMet_bw_40[] = {72};
constexpr uint16_t kMet_bw_41[] = {62};
constexpr uint16_t kMet_bw_42[] = {29};
constexpr uint16_t kStarters_bw[] = {495, 498, 501};
constexpr emulocke::TrackerStop kStops_bw[] = {
    {"starter", emulocke::TrackerStopKind::Encounter, "Starter", "", emulocke::BossKind::None, emulocke::CatchKind::Starter, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"b1", emulocke::TrackerStopKind::Boss, "Bianca", "Nuvema Town", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_1, 3, 0, 0, 0, 1, false, "", "", true},
    {"c1", emulocke::TrackerStopKind::Boss, "Cheren", "Nuvema Town", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_2, 3, 0, 0, 0, 1, false, "", "", true},
    {"route-1", emulocke::TrackerStopKind::Encounter, "Route 1", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_0, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"n1", emulocke::TrackerStopKind::Boss, "N", "Accumula Town", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_4, 1, 0, 0, 0, 1, false, "", "", false},
    {"route-2", emulocke::TrackerStopKind::Encounter, "Route 2", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_1, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"b2", emulocke::TrackerStopKind::Boss, "Bianca", "Route 2", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_6, 4, 0, 0, 0, 1, false, "", "", false},
    {"striaton-city", emulocke::TrackerStopKind::Encounter, "Striaton City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_2, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"c2", emulocke::TrackerStopKind::Boss, "Cheren", "Tranier's School", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_8, 4, 0, 0, 0, 1, false, "", "", false},
    {"gym-1", emulocke::TrackerStopKind::Boss, "Chili, Cress or Cilan", "Striaton Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_9, 4, 0, 0, 1, 1, false, "", "", false},
    {"dreamyard", emulocke::TrackerStopKind::Encounter, "Dreamyard", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_3, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-3", emulocke::TrackerStopKind::Encounter, "Route 3", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_4, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"c3", emulocke::TrackerStopKind::Boss, "Cheren", "Preschool", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_12, 4, 0, 0, 0, 1, false, "", "", false},
    {"wellspring-cave", emulocke::TrackerStopKind::Encounter, "Wellspring Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_5, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"nacrene-city", emulocke::TrackerStopKind::Encounter, "Nacrene City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_6, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"n2", emulocke::TrackerStopKind::Boss, "N", "Nacrene City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_15, 3, 0, 0, 0, 1, false, "", "", false},
    {"gym-2", emulocke::TrackerStopKind::Boss, "Lenora", "Nacrene Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_16, 2, 0, 0, 2, 1, false, "", "", false},
    {"pinwheel-forest", emulocke::TrackerStopKind::Encounter, "Pinwheel Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_7, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"castelia-city", emulocke::TrackerStopKind::Encounter, "Castelia City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_8, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-3", emulocke::TrackerStopKind::Boss, "Burgh", "Castelia Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_19, 3, 0, 0, 3, 1, false, "", "", false},
    {"b3", emulocke::TrackerStopKind::Boss, "Bianca", "Castelia City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_20, 8, 0, 0, 0, 1, false, "", "", false},
    {"route-4", emulocke::TrackerStopKind::Encounter, "Route 4", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_9, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"c4", emulocke::TrackerStopKind::Boss, "Cheren", "Route 4", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_22, 8, 0, 0, 0, 1, false, "", "", false},
    {"desert-resort", emulocke::TrackerStopKind::Encounter, "Desert Resort", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_10, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"relic-castle", emulocke::TrackerStopKind::Encounter, "Relic Castle", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_11, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"n3", emulocke::TrackerStopKind::Boss, "N", "Nimbasa City", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_25, 4, 0, 0, 0, 1, false, "", "", false},
    {"gym-4", emulocke::TrackerStopKind::Boss, "Elesa", "Nimbasa Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_26, 3, 0, 0, 4, 1, false, "", "", false},
    {"route-5", emulocke::TrackerStopKind::Encounter, "Route 5", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_12, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"c5", emulocke::TrackerStopKind::Boss, "Cheren", "Route 5", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_28, 8, 0, 0, 0, 1, false, "", "", false},
    {"driftveil-drawbridge", emulocke::TrackerStopKind::Encounter, "Driftveil Drawbridge", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_13, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"driftveil-city", emulocke::TrackerStopKind::Encounter, "Driftveil City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_14, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"cold-storage", emulocke::TrackerStopKind::Encounter, "Cold Storage", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-5", emulocke::TrackerStopKind::Boss, "Clay", "Driftveil Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_32, 3, 0, 0, 5, 1, false, "", "", false},
    {"b4", emulocke::TrackerStopKind::Boss, "Bianca", "Driftveil City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_33, 8, 0, 0, 0, 1, false, "", "", false},
    {"route-6", emulocke::TrackerStopKind::Encounter, "Route 6", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_15, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"mistralton-cave", emulocke::TrackerStopKind::Encounter, "Mistralton Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_16, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"chargestone-cave", emulocke::TrackerStopKind::Encounter, "Chargestone Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_17, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"n4", emulocke::TrackerStopKind::Boss, "N", "Chargestone Cave", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_37, 4, 0, 0, 0, 1, false, "", "", false},
    {"route-7", emulocke::TrackerStopKind::Encounter, "Route 7", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_18, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-6", emulocke::TrackerStopKind::Boss, "Skyla", "Mistralton Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_39, 3, 0, 0, 6, 1, false, "", "", false},
    {"c55", emulocke::TrackerStopKind::Boss, "Cheren", "Route 7", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_40, 8, 0, 0, 0, 1, false, "", "", false},
    {"route-17", emulocke::TrackerStopKind::Encounter, "Route 17", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_19, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-18", emulocke::TrackerStopKind::Encounter, "Route 18", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_20, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"p2-laboratory", emulocke::TrackerStopKind::Encounter, "P2 Laboratory", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_21, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"celestial-tower", emulocke::TrackerStopKind::Encounter, "Celestial Tower", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_22, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"twist-mountain", emulocke::TrackerStopKind::Encounter, "Twist Mountain", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_23, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"iccirus-city", emulocke::TrackerStopKind::Encounter, "Iccirus City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-7", emulocke::TrackerStopKind::Boss, "Brycen", "Iccirus Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_47, 3, 0, 0, 7, 1, false, "", "", false},
    {"dragonspiral-tower", emulocke::TrackerStopKind::Encounter, "Dragonspiral Tower", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_24, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-8", emulocke::TrackerStopKind::Encounter, "Route 8", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_25, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"b5", emulocke::TrackerStopKind::Boss, "Bianca", "Route 8", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_50, 8, 0, 0, 0, 1, false, "", "", false},
    {"moor-of-icirrus", emulocke::TrackerStopKind::Encounter, "Moor of Icirrus", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_26, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-9", emulocke::TrackerStopKind::Encounter, "Route 9", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_27, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"8a", emulocke::TrackerStopKind::Boss, "Drayden", "Opelucid Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_53, 3, 0, 0, 8, 1, false, "", "", false},
    {"route-10", emulocke::TrackerStopKind::Encounter, "Route 10", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_28, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"c6", emulocke::TrackerStopKind::Boss, "Cheren", "Route 10", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_55, 8, 0, 0, 0, 1, false, "", "", false},
    {"victory-road", emulocke::TrackerStopKind::Encounter, "Victory Road", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"e1", emulocke::TrackerStopKind::Boss, "Shauntal", "Pokémon League W Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_57, 4, 0, 0, 0, 1, false, "", "", false},
    {"e2", emulocke::TrackerStopKind::Boss, "Grimsley", "Pokémon League NW Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_58, 4, 0, 0, 0, 1, false, "", "", false},
    {"e3", emulocke::TrackerStopKind::Boss, "Caitlin", "Pokémon League NE Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_59, 4, 0, 0, 0, 1, false, "", "", false},
    {"e4", emulocke::TrackerStopKind::Boss, "Caitlin", "Pokémon League E Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_60, 4, 0, 0, 0, 1, false, "", "", false},
    {"n5a", emulocke::TrackerStopKind::Boss, "N", "N's Castle", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_61, 6, 0, 0, 0, 1, false, "", "", false},
    {"gh", emulocke::TrackerStopKind::Boss, "Ghetsis", "N's Castle", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_62, 6, 2400, 0, 0, 1, false, "", "", false},
    {"c7", emulocke::TrackerStopKind::Boss, "Cheren", "Victory Road", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_63, 10, 0, 0, 0, 1, false, "", "", false},
    {"e5", emulocke::TrackerStopKind::Boss, "Shauntal", "Pokémon League W Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_64, 6, 0, 0, 0, 1, false, "", "", false},
    {"e6", emulocke::TrackerStopKind::Boss, "Grimsley", "Pokémon League NW Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_65, 6, 0, 0, 0, 1, false, "", "", false},
    {"e7", emulocke::TrackerStopKind::Boss, "Caitlin", "Pokémon League NE Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_66, 6, 0, 0, 0, 1, false, "", "", false},
    {"e8", emulocke::TrackerStopKind::Boss, "Marshal", "Pokémon League E Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_67, 6, 0, 0, 0, 1, false, "", "", false},
    {"c", emulocke::TrackerStopKind::Boss, "Alder", "Pokémon League Champion", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_68, 6, 0, 0, 0, 1, false, "", "", false},
    {"route-11", emulocke::TrackerStopKind::Encounter, "Route 11", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_29, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"village-bridge", emulocke::TrackerStopKind::Encounter, "Village Bridge", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_30, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-12", emulocke::TrackerStopKind::Encounter, "Route 12", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_31, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-13", emulocke::TrackerStopKind::Encounter, "Route 13", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_32, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"undella-town", emulocke::TrackerStopKind::Encounter, "Undella Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_33, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"cc", emulocke::TrackerStopKind::Boss, "Cynthia", "Undella Town", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_74, 6, 0, 0, 0, 1, false, "", "", false},
    {"undella-bay", emulocke::TrackerStopKind::Encounter, "Undella Bay", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_34, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-14", emulocke::TrackerStopKind::Encounter, "Route 14", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_35, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"abundant-shrine", emulocke::TrackerStopKind::Encounter, "Abundant Shrine", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_36, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"white-forest", emulocke::TrackerStopKind::Encounter, "White Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_37, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-15", emulocke::TrackerStopKind::Encounter, "Route 15", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_38, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"marvelous-bridge", emulocke::TrackerStopKind::Encounter, "Marvelous Bridge", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_39, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"lostlorn-forest", emulocke::TrackerStopKind::Encounter, "Lostlorn Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_40, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"liberty-garden", emulocke::TrackerStopKind::Encounter, "Liberty Garden", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_41, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-16", emulocke::TrackerStopKind::Encounter, "Route 16", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_bw_42, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"morimoto", emulocke::TrackerStopKind::Boss, "Morimoto", "Castelia City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_bw_84, 6, 0, 0, 0, 1, false, "", "", false}
};

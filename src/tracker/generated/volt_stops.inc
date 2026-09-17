constexpr uint16_t kMet_volt_0[] = {14};
constexpr uint16_t kMet_volt_1[] = {15};
constexpr uint16_t kMet_volt_2[] = {6};
constexpr uint16_t kMet_volt_3[] = {32};
constexpr uint16_t kMet_volt_4[] = {16};
constexpr uint16_t kMet_volt_5[] = {53};
constexpr uint16_t kMet_volt_6[] = {7};
constexpr uint16_t kMet_volt_7[] = {33};
constexpr uint16_t kMet_volt_8[] = {62};
constexpr uint16_t kMet_volt_9[] = {17};
constexpr uint16_t kMet_volt_10[] = {34};
constexpr uint16_t kMet_volt_11[] = {35};
constexpr uint16_t kMet_volt_12[] = {29};
constexpr uint16_t kMet_volt_13[] = {18};
constexpr uint16_t kMet_volt_14[] = {72};
constexpr uint16_t kMet_volt_15[] = {10};
constexpr uint16_t kMet_volt_16[] = {19};
constexpr uint16_t kMet_volt_17[] = {37};
constexpr uint16_t kMet_volt_18[] = {20};
constexpr uint16_t kMet_volt_19[] = {56};
constexpr uint16_t kMet_volt_20[] = {30};
constexpr uint16_t kMet_volt_21[] = {31};
constexpr uint16_t kMet_volt_22[] = {63};
constexpr uint16_t kMet_volt_23[] = {54};
constexpr uint16_t kMet_volt_24[] = {38};
constexpr uint16_t kMet_volt_25[] = {21};
constexpr uint16_t kMet_volt_26[] = {57};
constexpr uint16_t kMet_volt_27[] = {39};
constexpr uint16_t kMet_volt_28[] = {22};
constexpr uint16_t kMet_volt_29[] = {23};
constexpr uint16_t kMet_volt_30[] = {45};
constexpr uint16_t kMet_volt_31[] = {24};
constexpr uint16_t kMet_volt_32[] = {67};
constexpr uint16_t kMet_volt_33[] = {25};
constexpr uint16_t kMet_volt_34[] = {26};
constexpr uint16_t kMet_volt_35[] = {61};
constexpr uint16_t kMet_volt_36[] = {42};
constexpr uint16_t kMet_volt_37[] = {71};
constexpr uint16_t kMet_volt_38[] = {27};
constexpr uint16_t kMet_volt_39[] = {70};
constexpr uint16_t kMet_volt_40[] = {51};
constexpr uint16_t kMet_volt_41[] = {28};
constexpr uint16_t kMet_volt_42[] = {68};
constexpr uint16_t kMet_volt_43[] = {59};
constexpr uint16_t kStarters_volt[] = {495, 498, 501};
constexpr emulocke::TrackerStop kStops_volt[] = {
    {"starter", emulocke::TrackerStopKind::Encounter, "Starter", "", emulocke::BossKind::None, emulocke::CatchKind::Starter, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"b1", emulocke::TrackerStopKind::Boss, "Bianca", "Nuvema Town", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_1, 3, 0, 0, 0, 1, false, "", "", true},
    {"c1", emulocke::TrackerStopKind::Boss, "Cheren", "Nuvema Town", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_2, 3, 0, 0, 0, 1, false, "", "", true},
    {"route-1", emulocke::TrackerStopKind::Encounter, "Route 1", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_0, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"n1", emulocke::TrackerStopKind::Boss, "N", "Accumula Town", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_4, 3, 0, 0, 0, 1, false, "", "", false},
    {"route-2", emulocke::TrackerStopKind::Encounter, "Route 2", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_1, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"b2", emulocke::TrackerStopKind::Boss, "Bianca", "Route 2", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_6, 4, 0, 0, 0, 1, false, "", "", false},
    {"striaton-city", emulocke::TrackerStopKind::Encounter, "Striaton City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_2, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"c2", emulocke::TrackerStopKind::Boss, "Cheren", "Tranier's School", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_8, 4, 0, 0, 0, 1, false, "", "", false},
    {"gym-1", emulocke::TrackerStopKind::Boss, "Chili, Cress or Cilan", "Striaton Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_9, 18, 0, 0, 1, 1, false, "", "Rotation Battle: This battle is a Rotation battle.", false},
    {"dreamyard", emulocke::TrackerStopKind::Encounter, "Dreamyard", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_3, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-3", emulocke::TrackerStopKind::Encounter, "Route 3", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_4, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"c3", emulocke::TrackerStopKind::Boss, "Cheren", "Preschool", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_12, 8, 0, 0, 0, 1, false, "", "", false},
    {"wellspring-cave", emulocke::TrackerStopKind::Encounter, "Wellspring Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_5, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"nacrene-city", emulocke::TrackerStopKind::Encounter, "Nacrene City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_6, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"n2", emulocke::TrackerStopKind::Boss, "N", "Nacrene City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_15, 5, 0, 0, 0, 2, false, "", "", false},
    {"gym-2", emulocke::TrackerStopKind::Boss, "Lenora", "Nacrene Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_16, 6, 0, 0, 2, 2, false, "", "", false},
    {"pinwheel-forest", emulocke::TrackerStopKind::Encounter, "Pinwheel Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_7, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"liberty-garden", emulocke::TrackerStopKind::Encounter, "Liberty Garden", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_8, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-3", emulocke::TrackerStopKind::Boss, "Burgh", "Castelia Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_19, 6, 0, 0, 3, 2, false, "", "", false},
    {"b3", emulocke::TrackerStopKind::Boss, "Bianca", "Castelia City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_20, 8, 0, 0, 0, 2, false, "", "", false},
    {"route-4", emulocke::TrackerStopKind::Encounter, "Route 4", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_9, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"c4", emulocke::TrackerStopKind::Boss, "Cheren", "Route 4", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_22, 9, 0, 0, 0, 1, false, "", "Rotation Battle: This battle is a Rotation battle.", false},
    {"desert-resort", emulocke::TrackerStopKind::Encounter, "Desert Resort", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_10, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"relic-castle", emulocke::TrackerStopKind::Encounter, "Relic Castle", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_11, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"n3", emulocke::TrackerStopKind::Boss, "N", "Nimbasa City", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_25, 6, 0, 0, 0, 2, false, "", "", false},
    {"gym-4", emulocke::TrackerStopKind::Boss, "Elesa", "Nimbasa Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_26, 6, 0, 0, 4, 1, false, "", "", false},
    {"route-16", emulocke::TrackerStopKind::Encounter, "Route 16", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_12, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-5", emulocke::TrackerStopKind::Encounter, "Route 5", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_13, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"c5", emulocke::TrackerStopKind::Boss, "Cheren", "Route 5", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_29, 9, 0, 0, 0, 1, false, "", "", false},
    {"lostlorn-forest", emulocke::TrackerStopKind::Encounter, "Lostlorn Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_14, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"cold-storage", emulocke::TrackerStopKind::Encounter, "Cold Storage", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"driftveil-drawbidge", emulocke::TrackerStopKind::Encounter, "Driftveil Drawbidge", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"driftveil-city", emulocke::TrackerStopKind::Encounter, "Driftveil City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_15, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-5", emulocke::TrackerStopKind::Boss, "Clay", "Driftveil Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_34, 6, 0, 0, 5, 1, false, "", "", false},
    {"b4", emulocke::TrackerStopKind::Boss, "Bianca", "Driftveil City", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_35, 9, 0, 0, 0, 1, false, "", "", false},
    {"route-6", emulocke::TrackerStopKind::Encounter, "Route 6", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_16, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"chargestone-cave", emulocke::TrackerStopKind::Encounter, "Chargestone Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_17, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"n4", emulocke::TrackerStopKind::Boss, "N", "Chargestone Cave", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_38, 6, 0, 0, 0, 1, false, "", "", false},
    {"route-7", emulocke::TrackerStopKind::Encounter, "Route 7", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_18, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"celestial-tower", emulocke::TrackerStopKind::Encounter, "Celestial Tower", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_19, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-6", emulocke::TrackerStopKind::Boss, "Skyla", "Mistralton Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_41, 6, 0, 0, 6, 3, false, "", "Triple Battle: This battle is a triple battle.", false},
    {"route-17", emulocke::TrackerStopKind::Encounter, "Route 17", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_20, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-18", emulocke::TrackerStopKind::Encounter, "Route 18", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_21, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"p2-laboratory", emulocke::TrackerStopKind::Encounter, "P2 Laboratory", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_22, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"mistralton-cave", emulocke::TrackerStopKind::Encounter, "Mistralton Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_23, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"twist-mountain", emulocke::TrackerStopKind::Encounter, "Twist Mountain", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_24, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"c6", emulocke::TrackerStopKind::Boss, "Cheren", "Twist Mountain", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_47, 12, 0, 0, 0, 1, false, "", "Rotation Battle: This battle is a Rotation battle.", false},
    {"iccirus-city", emulocke::TrackerStopKind::Encounter, "Iccirus City", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"gym-7", emulocke::TrackerStopKind::Boss, "Brycen", "Iccirus Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_49, 6, 0, 0, 7, 2, false, "", "", false},
    {"route-8", emulocke::TrackerStopKind::Encounter, "Route 8", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_25, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"b5", emulocke::TrackerStopKind::Boss, "Bianca", "Route 8", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_51, 12, 0, 0, 0, 3, false, "", "Triple Battle: This battle is a triple battle.", false},
    {"moor-of-icirrus", emulocke::TrackerStopKind::Encounter, "Moor of Icirrus", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_26, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"dragonspiral-tower", emulocke::TrackerStopKind::Encounter, "Dragonspiral Tower", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_27, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-9", emulocke::TrackerStopKind::Encounter, "Route 9", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_28, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"8b", emulocke::TrackerStopKind::Boss, "Iris", "Opelucid Gym", emulocke::BossKind::Gym, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_55, 6, 0, 0, 8, 1, false, "", "Rotation Battle: This battle is a Rotation battle.", false},
    {"route-10", emulocke::TrackerStopKind::Encounter, "Route 10", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_29, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"c7", emulocke::TrackerStopKind::Boss, "Cheren", "Route 10", emulocke::BossKind::Rival, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_57, 12, 0, 0, 0, 1, false, "", "", false},
    {"victory-road", emulocke::TrackerStopKind::Encounter, "Victory Road", "", emulocke::BossKind::None, emulocke::CatchKind::Met, nullptr, 0, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"e1", emulocke::TrackerStopKind::Boss, "Shauntal", "Pokémon League W Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_59, 6, 0, 0, 0, 2, false, "", "", false},
    {"e2", emulocke::TrackerStopKind::Boss, "Grimsley", "Pokémon League NW Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_60, 6, 0, 0, 0, 2, false, "", "", false},
    {"e3", emulocke::TrackerStopKind::Boss, "Caitlin", "Pokémon League NE Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_61, 6, 0, 0, 0, 2, false, "", "", false},
    {"e4", emulocke::TrackerStopKind::Boss, "Caitlin", "Pokémon League E Room", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_62, 6, 0, 0, 0, 2, false, "", "", false},
    {"ns-castle", emulocke::TrackerStopKind::Encounter, "N's Castle", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_30, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"n5b", emulocke::TrackerStopKind::Boss, "N", "N's Castle", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_64, 6, 0, 0, 0, 1, false, "", "", false},
    {"gh", emulocke::TrackerStopKind::Boss, "Ghetsis", "N's Castle", emulocke::BossKind::EvilTeam, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_65, 6, 2400, 0, 0, 1, false, "", "", false},
    {"route-11", emulocke::TrackerStopKind::Encounter, "Route 11", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_31, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"village-bridge", emulocke::TrackerStopKind::Encounter, "Village Bridge", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_32, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-12", emulocke::TrackerStopKind::Encounter, "Route 12", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_33, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-13", emulocke::TrackerStopKind::Encounter, "Route 13", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_34, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"giant-chasm", emulocke::TrackerStopKind::Encounter, "Giant Chasm", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_35, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"undella-town", emulocke::TrackerStopKind::Encounter, "Undella Town", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_36, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"ch1", emulocke::TrackerStopKind::Boss, "Cynthia", "Undella Town", emulocke::BossKind::MiniBoss, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_72, 6, 0, 0, 0, 1, false, "", "", false},
    {"undella-bay", emulocke::TrackerStopKind::Encounter, "Undella Bay", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_37, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"route-14", emulocke::TrackerStopKind::Encounter, "Route 14", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_38, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"abundant-shrine", emulocke::TrackerStopKind::Encounter, "Abundant Shrine", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_39, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"white-forest", emulocke::TrackerStopKind::Encounter, "White Forest", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_40, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"e5", emulocke::TrackerStopKind::Boss, "Shauntal", "Pokémon League W Room (Round 2)", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_77, 6, 0, 0, 0, 1, false, "", "", false},
    {"e6", emulocke::TrackerStopKind::Boss, "Grimsley", "Pokémon League NW Room (Round 2)", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_78, 6, 0, 0, 0, 1, false, "", "", false},
    {"e7", emulocke::TrackerStopKind::Boss, "Caitlin", "Pokémon League NE Room (Round 2)", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_79, 6, 0, 0, 0, 1, false, "", "", false},
    {"e8", emulocke::TrackerStopKind::Boss, "Marshal", "Pokémon League E Room (Round 2)", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_80, 6, 0, 0, 0, 1, false, "", "", false},
    {"ch2", emulocke::TrackerStopKind::Boss, "Alder", "Pokémon League Champion", emulocke::BossKind::EliteFour, emulocke::CatchKind::None, nullptr, 0, kTeam_volt_81, 6, 0, 0, 0, 1, false, "", "", false},
    {"route-15", emulocke::TrackerStopKind::Encounter, "Route 15", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_41, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"marvelous-bridge", emulocke::TrackerStopKind::Encounter, "Marvelous Bridge", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_42, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false},
    {"challengers-cave", emulocke::TrackerStopKind::Encounter, "Challenger's Cave", "", emulocke::BossKind::None, emulocke::CatchKind::Met, kMet_volt_43, 1, nullptr, 0, 0, 0, 0, 1, false, "", "", false}
};

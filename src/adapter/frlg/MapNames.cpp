#include "adapter/frlg/FrlgNames.hpp"

#include <cstdio>

namespace emulocke {
namespace {

constexpr const char* kTownsAndRoutes[] = {
    "PALLET TOWN",
    "VIRIDIAN CITY",
    "PEWTER CITY",
    "CERULEAN CITY",
    "LAVENDER TOWN",
    "VERMILION CITY",
    "CELADON CITY",
    "FUCHSIA CITY",
    "CINNABAR ISLAND",
    "INDIGO PLATEAU",
    "SAFFRON CITY",
    "SAFFRON CONNECTION",
    "ONE ISLAND",
    "TWO ISLAND",
    "THREE ISLAND",
    "FOUR ISLAND",
    "FIVE ISLAND",
    "SEVEN ISLAND",
    "SIX ISLAND",
    "ROUTE 1",
    "ROUTE 2",
    "ROUTE 3",
    "ROUTE 4",
    "ROUTE 5",
    "ROUTE 6",
    "ROUTE 7",
    "ROUTE 8",
    "ROUTE 9",
    "ROUTE 10",
    "ROUTE 11",
    "ROUTE 12",
    "ROUTE 13",
    "ROUTE 14",
    "ROUTE 15",
    "ROUTE 16",
    "ROUTE 17",
    "ROUTE 18",
    "ROUTE 19",
    "ROUTE 20",
    "ROUTE 21 NORTH",
    "ROUTE 21 SOUTH",
    "ROUTE 22",
    "ROUTE 23",
    "ROUTE 24",
    "ROUTE 25",
};

constexpr const char* kIndoorPallet[] = {
    "PLAYER HOUSE 1F",
    "PLAYER HOUSE 2F",
    "RIVAL HOUSE",
    "OAK'S LAB",
};

constexpr const char* kDungeons[] = {
    "VIRIDIAN FOREST",
    "MT MOON 1F",
    "MT MOON B1F",
    "MT MOON B2F",
};

}  // namespace

const char* frlgMapName(uint8_t group, uint8_t num, char* scratch, std::size_t scratchSize) {
    if (group == 3 && num < sizeof(kTownsAndRoutes) / sizeof(kTownsAndRoutes[0])) {
        return kTownsAndRoutes[num];
    }
    if (group == 4 && num < sizeof(kIndoorPallet) / sizeof(kIndoorPallet[0])) {
        return kIndoorPallet[num];
    }
    if (group == 1 && num < sizeof(kDungeons) / sizeof(kDungeons[0])) {
        return kDungeons[num];
    }
    if (scratch && scratchSize > 0) {
        std::snprintf(scratch, scratchSize, "MAP %u.%u", group, num);
        return scratch;
    }
    return "MAP";
}

}
#pragma once

#include "adapter/Cartridge.hpp"
#include "adapter/LiveMemory.hpp"
#include "adapter/Snapshot.hpp"
#include "adapter/Species.hpp"

#include <span>

namespace emulocke {

class GameAdapter {
public:
    virtual ~GameAdapter() = default;
    virtual AdapterId id() const = 0;
    virtual bool matches(const Cartridge& cart) const = 0;
    virtual GameSnapshot readSave(std::span<const uint8_t> sav) const = 0;
    virtual GameSnapshot readLive(const LiveMemory& mem) const = 0;
    virtual SpeciesRef species(uint16_t internalId) const = 0;
};

const GameAdapter* adapterFor(const Cartridge& cart);
const GameAdapter* adapterForSave(std::span<const uint8_t> sav);

}
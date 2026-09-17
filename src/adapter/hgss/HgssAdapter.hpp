#pragma once

#include "adapter/GameAdapter.hpp"

namespace emulocke {

class HgssAdapter final : public GameAdapter {
public:
    explicit HgssAdapter(bool soulSilver);
    AdapterId id() const override;
    bool matches(const Cartridge& cart) const override;
    GameSnapshot readSave(std::span<const uint8_t> sav) const override;
    GameSnapshot readLive(const LiveMemory& mem) const override;
    SpeciesRef species(uint16_t internalId) const override;

private:
    bool soulSilver_;
};

}

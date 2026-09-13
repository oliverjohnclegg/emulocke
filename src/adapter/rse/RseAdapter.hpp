#pragma once

#include "adapter/GameAdapter.hpp"

namespace emulocke {

enum class RseEdition { Ruby, Sapphire, Emerald };

class RseAdapter final : public GameAdapter {
public:
    RseAdapter(RseEdition edition, uint8_t revision);
    AdapterId id() const override;
    bool matches(const Cartridge& cart) const override;
    GameSnapshot readSave(std::span<const uint8_t> sav) const override;
    GameSnapshot readLive(const LiveMemory& mem) const override;

private:
    RseEdition edition_;
    uint8_t revision_;
};

}

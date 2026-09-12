#pragma once

#include "adapter/GameAdapter.hpp"

namespace emulocke {

enum class FrlgEdition { FireRed, LeafGreen };

class FrlgAdapter final : public GameAdapter {
public:
    explicit FrlgAdapter(FrlgEdition edition, uint8_t revision);
    AdapterId id() const override;
    bool matches(const Cartridge& cart) const override;
    GameSnapshot readSave(std::span<const uint8_t> sav) const override;
    GameSnapshot readLive(const LiveMemory& mem) const override;

private:
    FrlgEdition edition_;
    uint8_t revision_;
};

}

#pragma once

#include "adapter/GameAdapter.hpp"
#include "adapter/gen4/Layout.hpp"

namespace emulocke {

enum class DpptEdition { Diamond, Pearl, Platinum };

class DpptAdapter final : public GameAdapter {
public:
    DpptAdapter(DpptEdition edition, uint8_t revision);
    AdapterId id() const override;
    bool matches(const Cartridge& cart) const override;
    GameSnapshot readSave(std::span<const uint8_t> sav) const override;
    GameSnapshot readLive(const LiveMemory& mem) const override;

private:
    DpptEdition edition_;
    uint8_t revision_;
};

}

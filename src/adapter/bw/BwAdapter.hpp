#pragma once

#include "adapter/GameAdapter.hpp"

namespace emulocke {

class BwAdapter final : public GameAdapter {
public:
    explicit BwAdapter(bool white);
    AdapterId id() const override;
    bool matches(const Cartridge& cart) const override;
    GameSnapshot readSave(std::span<const uint8_t> sav) const override;
    GameSnapshot readLive(const LiveMemory& mem) const override;

private:
    bool white_;
};

class Bw2Adapter final : public GameAdapter {
public:
    explicit Bw2Adapter(bool white);
    AdapterId id() const override;
    bool matches(const Cartridge& cart) const override;
    GameSnapshot readSave(std::span<const uint8_t> sav) const override;
    GameSnapshot readLive(const LiveMemory& mem) const override;

private:
    bool white_;
};

}

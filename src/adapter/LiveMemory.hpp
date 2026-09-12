#pragma once

#include <cstdint>
#include <cstring>
#include <span>

namespace emulocke {

class LiveMemory {
public:
    virtual ~LiveMemory() = default;
    virtual bool read(uint32_t addr, std::span<uint8_t> out) const = 0;

    uint32_t read32(uint32_t addr) const {
        uint8_t b[4]{};
        if (!read(addr, b)) {
            return 0;
        }
        return static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) |
               (static_cast<uint32_t>(b[2]) << 16) | (static_cast<uint32_t>(b[3]) << 24);
    }

    uint8_t read8(uint32_t addr) const {
        uint8_t b{};
        if (!read(addr, {&b, 1})) {
            return 0;
        }
        return b;
    }
};

class SpanMemory final : public LiveMemory {
public:
    SpanMemory(uint32_t base, std::span<uint8_t> mem) : base_(base), mem_(mem) {}

    bool read(uint32_t addr, std::span<uint8_t> out) const override {
        if (addr < base_ || out.size() > mem_.size()) {
            return false;
        }
        const uint32_t off = addr - base_;
        if (off + out.size() > mem_.size()) {
            return false;
        }
        std::memcpy(out.data(), mem_.data() + off, out.size());
        return true;
    }

private:
    uint32_t base_{};
    std::span<uint8_t> mem_{};
};

}
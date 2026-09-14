#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>
#include <span>

namespace emulocke {

class BpsReader {
public:
    explicit BpsReader(std::span<const uint8_t> bytes, std::size_t begin, std::size_t end)
        : bytes_(bytes), pos_(begin), end_(end) {}

    std::size_t pos() const { return pos_; }
    std::size_t remaining() const { return pos_ <= end_ ? end_ - pos_ : 0; }
    bool done() const { return pos_ >= end_; }

    bool skip(std::uint64_t count) {
        if (count > remaining()) {
            return false;
        }
        pos_ += static_cast<std::size_t>(count);
        return true;
    }

    const uint8_t* take(std::size_t count) {
        if (count > remaining()) {
            return nullptr;
        }
        const uint8_t* at = bytes_.data() + pos_;
        pos_ += count;
        return at;
    }

    bool readVli(std::uint64_t& value) {
        static constexpr std::uint64_t kMax = std::numeric_limits<std::uint64_t>::max();
        static constexpr int kMaxBytes = 10;
        value = 0;
        std::uint64_t shift = 1;
        for (int n = 0; n < kMaxBytes && pos_ < end_; ++n) {
            const uint8_t x = bytes_[pos_++];
            const std::uint64_t digit = x & 0x7f;
            if (digit > (kMax - value) / shift) {
                return false;
            }
            value += digit * shift;
            if (x & 0x80) {
                return true;
            }
            if (shift > (kMax >> 7)) {
                return false;
            }
            shift <<= 7;
            if (shift > kMax - value) {
                return false;
            }
            value += shift;
        }
        return false;
    }

private:
    std::span<const uint8_t> bytes_;
    std::size_t pos_;
    std::size_t end_;
};

}

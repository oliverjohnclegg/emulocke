#pragma once

#include "adapter/LiveMemory.hpp"
#include "emu/EmuSession.hpp"

#include <memory>
#include <mutex>
#include <optional>
#include <span>
#include <string>
#include <vector>

namespace melonDS {
class NDS;
}

namespace emulocke {

class NdsSession final : public EmuSession, public LiveMemory {
public:
    static std::unique_ptr<NdsSession> open(const std::string& romPath, const std::string& savePath);
    ~NdsSession() override;
    NdsSession(const NdsSession&) = delete;
    NdsSession& operator=(const NdsSession&) = delete;
    ConsoleKind kind() const override { return ConsoleKind::Nds; }
    int screenCount() const override { return 2; }
    int screenWidth(int) const override { return 256; }
    int screenHeight(int) const override { return 192; }
    void copyScreen(int index, void* dest, int pitchBytes) const override;
    void runFrame() override;
    void reset() override;
    void setButtons(uint32_t pressed) override;
    void setTouch(bool down, uint16_t x, uint16_t y) override;
    void drainAudio(AudioOutput& audio) override;
    const std::string& romName() const override { return romName_; }
    const LiveMemory* liveMemory() const override { return this; }
    std::optional<Cartridge> cartridge() const override { return cart_; }
    bool read(uint32_t addr, std::span<uint8_t> out) const override;
    bool cheatsOk(std::string_view code) override;
    void installCheats(std::span<const CheatSpec> cheats) override;
    void writeSave(const uint8_t* data, uint32_t length);

private:
    NdsSession() = default;
    std::unique_ptr<melonDS::NDS> nds_;
    std::string romPath_;
    std::string savePath_;
    std::string romName_;
    Cartridge cart_{};
    std::vector<uint32_t> top_;
    std::vector<uint32_t> bottom_;
    std::vector<int16_t> audioScratch_;
    mutable std::mutex frameMutex_;
};

}

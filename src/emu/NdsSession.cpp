#include "emu/NdsSession.hpp"

#include "emu/AudioOutput.hpp"
#include "emu/Buttons.hpp"
#include "emu/FileBytes.hpp"
#include <NDS.h>
#include <NDSCart.h>
#include <Args.h>
#include <GPU.h>
#include <SPU.h>
#include <cstring>
#include <filesystem>

namespace emulocke {

std::unique_ptr<NdsSession> NdsSession::open(const std::string& romPath, const std::string& savePath) {
    auto bytes = readWholeFile(romPath);
    if (bytes.empty()) {
        return nullptr;
    }
    auto session = std::unique_ptr<NdsSession>(new NdsSession());
    session->romPath_ = romPath;
    session->savePath_ = savePath;
    session->romName_ = std::filesystem::path(romPath).filename().string();
    session->top_.assign(256 * 192, 0);
    session->bottom_.assign(256 * 192, 0);
    melonDS::NDSCart::NDSCartArgs cartArgs;
    auto save = readWholeFile(session->savePath_);
    if (!save.empty()) {
        cartArgs.SRAM = std::make_unique<melonDS::u8[]>(save.size());
        std::memcpy(cartArgs.SRAM.get(), save.data(), save.size());
        cartArgs.SRAMLength = static_cast<melonDS::u32>(save.size());
    }
    auto cart = melonDS::NDSCart::ParseROM(
        bytes.data(), static_cast<melonDS::u32>(bytes.size()), session.get(), std::move(cartArgs));
    if (!cart) {
        return nullptr;
    }
    melonDS::NDSArgs args;
    if (args.JIT) {
        args.JIT->FastMemory = false;
    }
    session->nds_ = std::make_unique<melonDS::NDS>(std::move(args), session.get());
    session->nds_->SetNDSCart(std::move(cart));
    session->nds_->Reset();
    if (session->nds_->NeedsDirectBoot()) {
        session->nds_->SetupDirectBoot(session->romName_);
    }
    session->nds_->Start();
    return session;
}

NdsSession::~NdsSession() = default;

void NdsSession::copyScreen(int index, void* dest, int pitchBytes) const {
    std::lock_guard lock(frameMutex_);
    const auto& src = index == 0 ? top_ : bottom_;
    auto* dst = static_cast<uint8_t*>(dest);
    for (int y = 0; y < 192; ++y) {
        std::memcpy(dst + y * pitchBytes, src.data() + y * 256, 256 * 4);
    }
}

void NdsSession::runFrame() {
    nds_->RunFrame();
    void* top = nullptr;
    void* bottom = nullptr;
    nds_->GPU.GetFramebuffers(&top, &bottom);
    std::lock_guard lock(frameMutex_);
    if (top) {
        std::memcpy(top_.data(), top, 256 * 192 * 4);
    }
    if (bottom) {
        std::memcpy(bottom_.data(), bottom, 256 * 192 * 4);
    }
}

void NdsSession::reset() {
    nds_->Reset();
    if (nds_->NeedsDirectBoot()) {
        nds_->SetupDirectBoot(romName_);
    }
    nds_->Start();
}

void NdsSession::setButtons(uint32_t pressed) {
    nds_->SetKeyMask(kReleasedMask & ~pressed);
}

void NdsSession::setTouch(bool down, uint16_t x, uint16_t y) {
    if (down) {
        nds_->TouchScreen(x, y);
    } else {
        nds_->ReleaseScreen();
    }
}

void NdsSession::drainAudio(AudioOutput& audio) {
    const int available = nds_->SPU.GetOutputSize();
    if (available <= 0) {
        return;
    }
    std::vector<int16_t> samples(static_cast<size_t>(available) * 2);
    const int got = nds_->SPU.ReadOutput(samples.data(), available);
    audio.push(samples.data(), got, 48000);
}

void NdsSession::writeSave(const uint8_t* data, uint32_t length) {
    writeWholeFile(savePath_, data, length);
}

}
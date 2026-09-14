#include "emu/GbaSession.hpp"

#include "emu/AudioOutput.hpp"
#include "emu/FileBytes.hpp"
#include "emu/GbaPixels.hpp"

#include <mgba/core/core.h>
#include <mgba/core/interface.h>
#include <mgba-util/audio-buffer.h>
#include <mgba-util/vfs.h>
#include <cstdlib>
#include <cstring>
#include <filesystem>

namespace emulocke {

std::unique_ptr<GbaSession> GbaSession::open(const std::string& romPath, const std::string& savePath) {
    auto bytes = readWholeFile(romPath);
    if (bytes.empty()) {
        return nullptr;
    }
    VFile* vf = VFileMemChunk(bytes.data(), bytes.size());
    if (!vf) {
        return nullptr;
    }
    auto session = std::unique_ptr<GbaSession>(new GbaSession());
    session->core_ = mCoreFindVF(vf);
    if (!session->core_ || !session->core_->init(session->core_)) {
        vf->close(vf);
        return nullptr;
    }
    mCoreInitConfig(session->core_, "emulocke");
    mCoreConfigSetDefaultValue(&session->core_->config, "skipBios", "1");
    mCoreConfigSetDefaultValue(&session->core_->config, "idleOptimization", "detect");
    mCoreConfigSetDefaultIntValue(&session->core_->config, "frameskip", 0);
    session->core_->opts.skipBios = true;
    session->core_->opts.frameskip = 0;
    session->core_->baseVideoSize(session->core_, &session->width_, &session->height_);
    session->pixels_.assign(session->width_ * session->height_, 0);
    session->display_.assign(session->width_ * session->height_, 0);
    session->core_->setVideoBuffer(session->core_, session->pixels_.data(), session->width_);
    session->core_->setAudioBufferSize(session->core_, 4096);
    if (!session->core_->loadROM(session->core_, vf)) {
        vf->close(vf);
        return nullptr;
    }
    session->savePath_ = savePath;
    session->core_->loadConfig(session->core_, &session->core_->config);
    session->core_->opts.skipBios = true;
    session->core_->opts.frameskip = 0;
    session->core_->reset(session->core_);
    auto save = readWholeFile(session->savePath_);
    if (!save.empty()) {
        session->core_->savedataRestore(session->core_, save.data(), save.size(), true);
    }
    mCoreCallbacks callbacks{};
    callbacks.context = session.get();
    callbacks.savedataUpdated = [](void* ctx) { static_cast<GbaSession*>(ctx)->flushSave(); };
    session->core_->addCoreCallbacks(session->core_, &callbacks);
    session->romName_ = std::filesystem::path(romPath).filename().string();
    session->cart_ = cartridgeFromRom(bytes);
    return session;
}

GbaSession::~GbaSession() {
    if (core_) {
        if (!savePath_.empty()) {
            flushSave();
        }
        mCoreConfigDeinit(&core_->config);
        core_->deinit(core_);
    }
}

void GbaSession::copyScreen(int index, void* dest, int pitchBytes) const {
    if (index != 0 || !dest) {
        return;
    }
    std::lock_guard lock(frameMutex_);
    auto* dst = static_cast<uint8_t*>(dest);
    const size_t rowBytes = static_cast<size_t>(width_) * 4;
    for (unsigned y = 0; y < height_; ++y) {
        std::memcpy(dst + static_cast<size_t>(y) * pitchBytes, display_.data() + static_cast<size_t>(y) * width_,
                    rowBytes);
    }
}

void GbaSession::runFrame() {
    core_->runFrame(core_);
    std::lock_guard lock(frameMutex_);
    const size_t n = static_cast<size_t>(width_) * height_;
    for (size_t i = 0; i < n; ++i) {
        display_[i] = gbaNativeToRgba(pixels_[i]);
    }
}

void GbaSession::reset() {
    core_->reset(core_);
}

void GbaSession::setButtons(uint32_t pressed) {
    core_->setKeys(core_, pressed & 0x3FF);
}

void GbaSession::drainAudio(AudioOutput& audio) {
    mAudioBuffer* buffer = core_->getAudioBuffer(core_);
    if (!buffer) {
        return;
    }
    const int available = static_cast<int>(mAudioBufferAvailable(buffer));
    if (available <= 0) {
        return;
    }
    audioScratch_.resize(static_cast<size_t>(available) * 2);
    const int got = static_cast<int>(mAudioBufferRead(buffer, audioScratch_.data(), static_cast<size_t>(available)));
    const int hz = static_cast<int>(core_->audioSampleRate(core_));
    audio.push(audioScratch_.data(), got, hz > 0 ? hz : 32768);
}

bool GbaSession::read(uint32_t addr, std::span<uint8_t> out) const {
    std::lock_guard lock(frameMutex_);
    if (!core_ || out.empty()) {
        return false;
    }
    size_t size = 0;
    void* block = mCoreGetMemoryBlock(core_, addr, &size);
    if (block && size >= out.size()) {
        std::memcpy(out.data(), block, out.size());
        return true;
    }
    for (std::size_t i = 0; i < out.size(); ++i) {
        out[i] = static_cast<uint8_t>(core_->busRead8(core_, addr + static_cast<uint32_t>(i)));
    }
    return true;
}

bool GbaSession::write(uint32_t addr, std::span<const uint8_t> in) {
    std::lock_guard lock(frameMutex_);
    if (!core_ || in.empty()) {
        return false;
    }
    size_t size = 0;
    void* block = mCoreGetMemoryBlock(core_, addr, &size);
    if (block && size >= in.size()) {
        std::memcpy(block, in.data(), in.size());
        return true;
    }
    for (std::size_t i = 0; i < in.size(); ++i) {
        core_->busWrite8(core_, addr + static_cast<uint32_t>(i), in[i]);
    }
    return true;
}

void GbaSession::flushSave() {
    if (!core_) {
        return;
    }
    void* sram = nullptr;
    const size_t n = core_->savedataClone(core_, &sram);
    if (n && sram) {
        writeWholeFile(savePath_, static_cast<const uint8_t*>(sram), static_cast<uint32_t>(n));
        std::free(sram);
    }
}

}
#include "emu/GbaSession.hpp"

#include "emu/AudioOutput.hpp"
#include "emu/FileBytes.hpp"
#include "emu/Paths.hpp"

#include <mgba/core/core.h>
#include <mgba/core/interface.h>
#include <mgba-util/audio-buffer.h>
#include <mgba-util/vfs.h>
#include <cstring>
#include <cstdlib>
#include <filesystem>
#include <vector>

namespace emulocke {

std::unique_ptr<GbaSession> GbaSession::open(const std::string& romPath) {
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
    session->core_->baseVideoSize(session->core_, &session->width_, &session->height_);
    session->pixels_.assign(session->width_ * session->height_, 0);
    session->core_->setVideoBuffer(session->core_, session->pixels_.data(), session->width_);
    session->core_->setAudioBufferSize(session->core_, 4096);
    if (!session->core_->loadROM(session->core_, vf)) {
        session->core_->deinit(session->core_);
        session->core_ = nullptr;
        return nullptr;
    }
    session->savePath_ = savePathBesideRom(romPath);
    auto save = readWholeFile(session->savePath_);
    if (!save.empty()) {
        session->core_->savedataRestore(session->core_, save.data(), save.size(), true);
    }
    session->core_->reset(session->core_);
    mCoreCallbacks callbacks{};
    callbacks.context = session.get();
    callbacks.savedataUpdated = [](void* ctx) { static_cast<GbaSession*>(ctx)->flushSave(); };
    session->core_->addCoreCallbacks(session->core_, &callbacks);
    session->romName_ = std::filesystem::path(romPath).filename().string();
    return session;
}

GbaSession::~GbaSession() {
    if (core_) {
        flushSave();
        core_->deinit(core_);
    }
}

void GbaSession::copyScreen(int index, void* dest, int pitchBytes) const {
    if (index != 0 || !dest) {
        return;
    }
    std::lock_guard lock(frameMutex_);
    const auto* src = reinterpret_cast<const uint8_t*>(pixels_.data());
    auto* dst = static_cast<uint8_t*>(dest);
    const int row = static_cast<int>(width_ * 4);
    for (unsigned y = 0; y < height_; ++y) {
        std::memcpy(dst + y * pitchBytes, src + y * row, row);
    }
}

void GbaSession::runFrame() {
    std::lock_guard lock(frameMutex_);
    core_->runFrame(core_);
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
    std::vector<int16_t> samples(static_cast<size_t>(available) * 2);
    const int got = static_cast<int>(mAudioBufferRead(buffer, samples.data(), static_cast<size_t>(available)));
    const int hz = static_cast<int>(core_->audioSampleRate(core_));
    audio.push(samples.data(), got, hz > 0 ? hz : 32768);
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
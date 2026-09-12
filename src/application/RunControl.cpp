#include "application/Application.hpp"

#include "emu/Paths.hpp"
#include "run/Roms.hpp"

namespace emulocke {

void Application::scanRoms() {
    detectedGames_ = scanRomsDirs(romsScanDirs());
}

void Application::requestNewRun() {
    scanRoms();
    newRunDraft_.rules = regularRules();
    if (newRunDraft_.gameIndex >= static_cast<int>(detectedGames_.size())) {
        newRunDraft_.gameIndex = 0;
    }
    showNewRun_ = true;
}

void Application::dismissNewRun() {
    showNewRun_ = false;
}

void Application::confirmNewRun() {
    showNewRun_ = false;
    pendingCreate_ = true;
}

void Application::requestLoadRun() {
    if (!runStore_->runs().empty()) {
        showLoadRun_ = true;
    }
}

void Application::dismissLoadRun() {
    showLoadRun_ = false;
}

void Application::queueLoadRun(std::string id) {
    showLoadRun_ = false;
    pendingLoadId_ = std::move(id);
}

void Application::queueNewAttempt(std::string sourceId) {
    showLoadRun_ = false;
    pendingAttemptId_ = std::move(sourceId);
}

void Application::drainPending() {
    if (pendingCreate_) {
        pendingCreate_ = false;
        createRunFromDraft();
    }
    if (!pendingAttemptId_.empty()) {
        const std::string id = std::move(pendingAttemptId_);
        pendingAttemptId_.clear();
        startNewAttempt(id);
    }
    if (!pendingLoadId_.empty()) {
        const std::string id = std::move(pendingLoadId_);
        pendingLoadId_.clear();
        loadRun(id);
    }
}

void Application::createRunFromDraft() {
    if (newRunDraft_.gameIndex < 0 ||
        newRunDraft_.gameIndex >= static_cast<int>(detectedGames_.size())) {
        status_ = "No Pokemon ROM in the roms folder.";
        return;
    }
    const DetectedGame& game = detectedGames_[static_cast<size_t>(newRunDraft_.gameIndex)];
    auto created = runStore_->create(game.gameId, game.romPath, newRunDraft_.rules);
    if (!created) {
        status_ = "Failed to create run.";
        return;
    }
    loadRun(created->id);
}

void Application::startNewAttempt(const std::string& sourceId) {
    const Run* source = runStore_->find(sourceId);
    if (!source) {
        status_ = "Run not found.";
        return;
    }
    const Run snapshot = *source;
    if (activeRunId_ == sourceId) {
        closeRun();
    }
    auto created = runStore_->createAttempt(snapshot);
    if (!created) {
        status_ = "Failed to start a new attempt.";
        return;
    }
    loadRun(created->id);
}

void Application::loadRun(const std::string& id) {
    Run* run = runStore_->find(id);
    if (!run) {
        status_ = "Run not found.";
        return;
    }
    scanRoms();
    auto rom = resolveRomPath(*run, detectedGames_);
    if (!rom) {
        status_ = "ROM missing from the roms folder.";
        return;
    }
    if (*rom != run->romPath) {
        runStore_->updateRomPath(id, *rom);
        run = runStore_->find(id);
    }
    if (!run) {
        return;
    }
    bootRun(*run);
    if (session_) {
        activeRunId_ = id;
        runStore_->touch(id);
    } else {
        activeRunId_.clear();
    }
}

}
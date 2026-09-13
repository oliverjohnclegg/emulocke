#include "application/Application.hpp"

#include "run/Catalog.hpp"

#include <string>

namespace emulocke {

void Application::requestNewRun() {
    if (newRunDraft_.catalogUuid.empty()) {
        for (const CatalogTitle& title : catalogTitles()) {
            if (romLibrary_->ready(title)) {
                newRunDraft_.catalogUuid = title.uuid;
                break;
            }
        }
        if (newRunDraft_.catalogUuid.empty() && !catalogTitles().empty()) {
            newRunDraft_.catalogUuid = catalogTitles().front().uuid;
        }
    }
    if (const CatalogTitle* title = catalogByUuid(newRunDraft_.catalogUuid)) {
        newRunDraft_.patchOption = std::string(catalogOptionId(*title, newRunDraft_.patchOption));
    }
    newRunDraft_.rules = regularRules();
    pendingNewRun_ = true;
}

void Application::dismissNewRun() {
    pendingNewRun_ = false;
    showNewRun_ = false;
}

void Application::confirmNewRun() {
    pendingNewRun_ = false;
    showNewRun_ = false;
    pendingCreate_ = true;
}

void Application::queueLoadRun(std::string id) {
    pendingLoadId_ = std::move(id);
}

void Application::queueNewAttempt(std::string sourceId) {
    pendingAttemptId_ = std::move(sourceId);
}

void Application::importPath(const std::string& path) {
    const ImportResult result = romLibrary_->importFile(path);
    status_ = result.message;
    if (result.ok && result.title) {
        const CatalogTitle* keep = catalogByUuid(importKeepUuid_);
        if (keep && keep->kind == TitleKind::Hack &&
            std::string(keep->prerequisiteUuid) == result.title->uuid) {
            newRunDraft_.catalogUuid = importKeepUuid_;
        } else if (keep && keep->kind == TitleKind::Hack) {
            newRunDraft_.catalogUuid = importKeepUuid_;
        } else {
            newRunDraft_.catalogUuid = result.title->uuid;
        }
    }
    importKeepUuid_.clear();
}

void Application::drainPending() {
    if (pendingNewRun_) {
        pendingNewRun_ = false;
        showNewRun_ = true;
    }
    if (pendingDumpPicker_) {
        pendingDumpPicker_ = false;
        showDumpPicker();
    }
    if (pendingSavPicker_) {
        pendingSavPicker_ = false;
        showSavPicker();
    }
    if (!pendingImport_.empty()) {
        const std::string path = std::move(pendingImport_);
        pendingImport_.clear();
        importPath(path);
    }
    const bool boot = pendingCreate_ || !pendingAttemptId_.empty() || !pendingLoadId_.empty();
    if (boot) {
        if (!showLoadingRun_) {
            showLoadingRun_ = true;
            loadingPainted_ = false;
            return;
        }
        if (!loadingPainted_) {
            return;
        }
    }
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
    if (boot) {
        showLoadingRun_ = false;
        loadingPainted_ = false;
    }
}

void Application::createRunFromDraft() {
    const std::string sav = std::move(pendingImportSav_);
    pendingImportSav_.clear();
    if (newRunDraft_.catalogUuid.empty()) {
        status_ = "Pick a game.";
        return;
    }
    auto rom = romLibrary_->ensurePlayable(newRunDraft_.catalogUuid, newRunDraft_.patchOption);
    if (!rom) {
        status_ = romLibrary_->lastError();
        return;
    }
    auto created = runStore_->create(newRunDraft_.catalogUuid, newRunDraft_.rules, newRunDraft_.patchOption);
    if (!created) {
        status_ = "Failed to create run.";
        return;
    }
    if (!sav.empty() && !runStore_->importBattery(created->id, sav)) {
        status_ = "Failed to import save.";
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
    const Run* run = runStore_->find(id);
    if (!run) {
        status_ = "Run not found.";
        return;
    }
    persistTracker();
    bootRun(*run);
    if (session_) {
        activeRunId_ = id;
        runStore_->touch(id);
        loadTrackerLog();
    } else {
        activeRunId_.clear();
        trackerLog_ = {};
    }
    syncWindowTitle();
}

}
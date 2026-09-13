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
    if (!pendingImport_.empty()) {
        const std::string path = std::move(pendingImport_);
        pendingImport_.clear();
        importPath(path);
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
}

void Application::createRunFromDraft() {
    if (newRunDraft_.catalogUuid.empty()) {
        status_ = "Pick a game.";
        return;
    }
    auto rom = romLibrary_->ensurePlayable(newRunDraft_.catalogUuid);
    if (!rom) {
        status_ = romLibrary_->lastError();
        return;
    }
    auto created = runStore_->create(newRunDraft_.catalogUuid, newRunDraft_.rules);
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
    const Run* run = runStore_->find(id);
    if (!run) {
        status_ = "Run not found.";
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
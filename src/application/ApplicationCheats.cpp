#include "application/Application.hpp"

#include "cheats/Uuid.hpp"

#include <mutex>

namespace emulocke {

void Application::persistCheats() {
    if (activeRunId_.empty() || !runStore_) {
        return;
    }
    cheats_.saveEnabled(runStore_->dir(activeRunId_) / "cheats.ini");
}

void Application::persistGameCheats() {
    if (activeRunId_.empty() || !runStore_) {
        return;
    }
    const Run* run = runStore_->find(activeRunId_);
    if (!run) {
        return;
    }
    const auto path = cheatGamePath(run->catalogUuid);
    if (!path.empty()) {
        cheats_.saveGame(path);
    }
}

void Application::installLiveCheats() {
    std::lock_guard lock(sessionMutex_);
    if (session_) {
        session_->installCheats(cheats_.enabledSpecs());
    }
}

void Application::loadCheats() {
    cheats_.clear();
    cheatError_.clear();
    if (activeRunId_.empty() || !runStore_) {
        return;
    }
    const Run* run = runStore_->find(activeRunId_);
    if (!run) {
        return;
    }
    if (!run->allowCheats) {
        return;
    }
    const auto game = cheatGamePath(run->catalogUuid);
    if (game.empty()) {
        return;
    }
    cheats_.loadGame(game);
    cheats_.loadEnabled(runStore_->dir(activeRunId_) / "cheats.ini");
    installLiveCheats();
}

bool Application::addCheat(std::string_view name, std::string_view code) {
    cheatError_.clear();
    if (activeRunId_.empty() || !session_) {
        cheatError_ = "No cart seated.";
        return false;
    }
    {
        std::lock_guard lock(sessionMutex_);
        if (!session_ || !session_->cheatsOk(code)) {
            cheatError_ = "That code did not parse.";
            return false;
        }
    }
    if (!cheats_.add(name, code)) {
        cheatError_ = "Could not save that cheat.";
        return false;
    }
    persistGameCheats();
    return true;
}

void Application::removeCheat(std::string_view id) {
    if (!cheats_.remove(id)) {
        return;
    }
    persistGameCheats();
    persistCheats();
    installLiveCheats();
}

void Application::setCheatEnabled(std::string_view id, bool on) {
    if (!cheats_.setEnabled(id, on)) {
        return;
    }
    persistCheats();
    installLiveCheats();
}

}

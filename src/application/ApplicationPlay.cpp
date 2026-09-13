#include "application/Application.hpp"

#include <SDL3/SDL.h>

namespace emulocke {

void Application::harvestPlayOrigin() {
    const Uint64 origin = playOriginNs_.exchange(0);
    if (origin != 0) {
        pendingPlayNs_.fetch_add(SDL_GetTicksNS() - origin);
    }
}

void Application::commitPlay() {
    const uint64_t ns = pendingPlayNs_.exchange(0);
    const uint64_t ms = ns / 1000000ull;
    const uint64_t rem = ns % 1000000ull;
    if (rem) {
        pendingPlayNs_.fetch_add(rem);
    }
    if (ms == 0 || activeRunId_.empty() || !runStore_ || !titlePlay_) {
        return;
    }
    runStore_->addPlayMs(activeRunId_, ms);
    if (const Run* run = runStore_->find(activeRunId_)) {
        titlePlay_->add(run->catalogUuid, ms);
    }
}

}

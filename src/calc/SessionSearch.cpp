#include "calc/Session.hpp"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>

namespace emulocke {
namespace {

bool has(const char* hay, const char* needle) {
    if (!hay || !needle || !needle[0]) {
        return false;
    }
    const std::string_view h = hay;
    const std::string_view n = needle;
    auto fold = [](char c) { return static_cast<char>(std::tolower(static_cast<unsigned char>(c))); };
    auto it = std::search(h.begin(), h.end(), n.begin(), n.end(),
        [&](char a, char b) { return fold(a) == fold(b); });
    return it != h.end();
}

}  // namespace

void CalcSession::search(const char* query) {
    if (query != query_) {
        std::snprintf(query_, sizeof(query_), "%s", query ? query : "");
    }
    trainers_.clear();
    locations_.clear();
    browsing_ = query_[0] != 0;
    if (!pack_ || !browsing_) {
        return;
    }
    for (int i = 0; i < pack_->locationCount; ++i) {
        if (has(pack_->locations[i].name, query_)) {
            locations_.push_back(&pack_->locations[i]);
        }
    }
    for (int i = 0; i < pack_->trainerCount; ++i) {
        const PackTrainer& t = pack_->trainers[i];
        if (has(t.name, query_) || has(t.cls, query_) || has(t.location, query_)) {
            trainers_.push_back(&t);
        }
    }
}

void CalcSession::lockParty(int slot) {
    partySlot_ = slot;
    pinParty_ = true;
    if (!pinFoe_ && !snap_.battle.inBattle) {
        foeSlot_ = nextIn();
    }
}

void CalcSession::lockFoe(int slot) {
    foeSlot_ = slot;
    pinFoe_ = true;
}

void CalcSession::pickTrainer(const PackTrainer* trainer) {
    trainer_ = trainer;
    foeSlot_ = 0;
    pinFoe_ = false;
    browsing_ = false;
    refreshFoe();
    if (!snap_.battle.inBattle) {
        foeSlot_ = nextIn();
    }
}

void CalcSession::pickLocation(const PackLocation* loc) {
    trainer_ = nullptr;
    trainers_.clear();
    locations_.clear();
    browsing_ = true;
    if (!pack_ || !loc) {
        return;
    }
    for (uint16_t i = 0; i < loc->count; ++i) {
        const PackTrainer* t = packTrainer(*pack_, pack_->locIds[loc->idOff + i]);
        if (t) {
            trainers_.push_back(t);
        }
    }
}

}

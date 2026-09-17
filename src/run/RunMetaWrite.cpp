#include "run/RunMeta.hpp"

#include "run/NdsMac.hpp"

#include <fstream>

namespace emulocke {

bool writeRunMeta(const std::filesystem::path& dir, const Run& run) {
    std::ofstream out(dir / "meta.ini", std::ios::trunc);
    if (!out) {
        return false;
    }
    auto yn = [](bool v) { return v ? "1" : "0"; };
    out << "game=" << run.catalogUuid << "\n";
    out << "lineageId=" << run.lineageId << "\n";
    out << "attempt=" << run.attempt << "\n";
    out << "firstEncounter=" << yn(run.rules.firstEncounter) << "\n";
    out << "nicknames=" << yn(run.rules.nicknames) << "\n";
    out << "faintIsDeath=" << yn(run.rules.faintIsDeath) << "\n";
    out << "setMode=" << yn(run.rules.setMode) << "\n";
    out << "noItemsInBattle=" << yn(run.rules.noItemsInBattle) << "\n";
    out << "levelCap=" << yn(run.rules.levelCap) << "\n";
    out << "dupesClause=" << yn(run.rules.dupesClause) << "\n";
    out << "shinyClause=" << yn(run.rules.shinyClause) << "\n";
    out << "allowCheats=" << yn(run.allowCheats) << "\n";
    if (!run.patchOption.empty()) {
        out << "patchOption=" << run.patchOption << "\n";
    }
    if (ndsMacAssigned(run.mac)) {
        out << "mac=" << formatNdsMac(run.mac) << "\n";
    }
    out << "createdAt=" << run.createdAt << "\n";
    out << "lastPlayedAt=" << run.lastPlayedAt << "\n";
    out << "playMs=" << run.playMs << "\n";
    out << "difficulty=" << run.difficulty << "\n";
    return static_cast<bool>(out);
}

}
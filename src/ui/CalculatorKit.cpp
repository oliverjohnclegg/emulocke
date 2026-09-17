#include "ui/Calculator.hpp"

#include "application/Application.hpp"
#include "calc/Session.hpp"
#include "ui/KitNav.hpp"

namespace emulocke {
namespace {

int matchupRows() {
    return 10;
}

int fieldRows() {
    return 21;
}

int locCap(const CalcSession& session) {
    const int n = static_cast<int>(session.locationHits().size());
    return n > 8 ? 8 : n;
}

int trainerCap(const CalcSession& session) {
    const int n = static_cast<int>(session.trainerHits().size());
    if (n > 10) {
        return 8;
    }
    return n;
}

int hitCount(const CalcSession& session) {
    return locCap(session) + trainerCap(session);
}

int colCount(const CalcSession& session, int col) {
    if (col == 0) {
        return 6;
    }
    if (col == 1) {
        return matchupRows();
    }
    if (col == 2) {
        return session.trainer() ? session.trainer()->count : 0;
    }
    return fieldRows();
}

void enterField(KitFocus& focus) {
    focus.calcReturnCol = focus.calcCol;
    focus.calcCol = 3;
    focus.calcRow = 0;
}

void leaveField(KitFocus& focus, const CalcSession& session) {
    focus.calcCol = focus.calcReturnCol;
    if (focus.calcCol < 0 || focus.calcCol > 2) {
        focus.calcCol = 0;
    }
    focus.calcRow = colCount(session, focus.calcCol) - 1;
    if (focus.calcRow < 0) {
        focus.calcRow = 0;
    }
}

}  // namespace

void applyCalculatorKit(Application& app, CalcSession& session) {
    if (!kitNavSuite(app, KitTab::Calculator)) {
        return;
    }
    KitFocus& focus = app.kitFocus();
    const KitFrame& kit = app.kit();
    if (kit.snap) {
        focus.calcCol = 1;
        focus.calcRow = 2;
    }
    if (session.browsing()) {
        kitMove(focus.searchHit, hitCount(session), kit.up || kit.left, kit.down || kit.right);
        if (kit.act && hitCount(session) > 0) {
            const int loc = locCap(session);
            if (focus.searchHit < loc) {
                session.pickLocation(session.locationHits()[static_cast<std::size_t>(focus.searchHit)]);
            } else {
                const int t = focus.searchHit - loc;
                session.pickTrainer(session.trainerHits()[static_cast<std::size_t>(t)]);
            }
        }
        return;
    }
    if (!session.trainer()) {
        return;
    }
    if (focus.calcCol == 3) {
        if (kit.up && focus.calcRow == 0) {
            leaveField(focus, session);
        } else {
            kitMove(focus.calcRow, fieldRows(), kit.up || kit.left, kit.down || kit.right);
        }
        return;
    }
    const int rows = colCount(session, focus.calcCol);
    if (kit.down && focus.calcRow >= rows - 1) {
        enterField(focus);
        return;
    }
    if (kit.left) {
        kitMove(focus.calcCol, 3, true, false);
        kitMove(focus.calcRow, colCount(session, focus.calcCol), false, false);
    }
    if (kit.right) {
        kitMove(focus.calcCol, 3, false, true);
        kitMove(focus.calcRow, colCount(session, focus.calcCol), false, false);
    }
    kitMove(focus.calcRow, colCount(session, focus.calcCol), kit.up, kit.down);
    if (!kit.act) {
        return;
    }
    if (focus.calcCol == 0) {
        session.lockParty(focus.calcRow);
    } else if (focus.calcCol == 2 && session.trainer()) {
        int order[6];
        session.foeOrder(order);
        if (focus.calcRow >= 0 && focus.calcRow < 6 && order[focus.calcRow] >= 0) {
            session.lockFoe(order[focus.calcRow]);
        }
    }
}

}

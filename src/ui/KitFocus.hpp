#pragma once

namespace emulocke {

enum class KitTab : int { Tracker = 1, Pokemon = 2, Calculator = 3, Cheats = 4, Logs = 5 };

struct KitFocus {
    KitTab tab{KitTab::Logs};
    int pendingTab{};
    int trackerRow{};
    int pokemonWell{};
    int calcCol{};
    int calcRow{};
    int calcReturnCol{};
    int cheatsRow{};
    int homeIndex{};
    int modalIndex{1};
    int searchHit{};
    bool focusSearch{};
    bool openCheatAdd{};
};

inline void kitMove(int& i, int count, bool prev, bool next) {
    if (count <= 0) {
        i = 0;
        return;
    }
    if (prev && i > 0) {
        --i;
    }
    if (next && i < count - 1) {
        ++i;
    }
    if (i < 0) {
        i = 0;
    }
    if (i >= count) {
        i = count - 1;
    }
}

}

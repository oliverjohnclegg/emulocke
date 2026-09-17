#pragma once

namespace emulocke {

struct KitFrame {
    bool act{};
    bool left{};
    bool right{};
    bool up{};
    bool down{};
    bool snap{};
    bool search{};
    bool pause{};
    bool pane{};
    bool backspace{};
    int tab{};
};

KitFrame pollKit(const bool* keys, bool textInput, bool blocked);

}

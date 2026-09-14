#pragma once

#include <string>

namespace emulocke {

struct Cheat {
    std::string id;
    std::string name;
    std::string code;
    bool enabled = false;
};

struct CheatSpec {
    std::string name;
    std::string code;
};

}

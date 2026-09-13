#include "run/TitlePlay.hpp"

#include <cstdlib>
#include <fstream>
#include <string>

namespace emulocke {

TitlePlay::TitlePlay(std::filesystem::path file) : file_(std::move(file)) {
    std::ifstream in(file_);
    if (!in) {
        return;
    }
    std::string line;
    while (std::getline(in, line)) {
        const auto eq = line.find('=');
        if (eq == std::string::npos || eq == 0) {
            continue;
        }
        ms_[line.substr(0, eq)] = std::strtoull(line.c_str() + eq + 1, nullptr, 10);
    }
}

uint64_t TitlePlay::get(std::string_view uuid) const {
    const auto it = ms_.find(std::string(uuid));
    return it == ms_.end() ? 0 : it->second;
}

bool TitlePlay::add(std::string_view uuid, uint64_t ms) {
    if (ms == 0 || uuid.empty()) {
        return true;
    }
    ms_[std::string(uuid)] += ms;
    return save();
}

bool TitlePlay::save() const {
    std::ofstream out(file_, std::ios::trunc);
    if (!out) {
        return false;
    }
    for (const auto& [id, value] : ms_) {
        out << id << '=' << value << '\n';
    }
    return static_cast<bool>(out);
}

}

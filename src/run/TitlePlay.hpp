#pragma once

#include <cstdint>
#include <filesystem>
#include <map>
#include <string>
#include <string_view>

namespace emulocke {

class TitlePlay {
public:
    explicit TitlePlay(std::filesystem::path file);
    uint64_t get(std::string_view uuid) const;
    bool add(std::string_view uuid, uint64_t ms);

private:
    bool save() const;
    std::filesystem::path file_;
    std::map<std::string, uint64_t> ms_;
};

}

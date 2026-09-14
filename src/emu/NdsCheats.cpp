#include "emu/NdsSession.hpp"

#include "cheats/Lines.hpp"

#include <NDS.h>
#include <AREngine.h>
#include <vector>

namespace emulocke {

bool NdsSession::cheatsOk(std::string_view code) {
    std::vector<uint32_t> words;
    return parseArWords(code, words);
}

void NdsSession::installCheats(std::span<const CheatSpec> cheats) {
    std::lock_guard lock(frameMutex_);
    if (!nds_) {
        return;
    }
    nds_->AREngine.Cheats.clear();
    for (const CheatSpec& spec : cheats) {
        std::vector<uint32_t> words;
        if (!parseArWords(spec.code, words)) {
            continue;
        }
        melonDS::ARCode row{};
        row.Name = spec.name;
        row.Enabled = true;
        row.Code.assign(words.begin(), words.end());
        nds_->AREngine.Cheats.push_back(std::move(row));
    }
}

}

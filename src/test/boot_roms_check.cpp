#include "adapter/GameAdapter.hpp"
#include "emu/FileBytes.hpp"
#include "emu/GbaSession.hpp"
#include "emu/NdsSession.hpp"
#include "run/Catalog.hpp"
#include "run/PatchApply.hpp"

#include <SDL3/SDL.h>
#include <cstdio>
#include <filesystem>
#include <string>

int main(int argc, char** argv) {
    SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "dummy");
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::fprintf(stderr, "sdl: %s\n", SDL_GetError());
        return 1;
    }
    if (argc < 2) {
        std::fprintf(stderr, "usage: emulocke-boot-check ROM [SAV]\n");
        return 2;
    }
    const std::string rom = argv[1];
    const std::string sav = argc > 2 ? argv[2] : rom + ".sav";
    const auto bytes = emulocke::readWholeFile(rom);
    const auto battery = emulocke::readWholeFile(sav);
    const emulocke::CatalogTitle* title = emulocke::catalogBySha1(emulocke::sha1Hex(bytes));
    const auto tmpSav = std::filesystem::temp_directory_path() /
                        (std::filesystem::path(rom).filename().string() + ".boot.sav");
    if (!battery.empty()) {
        emulocke::writeWholeFile(tmpSav.string(), battery.data(), static_cast<uint32_t>(battery.size()));
    }
    std::unique_ptr<emulocke::EmuSession> session;
    const std::string ext = std::filesystem::path(rom).extension().string();
    if (ext == ".gba" || ext == ".GBA") {
        session = emulocke::GbaSession::open(rom, tmpSav.string());
    } else {
        session = emulocke::NdsSession::open(rom, tmpSav.string());
    }
    if (!session || !session->cartridge()) {
        std::fprintf(stderr, "FAIL open %s catalog=%s\n", rom.c_str(), title ? title->slug : "none");
        return 1;
    }
    const emulocke::Cartridge cart = *session->cartridge();
    const emulocke::GameAdapter* adapter = emulocke::adapterFor(cart);
    if (!adapter) {
        std::fprintf(stderr, "FAIL adapter %s rev %u\n", cart.code, cart.revision);
        return 1;
    }
    for (int i = 0; i < 90; ++i) {
        session->runFrame();
    }
    emulocke::GameSnapshot snap = adapter->readLive(*session->liveMemory());
    const char* origin = "live";
    if ((!snap.ok || snap.party.count == 0) && !battery.empty()) {
        snap = adapter->readSave(battery);
        origin = "save";
    }
    std::printf("%s catalog=%s cart=%s rev=%u adapter=%s origin=%s ok=%d ot=%s party=%u first=%s\n",
                std::filesystem::path(rom).filename().c_str(), title ? title->slug : "NONE", cart.code,
                cart.revision, adapter->id().data(), origin, snap.ok ? 1 : 0, snap.trainer.name,
                snap.party.count, snap.party.mons[0].speciesName);
    SDL_Quit();
    return title && adapter ? 0 : 1;
}

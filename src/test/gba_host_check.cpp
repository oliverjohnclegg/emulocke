#include "emu/GbaPixels.hpp"
#include "emu/GbaSession.hpp"
#include "emu/FileBytes.hpp"

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <vector>

namespace {

uint32_t encodeImm(uint32_t value) {
    for (int rot = 0; rot < 16; ++rot) {
        const int shift = rot * 2;
        const uint32_t imm = shift == 0 ? value : ((value << shift) | (value >> (32 - shift)));
        if ((imm & 0xFFFFFF00u) == 0) {
            return (static_cast<uint32_t>(rot) << 8) | (imm & 0xFFu);
        }
    }
    std::fprintf(stderr, "cannot encode ARM immediate 0x%08X\n", value);
    std::exit(1);
}

uint32_t mov(uint32_t rd, uint32_t value) {
    return 0xE3A00000u | (rd << 12) | encodeImm(value);
}

uint32_t orr(uint32_t rd, uint32_t rn, uint32_t value) {
    return 0xE3800000u | (rn << 16) | (rd << 12) | encodeImm(value);
}

uint32_t strhImm(uint32_t rd, uint32_t rn, uint32_t off) {
    return 0xE1C000B0u | (rn << 16) | (rd << 12) | ((off & 0xF0u) << 4) | (off & 0x0Fu);
}

uint32_t strPost(uint32_t rd, uint32_t rn, uint32_t off) {
    return 0xE4800000u | (1u << 23) | (rn << 16) | (rd << 12) | (off & 0xFFFu);
}

uint32_t subs(uint32_t rd, uint32_t rn, uint32_t value) {
    return 0xE2500000u | (rn << 16) | (rd << 12) | encodeImm(value);
}

uint32_t bneBack(size_t from, size_t to) {
    const int disp = (static_cast<int>(to) - static_cast<int>(from + 8)) / 4;
    return 0x1A000000u | (static_cast<uint32_t>(disp) & 0xFFFFFFu);
}

void put32(std::vector<uint8_t>& rom, size_t at, uint32_t v) {
    rom[at] = static_cast<uint8_t>(v);
    rom[at + 1] = static_cast<uint8_t>(v >> 8);
    rom[at + 2] = static_cast<uint8_t>(v >> 16);
    rom[at + 3] = static_cast<uint8_t>(v >> 24);
}

void emitFill(std::vector<uint8_t>& rom, size_t& p, uint32_t rgb555, uint32_t stores) {
    auto emit = [&](uint32_t inst) {
        put32(rom, p, inst);
        p += 4;
    };
    emit(mov(5, 0x06000000));
    emit(mov(1, rgb555));
    emit(0xE1811801);
    emit(mov(6, stores));
    const size_t loop = p;
    emit(strPost(1, 5, 4));
    emit(subs(6, 6, 1));
    emit(bneBack(p, loop));
}

std::vector<uint8_t> makeTestRom() {
    std::vector<uint8_t> rom(0x8000, 0);
    put32(rom, 0, 0xEA00002E);
    rom[0xB2] = 0x96;
    const char title[] = "EMUCHECK";
    std::memcpy(rom.data() + 0xA0, title, sizeof(title) - 1);
    std::memcpy(rom.data() + 0xAC, "BPRE", 4);

    size_t p = 0xC0;
    auto emit = [&](uint32_t inst) {
        put32(rom, p, inst);
        p += 4;
    };

    emit(mov(0, 0x04000000));
    emit(mov(1, 0x0400));
    emit(orr(1, 1, 3));
    emit(strhImm(1, 0, 0));
    emitFill(rom, p, 0x7C00, 19200);
    emit(mov(5, 0x06000000));
    emit(mov(1, 0x03E0));
    emit(0xE1811801);
    emit(mov(6, 2400));
    const size_t row = p;
    emit(strPost(1, 5, 4));
    emit(subs(6, 6, 1));
    emit(bneBack(p, row));
    emit(0xEAFFFFFE);
    return rom;
}

uint32_t pixelAt(const std::vector<uint32_t>& fb, int x, int y) {
    return fb[static_cast<size_t>(y) * 240 + static_cast<size_t>(x)];
}

int channel(uint32_t px, int shift) {
    return static_cast<int>((px >> shift) & 0xFFu);
}

bool expectColor(const char* where, uint32_t px, int r, int g, int b, int slop) {
    const int pr = channel(px, 0);
    const int pg = channel(px, 8);
    const int pb = channel(px, 16);
    const int pa = channel(px, 24);
    if (pa != 255) {
        std::fprintf(stderr, "%s alpha %d want 255 (pixel %08X)\n", where, pa, px);
        return false;
    }
    if (std::abs(pr - r) > slop || std::abs(pg - g) > slop || std::abs(pb - b) > slop) {
        std::fprintf(stderr, "%s rgb %d,%d,%d want ~%d,%d,%d (pixel %08X)\n", where, pr, pg, pb, r, g, b, px);
        return false;
    }
    return true;
}

void writePpm(const char* path, const std::vector<uint32_t>& fb) {
    std::FILE* f = std::fopen(path, "wb");
    if (!f) {
        return;
    }
    std::fprintf(f, "P6\n240 160\n255\n");
    for (uint32_t px : fb) {
        const unsigned char rgb[3] = {
            static_cast<unsigned char>(channel(px, 0)),
            static_cast<unsigned char>(channel(px, 8)),
            static_cast<unsigned char>(channel(px, 16)),
        };
        std::fwrite(rgb, 1, 3, f);
    }
    std::fclose(f);
}

}  // namespace

int main(int argc, char** argv) {
    using emulocke::gbaNativeToRgba;
    if (gbaNativeToRgba(0x08000000u | 0x0000FF00u) != 0xFF00FF00u) {
        std::fprintf(stderr, "gbaNativeToRgba did not strip layer flags\n");
        return 1;
    }
    if (gbaNativeToRgba(0x0000FF00u) != 0xFF00FF00u) {
        std::fprintf(stderr, "priority-0 sprite alpha was not forced opaque\n");
        return 1;
    }

    const auto rom = makeTestRom();
    const std::filesystem::path romPath = std::filesystem::temp_directory_path() / "emulocke-gba-check.gba";
    const std::filesystem::path savPath = std::filesystem::temp_directory_path() / "emulocke-gba-check.sav";
    if (!emulocke::writeWholeFile(romPath.string(), rom.data(), static_cast<uint32_t>(rom.size()))) {
        std::fprintf(stderr, "failed to write test ROM\n");
        return 1;
    }
    auto session = emulocke::GbaSession::open(romPath.string(), savPath.string());
    if (!session) {
        std::fprintf(stderr, "failed to load test ROM\n");
        return 1;
    }
    for (int i = 0; i < 16; ++i) {
        session->runFrame();
    }
    std::vector<uint32_t> fb(240 * 160);
    session->copyScreen(0, fb.data(), 240 * 4);

    if (!expectColor("mode3 green", pixelAt(fb, 2, 0), 0, 255, 0, 8)) {
        return 1;
    }
    if (!expectColor("mode3 blue", pixelAt(fb, 80, 40), 0, 0, 255, 8)) {
        return 1;
    }
    for (uint32_t px : fb) {
        if (channel(px, 24) != 255) {
            std::fprintf(stderr, "found non-opaque pixel %08X\n", px);
            return 1;
        }
    }
    if (argc > 1) {
        writePpm(argv[1], fb);
    }

    const std::filesystem::path persistSav =
        std::filesystem::temp_directory_path() / "emulocke-gba-persist.sav";
    std::vector<uint8_t> persist(0x20000, 0xA5);
    persist[0x10] = 0x3C;
    if (!emulocke::writeWholeFile(persistSav.string(), persist.data(), static_cast<uint32_t>(persist.size()))) {
        std::fprintf(stderr, "failed to write persist sav\n");
        return 1;
    }
    {
        auto persistSession = emulocke::GbaSession::open(romPath.string(), persistSav.string());
        if (!persistSession) {
            std::fprintf(stderr, "failed to load persist ROM\n");
            return 1;
        }
        for (int i = 0; i < 8; ++i) {
            persistSession->runFrame();
        }
    }
    const auto after = emulocke::readWholeFile(persistSav.string());
    if (after.size() < 0x11 || after[0x10] != 0x3C) {
        std::fprintf(stderr, "gba save was wiped on boot\n");
        return 1;
    }

    std::printf("gba host check ok\n");
    return 0;
}

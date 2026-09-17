#include "adapter/LiveMemory.hpp"
#include "emu/FileBytes.hpp"
#include "emu/RamCapture.hpp"

#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <vector>

namespace {

int fails = 0;

void expect(bool cond, const char* msg) {
    if (!cond) {
        std::fprintf(stderr, "FAIL %s\n", msg);
        ++fails;
    }
}

class FailMemory final : public emulocke::LiveMemory {
public:
    bool read(uint32_t, std::span<uint8_t>) const override { return false; }
};

}  // namespace

int testRamCapture() {
    const auto dir = std::filesystem::temp_directory_path() / "emulocke-ram-capture-check";
    std::filesystem::remove_all(dir);
    std::vector<uint8_t> ram(emulocke::kNdsMainRamBytes, 0);
    ram.front() = 0x11;
    ram.back() = 0x22;
    emulocke::SpanMemory mem(emulocke::kNdsMainRam, ram);
    emulocke::RamCapture cap;
    cap.maybeWrite(mem, true, dir, 0);
    expect(!std::filesystem::exists(dir / "send-in.bin"), "missing dir writes nothing");

    std::filesystem::create_directories(dir);
    cap.maybeWrite(mem, false, dir, 0);
    expect(!std::filesystem::exists(dir / "send-in.bin"), "out of battle writes nothing");

    cap.maybeWrite(mem, true, dir, 0);
    const auto send = emulocke::readWholeFile(dir / "send-in.bin", emulocke::kNdsMainRamBytes);
    const auto after = emulocke::readWholeFile(dir / "after.bin", emulocke::kNdsMainRamBytes);
    expect(send.size() == emulocke::kNdsMainRamBytes && send.front() == 0x11 && send.back() == 0x22,
        "send-in is full main ram");
    expect(after == send, "enter also writes after");

    ram.front() = 0x33;
    cap.maybeWrite(mem, true, dir, emulocke::kRamCaptureGapMs - 1);
    expect(emulocke::readWholeFile(dir / "after.bin", emulocke::kNdsMainRamBytes).front() == 0x11,
        "gap skips rewrite");
    cap.maybeWrite(mem, true, dir, emulocke::kRamCaptureGapMs);
    expect(emulocke::readWholeFile(dir / "after.bin", emulocke::kNdsMainRamBytes).front() == 0x33,
        "after follows live ram");
    expect(emulocke::readWholeFile(dir / "send-in.bin", emulocke::kNdsMainRamBytes).front() == 0x11,
        "send-in stays first frame");

    FailMemory fail;
    const auto before = emulocke::readWholeFile(dir / "after.bin", emulocke::kNdsMainRamBytes);
    cap.maybeWrite(fail, true, dir, emulocke::kRamCaptureGapMs * 2);
    expect(emulocke::readWholeFile(dir / "after.bin", emulocke::kNdsMainRamBytes) == before,
        "failed read keeps last file");

    std::filesystem::remove_all(dir);
    return fails;
}

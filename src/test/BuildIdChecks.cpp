#include "application/BuildId.hpp"
#include "test/BuildIdChecks.hpp"

#include <cstdio>
#include <string>

int testBuildId() {
    using emulocke::DistOs;
    using emulocke::ReleaseChannel;
    using emulocke::artifactFileName;
    using emulocke::windowTitle;
    int fails = 0;
    const auto expectEq = [&](const std::string& got, const char* want, const char* msg) {
        if (got != want) {
            std::fprintf(stderr, "FAIL %s: got [%s] want [%s]\n", msg, got.c_str(), want);
            ++fails;
        }
    };
    expectEq(windowTitle(ReleaseChannel::Stable, "1.2.3", "deadbee", {}), "Emulocke v1.2.3", "stable idle");
    expectEq(windowTitle(ReleaseChannel::Stable, "1.2.3", "deadbee", "Pokemon Fire Red"),
        "Emulocke v1.2.3 - Pok\u00E9mon Fire Red", "stable run");
    expectEq(windowTitle(ReleaseChannel::Vanguard, "1.2.3", "abc1234", {}), "Emulocke VANGUARD [abc1234]",
        "vanguard idle");
    expectEq(windowTitle(ReleaseChannel::Vanguard, "1.2.3", "abc1234", "Pokemon Emerald"),
        "Emulocke VANGUARD [abc1234] - Pok\u00E9mon Emerald", "vanguard run");
    expectEq(windowTitle(ReleaseChannel::Stable, "0.1.0", "deadbee", "Pokemon"),
        "Emulocke v0.1.0 - Pok\u00E9mon", "stable pokemon only");
    expectEq(artifactFileName(ReleaseChannel::Stable, DistOs::WinX64, "1.2.3", "deadbee"),
        "emulocke-v1.2.3-win-x64.exe", "stable win");
    expectEq(artifactFileName(ReleaseChannel::Vanguard, DistOs::WinX64, "1.2.3", "abc1234"),
        "emulocke-vanguard-abc1234-win-x64.exe", "vanguard win");
    expectEq(artifactFileName(ReleaseChannel::Stable, DistOs::LinuxX64, "1.2.3", "deadbee"),
        "emulocke-v1.2.3-linux-x64", "stable linux");
    expectEq(artifactFileName(ReleaseChannel::Vanguard, DistOs::LinuxX64, "1.2.3", "abc1234"),
        "emulocke-vanguard-abc1234-linux-x64", "vanguard linux");
    expectEq(emulocke::windowIconBmp(ReleaseChannel::Stable), "icons/emulocke.bmp", "stable icon");
    expectEq(emulocke::windowIconBmp(ReleaseChannel::Vanguard), "icons/emulocke-vanguard.bmp",
        "vanguard icon");
    const std::string bakedIdle = windowTitle(emulocke::buildChannel(), emulocke::buildVersion(),
        emulocke::buildHash(), {});
    if (emulocke::buildChannel() == ReleaseChannel::Stable) {
        expectEq(bakedIdle, (std::string("Emulocke v") + emulocke::buildVersion()).c_str(), "baked stable");
    } else {
        expectEq(bakedIdle, (std::string("Emulocke VANGUARD [") + emulocke::buildHash() + "]").c_str(),
            "baked vanguard");
    }
    if (std::string(emulocke::buildVersion()).empty() || std::string(emulocke::buildHash()).empty()) {
        std::fprintf(stderr, "FAIL baked stamp empty\n");
        ++fails;
    }
    return fails;
}

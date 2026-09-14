#pragma once

#include <string>
#include <string_view>

namespace emulocke {

enum class ReleaseChannel { Stable, Vanguard };
enum class DistOs { LinuxX64, WinX64 };

ReleaseChannel buildChannel();
const char* buildVersion();
const char* buildHash();

std::string windowTitle(ReleaseChannel channel, std::string_view version, std::string_view hash,
    std::string_view gameTitle);
std::string artifactFileName(ReleaseChannel channel, DistOs os, std::string_view version,
    std::string_view hash);
const char* windowIconBmp(ReleaseChannel channel);

}

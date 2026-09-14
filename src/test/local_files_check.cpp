#include "emu/Paths.hpp"
#include "test/Check.hpp"

#include <Platform.h>

#include <filesystem>
#include <string>

namespace {

bool insidePrefDir(const std::string& resolved) {
    const auto pref = emulocke::prefDir().lexically_normal();
    const auto path = std::filesystem::path(resolved).lexically_normal();
    return !resolved.empty() && path.string().rfind(pref.string(), 0) == 0;
}

}  // namespace

void testLocalFilePaths() {
    using melonDS::Platform::GetLocalFilePath;
    REQUIRE(insidePrefDir(GetLocalFilePath("firmware.bin")));
    REQUIRE(insidePrefDir(GetLocalFilePath("nested/dir/rtc.bin")));
    REQUIRE(GetLocalFilePath("../prefs.ini").empty());
    REQUIRE(GetLocalFilePath("nested/../../escape").empty());
    REQUIRE(GetLocalFilePath("..").empty());
    REQUIRE(GetLocalFilePath("safe/..hidden").size() > 0);
    REQUIRE(insidePrefDir(GetLocalFilePath("safe/..hidden")));
    REQUIRE(melonDS::Platform::OpenLocalFile("../escape.bin", melonDS::Platform::FileMode::Read) == nullptr);
    REQUIRE(!melonDS::Platform::LocalFileExists("../.."));
    REQUIRE(!melonDS::Platform::CheckLocalFileWritable("../escape.bin"));
    const auto absolute = std::filesystem::temp_directory_path() / "emulocke-abs.bin";
    REQUIRE(GetLocalFilePath(absolute.string()) == absolute.string());
    REQUIRE(emulocke::pathFromUtf8("runs/abc").filename() == "abc");
}

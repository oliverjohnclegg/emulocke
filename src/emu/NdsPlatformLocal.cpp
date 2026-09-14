#include "emu/Paths.hpp"

#include <Platform.h>

#include <filesystem>
#include <string>

namespace melonDS::Platform {
namespace {

bool climbsOutOfDirectory(const std::filesystem::path& relative) {
    for (const auto& segment : relative) {
        if (segment == "..") {
            return true;
        }
    }
    return false;
}

}  // namespace

std::string GetLocalFilePath(const std::string& filename) {
    const std::filesystem::path relative(filename);
    if (relative.is_absolute()) {
        return filename;
    }
    if (climbsOutOfDirectory(relative)) {
        return {};
    }
    return emulocke::localDataPath(filename);
}

FileHandle* OpenLocalFile(const std::string& path, FileMode mode) {
    const std::string resolved = GetLocalFilePath(path);
    return resolved.empty() ? nullptr : OpenFile(resolved, mode);
}

bool LocalFileExists(const std::string& name) {
    const std::string resolved = GetLocalFilePath(name);
    return !resolved.empty() && FileExists(resolved);
}

bool CheckLocalFileWritable(const std::string& name) {
    const std::string resolved = GetLocalFilePath(name);
    return !resolved.empty() && CheckFileWritable(resolved);
}

}

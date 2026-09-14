#include "emu/FileBytes.hpp"

#include <Platform.h>

#include <cstdarg>
#include <cstdio>
#include <filesystem>
#include <string>

namespace melonDS::Platform {

FileHandle* OpenFile(const std::string& path, FileMode mode) {
    if ((mode & (FileMode::ReadWrite | FileMode::Append)) == FileMode::None) {
        return nullptr;
    }
    FILE* fp = std::fopen(path.c_str(), emulocke::fopenMode(static_cast<unsigned>(mode)).c_str());
    return reinterpret_cast<FileHandle*>(fp);
}

bool FileExists(const std::string& name) {
    return std::filesystem::exists(name);
}

bool CheckFileWritable(const std::string& filepath) {
    FILE* fp = std::fopen(filepath.c_str(), "ab");
    if (!fp) {
        return false;
    }
    std::fclose(fp);
    return true;
}

bool CloseFile(FileHandle* file) {
    return file && std::fclose(reinterpret_cast<FILE*>(file)) == 0;
}

bool IsEndOfFile(FileHandle* file) {
    return file && std::feof(reinterpret_cast<FILE*>(file)) != 0;
}

bool FileReadLine(char* str, int count, FileHandle* file) {
    return file && std::fgets(str, count, reinterpret_cast<FILE*>(file));
}

u64 FilePosition(FileHandle* file) {
    return file ? static_cast<u64>(std::ftell(reinterpret_cast<FILE*>(file))) : 0;
}

bool FileSeek(FileHandle* file, s64 offset, FileSeekOrigin origin) {
    int whence = SEEK_SET;
    if (origin == FileSeekOrigin::Current) whence = SEEK_CUR;
    if (origin == FileSeekOrigin::End) whence = SEEK_END;
    return file && std::fseek(reinterpret_cast<FILE*>(file), static_cast<long>(offset), whence) == 0;
}

void FileRewind(FileHandle* file) {
    if (file) {
        std::rewind(reinterpret_cast<FILE*>(file));
    }
}

u64 FileRead(void* data, u64 size, u64 count, FileHandle* file) {
    if (!file) {
        return 0;
    }
    return std::fread(data, static_cast<size_t>(size), static_cast<size_t>(count), reinterpret_cast<FILE*>(file));
}

bool FileFlush(FileHandle* file) {
    return file && std::fflush(reinterpret_cast<FILE*>(file)) == 0;
}

u64 FileWrite(const void* data, u64 size, u64 count, FileHandle* file) {
    if (!file) {
        return 0;
    }
    return std::fwrite(data, static_cast<size_t>(size), static_cast<size_t>(count), reinterpret_cast<FILE*>(file));
}

u64 FileWriteFormatted(FileHandle* file, const char* fmt, ...) {
    if (!file) {
        return 0;
    }
    va_list args;
    va_start(args, fmt);
    const int n = std::vfprintf(reinterpret_cast<FILE*>(file), fmt, args);
    va_end(args);
    return n < 0 ? 0 : static_cast<u64>(n);
}

u64 FileLength(FileHandle* file) {
    if (!file) {
        return 0;
    }
    FILE* fp = reinterpret_cast<FILE*>(file);
    const long cur = std::ftell(fp);
    std::fseek(fp, 0, SEEK_END);
    const long end = std::ftell(fp);
    std::fseek(fp, cur, SEEK_SET);
    return end < 0 ? 0 : static_cast<u64>(end);
}

}
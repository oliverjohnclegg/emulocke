#include "emu/FileBytes.hpp"

#include <cstdio>
#include <fstream>

namespace emulocke {

std::string fopenMode(unsigned mode) {
    const bool read = mode & 0x1;
    const bool write = mode & 0x2;
    const bool preserve = mode & 0x4;
    const bool append = mode & 0x20;
    const bool text = mode & 0x10;
    std::string s;
    if (append) {
        s = "a";
    } else if (write && !preserve) {
        s = "w";
    } else {
        s = "r";
    }
    if (read && write) {
        s += "+";
    }
    if (!text) {
        s += "b";
    }
    return s;
}

bool writeWholeFile(const std::string& path, const uint8_t* data, uint32_t length) {
    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    if (!out) {
        return false;
    }
    out.write(reinterpret_cast<const char*>(data), static_cast<std::streamsize>(length));
    return static_cast<bool>(out);
}

std::vector<uint8_t> readWholeFile(const std::string& path) {
    std::ifstream in(path, std::ios::binary | std::ios::ate);
    if (!in) {
        return {};
    }
    const auto size = in.tellg();
    in.seekg(0);
    std::vector<uint8_t> bytes(static_cast<size_t>(size));
    in.read(reinterpret_cast<char*>(bytes.data()), size);
    return bytes;
}

}
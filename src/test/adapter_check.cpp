#include "test/Check.hpp"

#include <cstdio>

int main() {
    testGen3Codec();
    testFrlgAdapter();
    std::printf("adapter check ok\n");
    return 0;
}
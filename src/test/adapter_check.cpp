#include "test/Check.hpp"

#include <cstdio>

int main() {
    testGen3Codec();
    testFrlgAdapter();
    testFrlgDifficulty();
    testRseAdapter();
    testGen4Adapter();
    testGen5Adapter();
    testSaveBounds();
    testSnapshotContract();
    testLocalSaves();
    std::printf("adapter check ok\n");
    return 0;
}
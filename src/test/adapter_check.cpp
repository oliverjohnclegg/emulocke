#include "test/Check.hpp"

#include <cstdio>

int main() {
    testGen3Codec();
    testFrlgAdapter();
    testFrlgSpecies();
    testFrlgDifficulty();
    testFrlgBoxes();
    testRseAdapter();
    testGen4Adapter();
    testGen4Battle();
    testGen5Adapter();
    testGen5Battle();
    testSaveBounds();
    testSnapshotContract();
    testLocalSaves();
    testBatteryWatch();
    std::printf("adapter check ok\n");
    return 0;
}
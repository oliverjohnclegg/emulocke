#include "test/Check.hpp"

#include <cstdio>

void testTrackerAtlas();
void testTrackerFill();
void testTrackerRivalFill();
void testPreviewSuite();

int main() {
    testTrackerAtlas();
    testTrackerFill();
    testTrackerRivalFill();
    testPreviewSuite();
    std::printf("tracker check ok\n");
    return 0;
}

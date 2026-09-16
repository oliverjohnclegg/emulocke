#include "test/Check.hpp"

#include <cstdio>

void testTrackerAtlas();
void testTrackerFill();
void testTrackerRivalFill();
void testPreviewSuite();
void testTrackerSnap();

int main() {
    testTrackerAtlas();
    testTrackerFill();
    testTrackerRivalFill();
    testPreviewSuite();
    testTrackerSnap();
    std::printf("tracker check ok\n");
    return 0;
}

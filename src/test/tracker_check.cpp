#include "test/Check.hpp"

#include <cstdio>

void testTrackerAtlas();
void testTrackerFill();
void testTrackerRivalFill();

int main() {
    testTrackerAtlas();
    testTrackerFill();
    testTrackerRivalFill();
    std::printf("tracker check ok\n");
    return 0;
}

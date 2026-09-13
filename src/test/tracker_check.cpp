#include "test/Check.hpp"

#include <cstdio>

void testTrackerAtlas();
void testTrackerFill();

int main() {
    testTrackerAtlas();
    testTrackerFill();
    std::printf("tracker check ok\n");
    return 0;
}

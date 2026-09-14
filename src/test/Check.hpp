#pragma once

#include <cstdio>
#include <cstdlib>

#define REQUIRE(cond) \
    do { \
        if (!(cond)) { \
            std::fprintf(stderr, "fail %s:%d: %s\n", __FILE__, __LINE__, #cond); \
            std::exit(1); \
        } \
    } while (0)

void testGen3Codec();
void testFrlgAdapter();
void testFrlgDifficulty();
void testRseAdapter();
void testGen4Adapter();
void testGen5Adapter();
void testSaveBounds();
void testLocalSaves();
void testSnapshotContract();

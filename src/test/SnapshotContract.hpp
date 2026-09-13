#pragma once

#include "adapter/Snapshot.hpp"

void requireSnapshotForSuite(const emulocke::GameSnapshot& snap, const char* via);
void testSnapshotContract();

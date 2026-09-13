#pragma once

#include <cstdint>
#include <vector>

enum class SuiteSav { Frlg, Rse, Dp, Pt, Hgss, Gen5 };

std::vector<uint8_t> makeSuiteSav(SuiteSav kind);

#pragma once

#include <imgui.h>

namespace emulocke {

inline constexpr ImVec4 kChassis{20 / 255.f, 22 / 255.f, 26 / 255.f, 1.f};
inline constexpr ImVec4 kMenuStrip{16 / 255.f, 18 / 255.f, 24 / 255.f, 1.f};
inline constexpr ImVec4 kPanel{27 / 255.f, 30 / 255.f, 38 / 255.f, 1.f};
inline constexpr ImVec4 kScreenWell{11 / 255.f, 13 / 255.f, 17 / 255.f, 1.f};
inline constexpr ImVec4 kPopup{22 / 255.f, 25 / 255.f, 32 / 255.f, 0.98f};
inline constexpr ImVec4 kCream{239 / 255.f, 228 / 255.f, 204 / 255.f, 1.f};
inline constexpr ImVec4 kIvory{237 / 255.f, 230 / 255.f, 214 / 255.f, 1.f};
inline constexpr ImVec4 kOnCream{26 / 255.f, 28 / 255.f, 32 / 255.f, 1.f};
inline constexpr ImVec4 kDisabled{138 / 255.f, 132 / 255.f, 120 / 255.f, 1.f};
inline constexpr ImVec4 kButton{34 / 255.f, 38 / 255.f, 47 / 255.f, 1.f};
inline constexpr ImVec4 kButtonHover{58 / 255.f, 55 / 255.f, 47 / 255.f, 1.f};
inline constexpr ImVec4 kButtonActive{74 / 255.f, 67 / 255.f, 56 / 255.f, 1.f};
inline constexpr ImVec4 kFrame{18 / 255.f, 20 / 255.f, 26 / 255.f, 1.f};
inline constexpr ImVec4 kBorder{239 / 255.f, 228 / 255.f, 204 / 255.f, 0.35f};
inline constexpr ImVec4 kHeader{56 / 255.f, 52 / 255.f, 44 / 255.f, 1.f};
inline constexpr ImVec4 kHeaderHover{72 / 255.f, 66 / 255.f, 54 / 255.f, 1.f};
inline constexpr ImVec4 kHeaderActive{96 / 255.f, 86 / 255.f, 68 / 255.f, 1.f};
inline constexpr ImU32 kPaused = IM_COL32(227, 28, 28, 255);

void applyTheme();
ImFont* loadDisplayFont();
ImFont* loadBodyFont();

}

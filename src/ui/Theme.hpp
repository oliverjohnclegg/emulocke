#pragma once

#include <imgui.h>

namespace emulocke {

inline constexpr ImVec4 kChassis{26 / 255.f, 26 / 255.f, 28 / 255.f, 1.f};
inline constexpr ImVec4 kMenuStrip{20 / 255.f, 20 / 255.f, 22 / 255.f, 1.f};
inline constexpr ImVec4 kPanel{36 / 255.f, 36 / 255.f, 38 / 255.f, 1.f};
inline constexpr ImVec4 kScreenWell{12 / 255.f, 12 / 255.f, 13 / 255.f, 1.f};
inline constexpr ImVec4 kPopup{30 / 255.f, 30 / 255.f, 32 / 255.f, 0.98f};
inline constexpr ImVec4 kMetal{215 / 255.f, 205 / 255.f, 189 / 255.f, 1.f};
inline constexpr ImVec4 kDisabled{120 / 255.f, 116 / 255.f, 110 / 255.f, 1.f};
inline constexpr ImVec4 kButton{42 / 255.f, 42 / 255.f, 44 / 255.f, 1.f};
inline constexpr ImVec4 kButtonHover{54 / 255.f, 54 / 255.f, 56 / 255.f, 1.f};
inline constexpr ImVec4 kButtonActive{66 / 255.f, 66 / 255.f, 68 / 255.f, 1.f};
inline constexpr ImVec4 kFrame{22 / 255.f, 22 / 255.f, 23 / 255.f, 1.f};
inline constexpr ImVec4 kBorder{215 / 255.f, 205 / 255.f, 189 / 255.f, 0.22f};
inline constexpr ImVec4 kHeader{42 / 255.f, 42 / 255.f, 44 / 255.f, 1.f};
inline constexpr ImVec4 kHeaderHover{54 / 255.f, 54 / 255.f, 56 / 255.f, 1.f};
inline constexpr ImVec4 kHeaderActive{66 / 255.f, 66 / 255.f, 68 / 255.f, 1.f};
inline constexpr ImU32 kPaused = IM_COL32(196, 43, 43, 255);
inline constexpr ImVec4 kStatUp{196 / 255.f, 43 / 255.f, 43 / 255.f, 1.f};
inline constexpr ImVec4 kStatDown{88 / 255.f, 148 / 255.f, 196 / 255.f, 1.f};

void applyTheme();
ImFont* loadDisplayFont();
ImFont* loadBodyFont();

}

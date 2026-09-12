#include "ui/Theme.hpp"

#include "emu/Paths.hpp"

#include <string>

namespace emulocke {
namespace {

ImFont* loadAssetFont(const char* file, float size) {
    ImFontConfig cfg;
    cfg.PixelSnapH = true;
    const std::string path = assetPath(file);
    return ImGui::GetIO().Fonts->AddFontFromFileTTF(
        path.c_str(), size, &cfg, ImGui::GetIO().Fonts->GetGlyphRangesDefault());
}

}  // namespace

void applyTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.f;
    style.ChildRounding = 0.f;
    style.FrameRounding = 0.f;
    style.GrabRounding = 0.f;
    style.PopupRounding = 0.f;
    style.WindowPadding = ImVec2(5.f, 5.f);
    style.FramePadding = ImVec2(8.f, 3.f);
    style.ItemSpacing = ImVec2(5.f, 5.f);
    style.ScrollbarSize = 10.f;
    style.WindowBorderSize = 0.f;
    style.ChildBorderSize = 1.f;
    style.FrameBorderSize = 1.f;
    style.PopupBorderSize = 1.f;
    style.TabRounding = 0.f;
    style.TabBorderSize = 1.f;
    style.TabBarBorderSize = 1.f;
    style.TabBarOverlineSize = 2.f;
    style.TabMinWidthBase = 72.f;
    ImVec4* c = style.Colors;
    c[ImGuiCol_WindowBg] = kChassis;
    c[ImGuiCol_ChildBg] = kPanel;
    c[ImGuiCol_PopupBg] = kPopup;
    c[ImGuiCol_Border] = kBorder;
    c[ImGuiCol_Text] = kMetal;
    c[ImGuiCol_TextDisabled] = kDisabled;
    c[ImGuiCol_Header] = kHeader;
    c[ImGuiCol_HeaderHovered] = kHeaderHover;
    c[ImGuiCol_HeaderActive] = kHeaderActive;
    c[ImGuiCol_Button] = kButton;
    c[ImGuiCol_ButtonHovered] = kButtonHover;
    c[ImGuiCol_ButtonActive] = kButtonActive;
    c[ImGuiCol_FrameBg] = kFrame;
    c[ImGuiCol_FrameBgHovered] = kHeader;
    c[ImGuiCol_FrameBgActive] = kHeaderHover;
    c[ImGuiCol_MenuBarBg] = kMenuStrip;
    c[ImGuiCol_TitleBg] = kMenuStrip;
    c[ImGuiCol_TitleBgActive] = kMenuStrip;
    c[ImGuiCol_Separator] = kBorder;
    c[ImGuiCol_SeparatorHovered] = ImVec4(kMetal.x, kMetal.y, kMetal.z, 0.45f);
    c[ImGuiCol_SeparatorActive] = kMetal;
    c[ImGuiCol_NavCursor] = kMetal;
    c[ImGuiCol_ScrollbarGrab] = ImVec4(kMetal.x, kMetal.y, kMetal.z, 0.40f);
    c[ImGuiCol_ScrollbarGrabHovered] = ImVec4(kMetal.x, kMetal.y, kMetal.z, 0.70f);
    c[ImGuiCol_ScrollbarGrabActive] = kMetal;
    c[ImGuiCol_CheckMark] = kMetal;
    c[ImGuiCol_SliderGrab] = ImVec4(kMetal.x, kMetal.y, kMetal.z, 0.70f);
    c[ImGuiCol_SliderGrabActive] = kMetal;
    c[ImGuiCol_ModalWindowDimBg] = ImVec4(kChassis.x, kChassis.y, kChassis.z, 0.72f);
    c[ImGuiCol_Tab] = kMenuStrip;
    c[ImGuiCol_TabHovered] = kHeaderHover;
    c[ImGuiCol_TabSelected] = kButton;
    c[ImGuiCol_TabSelectedOverline] = kMetal;
    c[ImGuiCol_TabDimmed] = kMenuStrip;
    c[ImGuiCol_TabDimmedSelected] = kButton;
    c[ImGuiCol_TabDimmedSelectedOverline] = kMetal;
}

ImFont* loadDisplayFont() {
    return loadAssetFont("fonts/MPLUSRounded1c-Medium.ttf", 20.f);
}

ImFont* loadBodyFont() {
    return loadAssetFont("fonts/FiraSans-Regular.ttf", 15.f);
}

}

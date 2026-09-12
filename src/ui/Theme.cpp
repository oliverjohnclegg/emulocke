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
    style.ChildRounding = 4.f;
    style.FrameRounding = 4.f;
    style.GrabRounding = 4.f;
    style.PopupRounding = 4.f;
    style.WindowPadding = ImVec2(12.f, 10.f);
    style.FramePadding = ImVec2(8.f, 5.f);
    style.ItemSpacing = ImVec2(10.f, 8.f);
    style.ScrollbarSize = 10.f;
    style.WindowBorderSize = 0.f;
    style.ChildBorderSize = 1.f;
    style.FrameBorderSize = 1.f;
    style.PopupBorderSize = 1.f;
    ImVec4* c = style.Colors;
    c[ImGuiCol_WindowBg] = kChassis;
    c[ImGuiCol_ChildBg] = kPanel;
    c[ImGuiCol_PopupBg] = kPopup;
    c[ImGuiCol_Border] = kBorder;
    c[ImGuiCol_Text] = kIvory;
    c[ImGuiCol_TextDisabled] = kDisabled;
    c[ImGuiCol_Header] = kHeader;
    c[ImGuiCol_HeaderHovered] = kHeaderHover;
    c[ImGuiCol_HeaderActive] = kHeaderActive;
    c[ImGuiCol_Button] = kButton;
    c[ImGuiCol_ButtonHovered] = kButtonHover;
    c[ImGuiCol_ButtonActive] = kButtonActive;
    c[ImGuiCol_FrameBg] = kFrame;
    c[ImGuiCol_FrameBgHovered] = kHeaderHover;
    c[ImGuiCol_FrameBgActive] = kHeaderActive;
    c[ImGuiCol_MenuBarBg] = kMenuStrip;
    c[ImGuiCol_TitleBg] = kMenuStrip;
    c[ImGuiCol_TitleBgActive] = kMenuStrip;
    c[ImGuiCol_Separator] = kBorder;
    c[ImGuiCol_ScrollbarGrab] = ImVec4(kCream.x, kCream.y, kCream.z, 0.40f);
    c[ImGuiCol_ScrollbarGrabHovered] = ImVec4(kCream.x, kCream.y, kCream.z, 0.70f);
    c[ImGuiCol_ScrollbarGrabActive] = kCream;
}

ImFont* loadDisplayFont() {
    return loadAssetFont("fonts/MPLUSRounded1c-Medium.ttf", 20.f);
}

ImFont* loadBodyFont() {
    return loadAssetFont("fonts/FiraSans-Regular.ttf", 15.f);
}

}

#include "ui/Theme.hpp"

#include "emu/Paths.hpp"

#include <imgui.h>

namespace emulocke {

void applyTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.f;
    style.ChildRounding = 2.f;
    style.FrameRounding = 2.f;
    style.GrabRounding = 2.f;
    style.WindowPadding = ImVec2(12.f, 10.f);
    style.FramePadding = ImVec2(10.f, 6.f);
    style.ItemSpacing = ImVec2(10.f, 8.f);
    style.ScrollbarSize = 10.f;
    style.WindowBorderSize = 0.f;
    style.ChildBorderSize = 1.f;
    ImVec4* c = style.Colors;
    c[ImGuiCol_WindowBg] = ImVec4(0.071f, 0.063f, 0.055f, 1.f);
    c[ImGuiCol_ChildBg] = ImVec4(0.102f, 0.090f, 0.078f, 1.f);
    c[ImGuiCol_PopupBg] = ImVec4(0.090f, 0.078f, 0.067f, 0.98f);
    c[ImGuiCol_Border] = ImVec4(0.22f, 0.16f, 0.14f, 1.f);
    c[ImGuiCol_Text] = ImVec4(0.843f, 0.804f, 0.745f, 1.f);
    c[ImGuiCol_TextDisabled] = ImVec4(0.48f, 0.44f, 0.41f, 1.f);
    c[ImGuiCol_Header] = ImVec4(0.77f, 0.17f, 0.17f, 0.45f);
    c[ImGuiCol_HeaderHovered] = ImVec4(0.77f, 0.17f, 0.17f, 0.70f);
    c[ImGuiCol_HeaderActive] = ImVec4(0.77f, 0.17f, 0.17f, 0.90f);
    c[ImGuiCol_Button] = ImVec4(0.18f, 0.14f, 0.12f, 1.f);
    c[ImGuiCol_ButtonHovered] = ImVec4(0.77f, 0.17f, 0.17f, 0.55f);
    c[ImGuiCol_ButtonActive] = ImVec4(0.77f, 0.17f, 0.17f, 0.80f);
    c[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.10f, 0.09f, 1.f);
    c[ImGuiCol_MenuBarBg] = ImVec4(0.055f, 0.047f, 0.043f, 1.f);
    c[ImGuiCol_TitleBg] = ImVec4(0.055f, 0.047f, 0.043f, 1.f);
    c[ImGuiCol_TitleBgActive] = ImVec4(0.77f, 0.17f, 0.17f, 0.35f);
    c[ImGuiCol_Separator] = ImVec4(0.77f, 0.17f, 0.17f, 0.45f);
    c[ImGuiCol_ScrollbarGrab] = ImVec4(0.77f, 0.17f, 0.17f, 0.55f);
}

ImFont* loadDisplayFont() {
    const std::string path = assetPath("fonts/Oxanium-SemiBold.ttf");
    return ImGui::GetIO().Fonts->AddFontFromFileTTF(path.c_str(), 20.f);
}

ImFont* loadBodyFont() {
    const std::string path = assetPath("fonts/ShareTechMono-Regular.ttf");
    return ImGui::GetIO().Fonts->AddFontFromFileTTF(path.c_str(), 15.f);
}

}
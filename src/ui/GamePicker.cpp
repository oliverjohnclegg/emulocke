#include "ui/GamePicker.hpp"

#include "application/Application.hpp"
#include "run/Catalog.hpp"
#include "ui/GameStrip.hpp"

#include <imgui.h>
#include <cctype>
#include <string>
#include <string_view>

namespace emulocke {
namespace {

bool containsInsensitive(std::string_view hay, std::string_view needle) {
    if (needle.empty()) {
        return true;
    }
    if (needle.size() > hay.size()) {
        return false;
    }
    for (size_t i = 0; i + needle.size() <= hay.size(); ++i) {
        size_t j = 0;
        while (j < needle.size()) {
            const char a = static_cast<char>(std::tolower(static_cast<unsigned char>(hay[i + j])));
            const char b = static_cast<char>(std::tolower(static_cast<unsigned char>(needle[j])));
            if (a != b) {
                break;
            }
            ++j;
        }
        if (j == needle.size()) {
            return true;
        }
    }
    return false;
}

bool titleMatches(const CatalogTitle& title, std::string_view query) {
    const std::string listed = catalogListTitle(title);
    return containsInsensitive(title.title, query) || containsInsensitive(listed, query) ||
           containsInsensitive(title.fullName, query) || containsInsensitive(title.version, query) ||
           containsInsensitive(title.details, query) || containsInsensitive(title.slug, query) ||
           containsInsensitive(title.creator, query);
}

}  // namespace

void drawGamePicker(Application& app, std::string& catalogUuid) {
    app.gameArt().requestPrefetch();
    const CatalogTitle* selected = catalogByUuid(catalogUuid);
    if (!selected && !catalogTitles().empty()) {
        selected = &catalogTitles().front();
        for (const CatalogTitle& title : catalogTitles()) {
            if (app.romLibrary().ready(title)) {
                selected = &title;
                break;
            }
        }
        catalogUuid = selected->uuid;
    }
    ImGui::SetNextWindowSizeConstraints(ImVec2(0.f, 0.f), ImVec2(800.f, kTitleStripH * 8.f + 40.f));
    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6.f, 20.f));
    if (app.kitFocus().focusSearch) {
        ImGui::OpenPopup("##game");
        app.kitFocus().focusSearch = false;
    }
    const bool open = ImGui::BeginCombo("##game", nullptr, ImGuiComboFlags_HeightLarge);
    const ImVec2 previewMin = ImGui::GetItemRectMin();
    const ImVec2 previewMax = ImGui::GetItemRectMax();
    const float arrow = ImGui::GetFrameHeight();
    const bool preview = selected && ImGui::IsItemVisible();
    ImGui::PopStyleVar();
    if (open) {
        static char query[64];
        if (ImGui::IsWindowAppearing()) {
            query[0] = 0;
            ImGui::SetKeyboardFocusHere();
        }
        ImGui::SetNextItemWidth(-1.f);
        ImGui::InputTextWithHint("##search", "SEARCH", query, sizeof(query));
        int shown = 0;
        for (const CatalogTitle* title : catalogPickerRows()) {
            if (titleMatches(*title, query)) {
                drawTitleStripRow(app, *title, catalogUuid);
                ++shown;
            }
        }
        if (shown == 0) {
            ImGui::TextDisabled("No games.");
        }
        ImGui::EndCombo();
    }
    if (preview) {
        const bool ready = app.romLibrary().ready(*selected);
        drawTitleStrip(app, *selected, previewMin, ImVec2(previewMax.x - arrow, previewMax.y), ready);
    }
}

}

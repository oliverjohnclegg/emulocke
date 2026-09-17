#include "ui/NewRunOptions.hpp"

#include "application/Application.hpp"
#include "run/Catalog.hpp"
#include "ui/KitNav.hpp"

#include <imgui.h>
#include <vector>

namespace emulocke {

void applyNewRunKit(Application& app, bool canStart) {
    if (ImGui::GetIO().WantTextInput) {
        return;
    }
    KitFocus& focus = app.kitFocus();
    const KitFrame& kit = app.kit();
    if (kitModalHold()) {
        focus.modalIndex = 0;
        return;
    }
    if (kit.pause) {
        app.dismissNewRun();
        ImGui::CloseCurrentPopup();
        return;
    }
    const std::vector<const CatalogTitle*> rows = catalogPickerRows();
    int cur = 0;
    for (int i = 0; i < static_cast<int>(rows.size()); ++i) {
        if (app.newRunDraft().catalogUuid == rows[static_cast<std::size_t>(i)]->uuid) {
            cur = i;
            break;
        }
    }
    const int was = cur;
    kitMove(cur, static_cast<int>(rows.size()), kit.up, kit.down);
    if (cur != was && !rows.empty()) {
        selectNewRunTitle(app.newRunDraft(), *rows[static_cast<std::size_t>(cur)]);
    }
    kitMove(focus.modalIndex, 3, kit.left, kit.right);
    if (!kit.act) {
        return;
    }
    if (focus.modalIndex == 0 && canStart) {
        app.confirmNewRun();
        ImGui::CloseCurrentPopup();
    } else if (focus.modalIndex == 1) {
        app.dismissNewRun();
        ImGui::CloseCurrentPopup();
    } else if (focus.modalIndex == 2 && canStart) {
        app.requestImportSav();
    }
}

}

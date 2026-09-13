#include "ui/NewRunOptions.hpp"

#include <imgui.h>
#include <string>

namespace emulocke {

void selectNewRunTitle(NewRunDraft& draft, const CatalogTitle& title) {
    draft.catalogUuid = title.uuid;
    draft.patchOption = std::string(catalogOptionId(title, {}));
}

void drawOptionalPatches(NewRunDraft& draft, const CatalogTitle& title) {
    if (title.optionCount == 0 || !title.options) {
        return;
    }
    ImGui::Text("Optional Patches");
    for (uint8_t i = 0; i < title.optionCount; ++i) {
        const PatchOption& option = title.options[i];
        if (i > 0) {
            ImGui::SameLine();
        }
        if (ImGui::RadioButton(option.label, draft.patchOption == option.id)) {
            draft.patchOption = option.id;
        }
    }
}

}

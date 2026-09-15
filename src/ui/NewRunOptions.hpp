#pragma once

#include "run/Catalog.hpp"
#include "run/NuzlockeRules.hpp"
#include "run/Run.hpp"

namespace emulocke {

void selectNewRunTitle(NewRunDraft& draft, const CatalogTitle& title);
void bindNewRunTitle(NewRunDraft& draft, const CatalogTitle& title);
void drawGameConfig(NewRunDraft& draft, const CatalogTitle& title);
void drawNuzlockeSettings(NuzlockeRules& rules, bool& allowCheats);

}

#pragma once

#include "run/Catalog.hpp"
#include "run/NuzlockeRules.hpp"
#include "run/Run.hpp"

namespace emulocke {

class Application;

void selectNewRunTitle(NewRunDraft& draft, const CatalogTitle& title);
void bindNewRunTitle(NewRunDraft& draft, const CatalogTitle& title);
void applyNewRunKit(Application& app, bool canStart);
void drawGameConfig(NewRunDraft& draft, const CatalogTitle& title);
void drawNuzlockeSettings(NuzlockeRules& rules, bool& allowCheats);

}

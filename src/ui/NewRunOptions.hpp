#pragma once

#include "run/Catalog.hpp"
#include "run/Run.hpp"

namespace emulocke {

void selectNewRunTitle(NewRunDraft& draft, const CatalogTitle& title);
void drawOptionalPatches(NewRunDraft& draft, const CatalogTitle& title);

}

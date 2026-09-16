#pragma once

#include "run/Run.hpp"

namespace emulocke {

class Application;

bool drawRunStrip(Application& app, const Run& run, bool focus = false);

}

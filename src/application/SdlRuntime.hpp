#pragma once

#include <cstdint>

namespace emulocke {

class SdlRuntime {
public:
    SdlRuntime();
    ~SdlRuntime();
    SdlRuntime(const SdlRuntime&) = delete;
    SdlRuntime& operator=(const SdlRuntime&) = delete;
    bool ok() const { return ok_; }

private:
    bool ok_{false};
};

}

#pragma once

#include "Task.h"

namespace plenty_healing {

class PlentyHealing {

public:
    static PlentyHealing &getInstance();

    PlentyHealing(ll::mod::NativeMod &self) : mSelf(self) {};

    [[nodiscard]] ll::mod::NativeMod &getSelf() const { return mSelf; }

    /// @return True if the mod is loaded successfully.
    bool load();

    /// @return True if the mod is enabled successfully.
    bool enable();

    /// @return True if the mod is disabled successfully.
    bool disable();

private:
    ll::mod::NativeMod &mSelf;
};

} // namespace plenty_healing

#include "mod/PlentyHealing.h"

#include <memory>

#include "ll/api/mod/RegisterHelper.h"

namespace plenty_healing {

static std::unique_ptr<PlentyHealing> instance;

PlentyHealing& PlentyHealing::getInstance() { return *instance; }


bool PlentyHealing::load() {
    getSelf().getLogger().debug("Loading...");
    // Code for loading the mod goes here.
    return true;
}

bool PlentyHealing::enable() {
    getSelf().getLogger().debug("Enabling...");
    // Code for enabling the mod goes here.
    return true;
}

bool PlentyHealing::disable() {
    getSelf().getLogger().debug("Disabling...");
    // Code for disabling the mod goes here.
    return true;
}

} // namespace my_mod

LL_REGISTER_MOD(plenty_healing::PlentyHealing, plenty_healing::instance);

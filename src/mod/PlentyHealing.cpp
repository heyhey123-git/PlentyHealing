#include "mod/PlentyHealing.h"

#include "Listeners.h"
#include "PlentyHealing.h"
#include "ll/api/mod/RegisterHelper.h"

#include <memory>

namespace plenty_healing {
    using tasks_map = std::unordered_map<mce::UUID, std::shared_ptr<Task>>;

static std::unique_ptr<PlentyHealing> instance;

PlentyHealing &PlentyHealing::getInstance() { return *instance; }

bool PlentyHealing::load() { return true; }

bool PlentyHealing::enable() {
    listeners::registerListeners();
    tasksMap = std::make_shared<tasks_map>();
    return true;
}

bool PlentyHealing::disable() {
    listeners::unRegisterListeners();
    for (auto &pair : *tasksMap) {
        pair.second->cancel();
    }
    tasksMap.reset();

    return true;
}

std::weak_ptr<tasks_map> PlentyHealing::getTasksMap() { return this->tasksMap; }

std::weak_ptr<ll::schedule::GameTickScheduler> PlentyHealing::getScheduler() { return this->scheduler; }

} // namespace plenty_healing

LL_REGISTER_MOD(plenty_healing::PlentyHealing, plenty_healing::instance);

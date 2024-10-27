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
    tasksMap.emplace();
    scheduler.emplace();
    listeners::registerListeners();
    return true;
}

bool PlentyHealing::disable() {
    listeners::unRegisterListeners();
    for (auto &pair : *tasksMap) {
        pair.second->cancel();
    }
    tasksMap.reset();
    scheduler.reset();

    return true;
}

tasks_map &PlentyHealing::getTasksMap() { return tasksMap.value(); }

ll::schedule::GameTickScheduler &PlentyHealing::getScheduler() { return scheduler.value(); }

} // namespace plenty_healing

LL_REGISTER_MOD(plenty_healing::PlentyHealing, plenty_healing::instance);

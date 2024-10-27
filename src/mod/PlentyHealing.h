#pragma once

#include "Task.h"
#include "ll/api/mod/NativeMod.h"
#include "ll/api/schedule/Scheduler.h"
#include "mc/deps/core/mce/UUID.h"

#include <unordered_map>

namespace plenty_healing {

class PlentyHealing {
    using tasks_map = std::unordered_map<mce::UUID, std::shared_ptr<Task>>;

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

    tasks_map &getTasksMap();

    ll::schedule::GameTickScheduler &getScheduler();

private:
    ll::mod::NativeMod &mSelf;

    std::optional<ll::schedule::GameTickScheduler> scheduler;

    std::optional<tasks_map> tasksMap;
};

} // namespace plenty_healing

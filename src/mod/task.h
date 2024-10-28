#pragma once

#include "ll/api/schedule/Scheduler.h"
#include "mc/deps/core/mce/UUID.h"

#include <unordered_map>

namespace task {

    using t_scheduler = ll::schedule::GameTickScheduler;

    extern std::shared_ptr<ll::schedule::task::Task<ll::chrono::GameTickClock>> thisTask;

    extern std::optional<ll::schedule::GameTickScheduler> scheduler;

    void registerTask();

    void unregisterTask();

    void execute();

};
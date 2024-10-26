#pragma once

#include "ll/api/schedule/Scheduler.h"
#include "mc/deps/core/mce/UUID.h"
#include <unordered_map>

class Task {
    using t_scheduler = ll::schedule::GameTickScheduler;

public:
    Task() = delete;

    Task(const Task&) = delete;

    Task(mce::UUID playerID, std::shared_ptr<t_scheduler> scheduler);

    void execute();

    void cancel();

private:
    mce::UUID playerID;

    std::shared_ptr<t_scheduler> scheduler;

    std::shared_ptr<ll::schedule::task::Task<ll::chrono::GameTickClock>> thisTask;
};
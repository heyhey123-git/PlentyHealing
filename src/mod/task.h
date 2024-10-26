#pragma once

#include "ll/api/schedule/Scheduler.h"
#include "mc/deps/core/mce/UUID.h"

#include <unordered_map>

class Task {
    using t_scheduler = ll::schedule::GameTickScheduler;

public:
    Task() = delete;

    Task(const Task &) noexcept = default;

    Task(Task &&) noexcept = default;

    Task(mce::UUID playerID);

    void execute();

    void cancel();

private:
    mce::UUID playerID;

    std::shared_ptr<ll::schedule::task::Task<ll::chrono::GameTickClock>> thisTask;
};
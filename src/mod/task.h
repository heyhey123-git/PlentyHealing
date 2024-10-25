#pragma once

#include <ll/api/schedule/Scheduler.h>
#include <mc/deps/core/mce/UUID.h>
#include <unordered_map>

class Task {
    using map = std::unordered_map<mce::UUID, std::shared_ptr<Task>>;
    using t_scheduler = ll::schedule::GameTickScheduler;

public:
    Task() = delete;

    Task(Task const&) = delete;

    Task(Task&&) = delete;

    Task(mce::UUID playerID, std::shared_ptr<map> tasks, std::shared_ptr<t_scheduler> scheduler);

    void execute();

    void cancel();

private:
    std::weak_ptr<map> tasks;

    mce::UUID playerID;

    std::shared_ptr<t_scheduler> scheduler;

    std::shared_ptr<ll::schedule::task::Task<ll::chrono::GameTickClock>> thisTask;
};
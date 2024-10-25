#include "task.h"

#include "ll/api/service/Bedrock.h"
#include "mc/world/actor/player/Player.h"

Task::Task(mce::UUID playerID, std::shared_ptr<map> tasks, std::shared_ptr<t_scheduler> scheduler)
: playerID(playerID),
  scheduler(scheduler) {
    this->thisTask = scheduler->add<ll::schedule::task::RepeatTask>(10, [this]() { this->execute(); });
    tasks->insert({playerID, std::make_shared<Task>(*this)});
    std::weak_ptr<map> weakTasksPtr = tasks;
    this->tasks                     = weakTasksPtr;
}

void Task::execute() { 
    Player* player = ll::service::getLevel()->getPlayer(this->playerID);
    player->getAttribute
}

void Task::cancel() {
    this->thisTask->cancel();
    this->scheduler->remove(this->thisTask);
    this->tasks.lock()->erase(this->playerID);
}

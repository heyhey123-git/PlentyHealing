#include "Task.h"

#include "ll/api/service/Bedrock.h"
#include "mc/world/actor/player/Player.h"
#include "mc/world/attribute/Attribute.h"
#include "mc/world/attribute/AttributeInstance.h"
#include "mc/world/level/level.h"

#include <cmath>

Task::Task(mce::UUID playerID, std::shared_ptr<t_scheduler> scheduler) : playerID(playerID), scheduler(scheduler) {
    this->thisTask = scheduler->add<ll::schedule::task::RepeatTask>(
        std::chrono::milliseconds(500), [this]() { this->execute(); }
        );
}

void Task::execute() {
    Player *player     = ll::service::getLevel()->getPlayer(this->playerID);
    auto    saturation = player->getMutableAttribute(Player::SATURATION)->getCurrentValue();
    auto    hunger     = player->getMutableAttribute(Player::HUNGER)->getCurrentValue();
    auto    health     = player->getHealth();
    auto    maxHealth  = player->getMaxHealth();
    if (hunger != 20 || saturation == 0 || health == maxHealth) return;
    player->heal(1);
    auto exhaustion = player->getMutableAttribute(Player::EXHAUSTION);
    exhaustion->setCurrentValue(exhaustion->getCurrentValue() + 6);
}

void Task::cancel() {
    this->thisTask->cancel();
    this->scheduler->remove(this->thisTask);
}

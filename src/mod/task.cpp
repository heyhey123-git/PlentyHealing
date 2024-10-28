#include "Task.h"

#include "PlentyHealing.h"
#include "ll/api/service/Bedrock.h"
#include "mc/world/actor/player/Player.h"
#include "mc/world/attribute/Attribute.h"
#include "mc/world/attribute/AttributeInstance.h"
#include "mc/world/attribute/SharedAttributes.h"
#include "mc/world/level/level.h"

#include <cmath>

namespace task {
    
    std::shared_ptr<ll::schedule::task::Task<ll::chrono::GameTickClock>> thisTask;

    std::optional<ll::schedule::GameTickScheduler> scheduler;

void execute() {
    ll::service::getLevel()->forEachPlayer([](Player &player) -> bool {
        auto saturation = player.getMutableAttribute(Player::SATURATION)->getCurrentValue();
        auto hunger     = player.getMutableAttribute(Player::HUNGER)->getCurrentValue();
        auto health     = player.getHealth();
        auto maxHealth  = player.getMaxHealth();

        if (hunger != 20 || saturation == 0 || health == maxHealth) return true;

        player.getMutableAttribute(SharedAttributes::HEALTH)->setCurrentValue(fmin(maxHealth, health + 1));
        auto exhaustion = player.getMutableAttribute(Player::EXHAUSTION);
        exhaustion->setCurrentValue(fmin(exhaustion->getCurrentValue() + 6, exhaustion->getMaxValue()));
        return true;
    });
}

void registerTask() {
    scheduler.emplace();
    thisTask = scheduler->add<ll::schedule::task::RepeatTask>(ll::chrono::ticks(10), execute);
}

void unregisterTask() {
    thisTask->cancel();
    thisTask.reset();
    scheduler.reset();
}

} // namespace task

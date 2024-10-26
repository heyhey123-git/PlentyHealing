#include "Listeners.h"

#include "PlentyHealing.h"
#include "Task.h"
#include "ll/api/event/EventBus.h"

namespace listeners {

std::shared_ptr<ListenerBase> playerJoinListenerPtr = nullptr;
std::shared_ptr<ListenerBase> playerLeftListenerPtr = nullptr;

void playerJoinListener(PlayerJoinEvent &event) {
    auto plugin    = plenty_healing::PlentyHealing::getInstance();
    auto map       = plugin.getTasksMap().lock();
    auto scheduler = plugin.getScheduler();
    auto uuid      = event.self().getUuid();
    auto task      = std::make_shared<Task>(uuid, scheduler.lock());
    map->insert({uuid, task});
}

void playerLeftListener(PlayerLeaveEvent &event) {
    auto plugin    = plenty_healing::PlentyHealing::getInstance();
    auto map       = plugin.getTasksMap().lock();
    auto scheduler = plugin.getScheduler();
    auto uuid      = event.self().getUuid();
    map->find(uuid)->second->cancel();
    map->erase(uuid);
}

void registerListeners() {
    auto &eventBus = EventBus::getInstance();

    auto joinListener =
        eventBus.emplaceListener<PlayerJoinEvent>([](PlayerJoinEvent &event) { playerJoinListener(event); });
    playerJoinListenerPtr = joinListener;
    eventBus.addListener(joinListener);

    auto leftListener =
        eventBus.emplaceListener<PlayerLeaveEvent>([](PlayerLeaveEvent &event) { playerLeftListener(event); });
    playerLeftListenerPtr = leftListener;
    eventBus.addListener(leftListener);
}

void unRegisterListeners() {
    auto &eventBus = EventBus::getInstance();

    eventBus.removeListener(playerJoinListenerPtr);
    eventBus.removeListener(playerLeftListenerPtr);

    playerJoinListenerPtr.reset();
    playerLeftListenerPtr.reset();
}
} // namespace listeners

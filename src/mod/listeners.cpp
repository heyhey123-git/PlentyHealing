#include "Listeners.h"

#include "PlentyHealing.h"
#include "Task.h"
#include "ll/api/event/EventBus.h"

namespace listeners {

std::shared_ptr<ListenerBase> playerJoinListenerPtr = nullptr;
std::shared_ptr<ListenerBase> playerLeftListenerPtr = nullptr;

void playerJoinListener(PlayerJoinEvent &event) {
    auto uuid = event.self().getUuid();
    auto map  = plenty_healing::PlentyHealing::getInstance().getTasksMap();
    map.try_emplace(uuid, std::make_shared<Task>(uuid));
}

void playerLeftListener(PlayerLeaveEvent &event) {
    auto map  = plenty_healing::PlentyHealing::getInstance().getTasksMap();
    auto uuid = event.self().getUuid();
    map.find(uuid)->second->cancel();
    map.erase(uuid);
}

void registerListeners() {
    auto &eventBus = EventBus::getInstance();

    auto joinListener =
        eventBus.emplaceListener<PlayerJoinEvent>([](PlayerJoinEvent &event) { playerJoinListener(event); });
    playerJoinListenerPtr = joinListener;

    auto leftListener =
        eventBus.emplaceListener<PlayerLeaveEvent>([](PlayerLeaveEvent &event) { playerLeftListener(event); });
    playerLeftListenerPtr = leftListener;
}

void unRegisterListeners() {
    auto &eventBus = EventBus::getInstance();
    eventBus.removeListener(playerJoinListenerPtr);
    eventBus.removeListener(playerLeftListenerPtr);
}
} // namespace listeners

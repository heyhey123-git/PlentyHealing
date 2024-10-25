#include "listeners.h"

#include "ll/api/event/EventBus.h"

void listeners::playerJoinListener(PlayerJoinEvent &event) {}

void listeners::playerLeftListener(PlayerLeaveEvent &event) {}

void listeners::registerListeners() {
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

void listeners::unRegisterListeners() {
    auto &eventBus = EventBus::getInstance();

    eventBus.removeListener(playerJoinListenerPtr);
    eventBus.removeListener(playerLeftListenerPtr);

    playerJoinListenerPtr = nullptr;
    playerLeftListenerPtr = nullptr;
}
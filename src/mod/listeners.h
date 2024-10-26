#pragma once

#include "ll/api/event/ListenerBase.h"
#include "ll/api/event/player/PlayerJoinEvent.h"
#include "ll/api/event/player/PlayerLeaveEvent.h"

#include <unordered_map>

namespace listeners {
using namespace ll::event;
using namespace ll::event::player;

extern std::shared_ptr<ListenerBase> playerJoinListenerPtr;
extern std::shared_ptr<ListenerBase> playerLeftListenerPtr;

void playerJoinListener(PlayerJoinEvent &event);

void playerLeftListener(PlayerLeaveEvent &event);

void registerListeners();

void unRegisterListeners();
} // namespace listeners
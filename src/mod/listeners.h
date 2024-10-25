#include "ll/api/event/player/PlayerJoinEvent.h"
#include "ll/api/event/player/PlayerLeaveEvent.h"

namespace listeners {
using namespace ll::event;
using namespace ll::event::player;

ListenerPtr playerJoinListenerPtr;
ListenerPtr playerLeftListenerPtr;

void playerJoinListener(PlayerJoinEvent &event);

void playerLeftListener(PlayerLeaveEvent &event);

void registerListeners();

void unRegisterListeners();
} // namespace listeners
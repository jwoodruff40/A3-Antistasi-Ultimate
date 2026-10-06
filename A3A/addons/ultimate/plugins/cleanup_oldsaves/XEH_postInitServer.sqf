#include "script_component.hpp"

INFO("Hooking cleanup old saves handler into CBA server game saved event.");

[CBA_EVENT_SERVER_GAME_SAVED, { call FUNC(onEventServerGameSaved) }] call FUNCMAIN(addEventHandler);

nil;

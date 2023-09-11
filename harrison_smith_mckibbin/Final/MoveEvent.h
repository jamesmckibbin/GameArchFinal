#pragma once

#include "Event.h"

enum MoveEventType
{
	PLAYER_MOVE_LEFT = NUM_GAME_EVENTS,
	PLAYER_MOVE_RIGHT,
	PLAYER_MOVE_UP,
	PLAYER_MOVE_DOWN,
	PLAYER_ATTACK,
	PLAYER_SPECIAL,
	NUM_MOVE_EVENTS
};

class MoveEvent : public Event
{
public:
	MoveEvent(MoveEventType type) : Event(static_cast<EventType>(type)) {}
	~MoveEvent() {}
};
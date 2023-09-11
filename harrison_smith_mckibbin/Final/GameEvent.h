#pragma once

#include "Event.h"
#include "Vector2D.h"

enum GameEventType
{
	ADD_ORB = NUM_INTERFACE_EVENTS,
	DESTROY_UNITS,
	UNPAUSE_START_RESTART_GAME,
	RETURN_MAIN_MENU,
	CHARACTER_SELECT,
	WARRIOR_SELECT,
	BANDIT_SELECT,
	WIZARD_SELECT,
	OPTIONS,
	LANGUAGE,
	PAUSE_GAME,
	QUIT_GAME,
	LOAD_SAVE,
	DIFFICULTY,
	DIFFICULTY_ONE,
	DIFFICULTY_TWO,
	DIFFICULTY_THREE,
	TOGGLE_MUSIC,
	NUM_GAME_EVENTS
};

class GameEvent : public Event
{
public:
	GameEvent(GameEventType type) : Event(static_cast<EventType>(type)) {}
	GameEvent(GameEventType type, const Vector2D& pos) : Event(static_cast<EventType>(type)), mPos(pos) {}
	~GameEvent() {}

	Vector2D getPos() const { return mPos; }
private:
	Vector2D mPos = Vector2D(0, 0);
};

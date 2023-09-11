#pragma once

#include "Event.h"
#include "MoveEvent.h"

enum MenuEventType
{
	UP = NUM_MOVE_EVENTS,
	DOWN,
	SELECT,
	BACK
};

class MenuEvent : public Event
{
public:
	MenuEvent(MenuEventType type, string menu) : Event(static_cast<EventType>(type)), mMenu(menu) {}
	~MenuEvent() {}

	string getMenu() const { return mMenu; }
private:
	// SET THIS TO "" FOR EVERYTHING BUT SELECT
	string mMenu;
};

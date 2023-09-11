#pragma once

#include "Event.h"
#include "EventSystem.h"
#include "Vector2D.h"
#include "InputSystem.h"

enum Keys;
enum MouseButtons;

enum InterfaceEventType
{
	KEY_PRESSED = NUM_BASE_EVENT_TYPES,
	MOUSE_BUTTON_PRESSED,
	NUM_INTERFACE_EVENTS
};

class InterfaceEvent : public Event
{
public:
	InterfaceEvent(InterfaceEventType type, const Keys key) : Event(EventType(type)), mKey(key) {}
	InterfaceEvent(InterfaceEventType type, const MouseButtons button, const Vector2D& pos) : Event(EventType(type)), mMouseButton(button), mPos(pos) {}
	~InterfaceEvent() {}

	Keys getKey() const { return mKey; };
	MouseButtons getMouseButton() const { return mMouseButton; }
	Vector2D getPos() const { return mPos; }
private:
	Keys mKey = static_cast<Keys>(NULL);
	MouseButtons mMouseButton = static_cast<MouseButtons>(NULL);
	Vector2D mPos = Vector2D(0, 0);
};
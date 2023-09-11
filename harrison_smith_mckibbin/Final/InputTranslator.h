#pragma once

#include "EventSystem.h"
#include "EventListener.h"
#include "InterfaceEvent.h"
#include "GameEvent.h"
#include "MoveEvent.h"

class InputTranslator : public EventListener
{
public:
	InputTranslator() {}
	~InputTranslator() {
		cleanup();
	}

	void init();
	void cleanup();

	void handleEvent(const Event& event);
};
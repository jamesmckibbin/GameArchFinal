#include "InputTranslator.h"

void InputTranslator::init()
{
	EventSystem::getInstance()->addListener((EventType)KEY_PRESSED, this);
	EventSystem::getInstance()->addListener((EventType)MOUSE_BUTTON_PRESSED, this);
}

void InputTranslator::cleanup()
{
	EventSystem::getInstance()->removeListener((EventType)KEY_PRESSED, this);
	EventSystem::getInstance()->removeListener((EventType)MOUSE_BUTTON_PRESSED, this);
}

void InputTranslator::handleEvent(const Event& event)
{
	const InterfaceEvent& inputEvent = static_cast<const InterfaceEvent&>(event);

	if (event.getType() == KEY_PRESSED)
	{
		if (inputEvent.getKey() == C_KEY)
		{
			EventSystem::getInstance()->fireEvent(GameEvent(PAUSE_GAME));
		}
		else if (inputEvent.getKey() == SPACE_KEY)
		{
			EventSystem::getInstance()->fireEvent(GameEvent(UNPAUSE_START_RESTART_GAME));
		}
		else if (inputEvent.getKey() == LEFT_ARROW_KEY)
		{
			EventSystem::getInstance()->fireEvent(MoveEvent(PLAYER_MOVE_LEFT));
		}
		else if (inputEvent.getKey() == RIGHT_ARROW_KEY)
		{
			EventSystem::getInstance()->fireEvent(MoveEvent(PLAYER_MOVE_RIGHT));
		}
		else if (inputEvent.getKey() == UP_ARROW_KEY)
		{
			EventSystem::getInstance()->fireEvent(MoveEvent(PLAYER_MOVE_UP));
		}
		else if (inputEvent.getKey() == DOWN_ARROW_KEY)
		{
			EventSystem::getInstance()->fireEvent(MoveEvent(PLAYER_MOVE_DOWN));
		}
		else if (inputEvent.getKey() == Z_KEY)
		{
			EventSystem::getInstance()->fireEvent(MoveEvent(PLAYER_ATTACK));
		}
		else if (inputEvent.getKey() == X_KEY)
		{
			EventSystem::getInstance()->fireEvent(MoveEvent(PLAYER_SPECIAL));
		}
	}
}
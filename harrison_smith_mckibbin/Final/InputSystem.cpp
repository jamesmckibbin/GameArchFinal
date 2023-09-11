#include "InputSystem.h"

void InputSystem::initInput()
{
	al_install_keyboard();
	al_install_mouse();

	mQueue = al_create_event_queue();
	al_register_event_source(mQueue, al_get_mouse_event_source());
	al_register_event_source(mQueue, al_get_keyboard_event_source());
}

void InputSystem::cleanupInput()
{
	al_uninstall_keyboard();
	al_uninstall_mouse();
}

bool InputSystem::getKeyState(Keys key)
{
	al_get_keyboard_state(&mKeyState);
	return al_key_down(&mKeyState, key);
}

void InputSystem::update()
{
	ALLEGRO_EVENT event;

	while (!al_is_event_queue_empty(mQueue))
	{
		al_get_next_event(mQueue, &event);

		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			EventSystem::getInstance()->fireEvent(InterfaceEvent(MOUSE_BUTTON_PRESSED, (MouseButtons)event.mouse.button, Vector2D(event.mouse.x, event.mouse.y)));
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			EventSystem::getInstance()->fireEvent(InterfaceEvent(KEY_PRESSED, (Keys)event.keyboard.keycode));
		}
	}
}
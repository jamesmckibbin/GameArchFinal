#pragma once
#include <allegro5/allegro.h>
#include "Trackable.h"
#include "InterfaceEvent.h"

enum Keys
{
	NULL_KEY = -1,
	SPACE_KEY = ALLEGRO_KEY_SPACE,
	ESC_KEY = ALLEGRO_KEY_ESCAPE,
	ENTER_KEY = ALLEGRO_KEY_ENTER,
	Z_KEY = ALLEGRO_KEY_Z,
	X_KEY = ALLEGRO_KEY_X,
	C_KEY = ALLEGRO_KEY_C,
	LEFT_ARROW_KEY = ALLEGRO_KEY_LEFT,
	RIGHT_ARROW_KEY = ALLEGRO_KEY_RIGHT,
	UP_ARROW_KEY = ALLEGRO_KEY_UP,
	DOWN_ARROW_KEY = ALLEGRO_KEY_DOWN
};

enum MouseButtons
{
	NULL_MOUSE = -1,
	MOUSE_LEFT = 1,
	MOUSE_RIGHT = 2
};

class InputSystem : public Trackable
{
public:
	InputSystem() {}
	~InputSystem() { 
		cleanupInput(); 
	}

	void initInput();
	void cleanupInput();

	bool getKeyState(Keys key);
	void update();

private:
	ALLEGRO_EVENT_QUEUE* mQueue = nullptr;

	ALLEGRO_KEYBOARD_STATE mKeyState;
};

#include <iostream>
#include <MemoryTracker.h>

#include "Game.h"
#include "GameData.h"

using namespace std;

int main()
{
	srand((unsigned)time(NULL));

	EventSystem::initInstance();
	EventSystem::getInstance()->init();
	Game::initInstance();
	Game* game = Game::getInstance();

	game->initGame(SCREEN_WIDTH, SCREEN_HEIGHT);
	game->doLoop();

	Game::deleteInstance();
	EventSystem::getInstance()->cleanupInstance();

	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");

	return 0;
}
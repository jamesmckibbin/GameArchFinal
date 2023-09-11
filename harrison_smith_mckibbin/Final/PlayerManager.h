#pragma once
#include "Player.h"
#include "Game.h"

class PlayerManager : public Trackable
{
public:
	PlayerManager() {}
	~PlayerManager() {
		cleanup();
	}
	void init();
	void cleanup();

	void createPlayer(const Vector2D& pos, const int& character);
	void deleteUnit();
	void clearUnits();
	void updateUnits(float deltaTime);
	void drawUnits();
	void pauseUnits();
	void unPauseUnits();
	void changeUnitAnim(const Vector2D& pos);

	Player* getUnit() { return mPlayer; }

	bool unitExists();
	bool mouseOnUnit(const Vector2D& mousePos, unsigned int index);
	bool playerOffScreen(int index);

private:
	Player* mPlayer = nullptr;

	Vector2D mPlayerHitbox = Vector2D(48, 48);

	bool mShouldAnimate = true;
};
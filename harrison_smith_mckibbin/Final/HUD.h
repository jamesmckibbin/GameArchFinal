#pragma once

#include "Game.h"

class HUD : public Trackable
{
public:
	HUD() {}
	~HUD() {
		cleanup();
	}

	void init();
	void cleanup();

	void updateHUD();
	void drawHUD();

	void setLastFrameTime(double time);

private:
	Font* mHUDFont = nullptr;
	Font* mCharFont = nullptr;
	Color mTextColor = Color(200, 255, 255, 255);

	string mFPS;
	string mWave;
	string mTime;
	string mInvincibilityTimer;

	float mLastFrameTime = 0.0f;
};
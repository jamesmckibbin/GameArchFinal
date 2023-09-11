#include "HUD.h"

#include "PlayerManager.h"

void HUD::init()
{
	// Create fonts
	mHUDFont = new Font(ART_ASSET_PATH + "menu.ttf", 30);
	mCharFont = new Font(ART_ASSET_PATH + "menu.ttf", 24);
}

void HUD::cleanup()
{
	// Delete fonts
	delete mHUDFont;
	mHUDFont = nullptr;
	delete mCharFont;
	mCharFont = nullptr;
}

void HUD::updateHUD()
{
	// Update Score
	mWave = "Wave: " + std::to_string(Game::getInstance()->getWave());

	// Update FPS
	mFPS = std::to_string(1000 / mLastFrameTime) + " FPS";

	// Update Time
	mTime = "Time: " + std::to_string(Game::getInstance()->getInGameTime());

	// Update Invincible Time
	mInvincibilityTimer = std::to_string(Game::getInstance()->getPlayerManager()->getUnit()->getInvincibleTime() / 1000);
}

void HUD::drawHUD()
{
	// Draw Score
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), Vector2D(10, 10), mHUDFont,
		mTextColor, mWave);

	// Draw FPS
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), Vector2D(550, 10), mHUDFont,
		mTextColor, mFPS);

	// Draw Time
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), Vector2D(550, 40), mHUDFont,
		mTextColor, mTime);

	if (Game::getInstance()->getPlayerManager()->getUnit()->getCharacter() == 1 &&
		Game::getInstance()->getPlayerManager()->getUnit()->isInvincible())
	{
		// Draw Invincibility Timer
		Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(),
			Vector2D(Game::getInstance()->getPlayerManager()->getUnit()->getPosition().getX() - 30.0f,
				Game::getInstance()->getPlayerManager()->getUnit()->getPosition().getY() - 20.0f), mCharFont,
			mTextColor, mInvincibilityTimer);
	}
}

void HUD::setLastFrameTime(const double time)
{
	// Set the frame time to get FPS
	mLastFrameTime = time;
}
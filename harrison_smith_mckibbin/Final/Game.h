#pragma once
#include "GraphicsSystem.h"
#include "GraphicsBufferManager.h"
#include "GameData.h"
#include "Sprite.h"
#include "InputSystem.h"
#include "InputTranslator.h"
#include "EnemyManager.h"
#include "HUD.h"
#include "Menu.h"
#include "AudioManager.h"
#include "AnimationManager.h"
#include "AutoSave.h"
#include "Timer.h"
#include "EventListener.h"

class HUD;
class Menu;
class PlayerManager;
class GraphicsBufferManager;
class AudioManager;
class AnimationManager;

class Game : public EventListener
{
public:

	Game() {}
	~Game() {
		cleanupGame();
	}

	void initGame(int displayWidth, int displayHeight);
	void cleanupGame();

	void doLoop();
	void changeWave(int num);
	void checkArrowKeys();
	void updateEnemies(Vector2D target);
	void updateMeter();
	void setDifficulty(int difficulty);

	GraphicsSystem* getGraphics() const { return mGraphics; }
	InputSystem* getInput() const { return mInput; }
	GraphicsBufferManager* getGraphicsBufferManager() const { return mGraphicsBufferManager; }
	AudioManager* getAudioManager() const { return mAudioManager; }
	AnimationManager* getAnimationManager() const { return mAnimationManager; }
	PlayerManager* getPlayerManager() const { return mPlayerManager; }

	int getWave() const { return mWave; }
	double getInGameTime() const { return mInGameTime; }
	float getCurrentDifficulty() const { return mGameDifficulty; }

	void checkDamage();

	static Game* getInstance() { return mGame; }
	static void initInstance();
	static void deleteInstance();

	void handleEvent(const Event& event);

	// Game State Booleans
	bool mGameLooping = true;
	bool mGameStarted = false;
	bool mInCharSelect = false;
	bool mInOptions = false;
	bool mInLanguage = false;
	bool mInDifficulty = false;
	bool mGamePaused = false;
	bool mGameOver = false;
	bool mMusicPlaying = true;

private:
	int mWave = 1;
	int mWaveEnemyCount = 5;
	int mEnemySpawnCounter = 0;
	int mEnemySpawnRate = 60;
	int mMaxEnemySpawnRate = 60;
	double mInGameTime = 0.0;
	float mFrameTime = 1000 / FRAME_RATE;
	float mGameDifficulty = 1.0f;
	int mAttackCooldown = 0;
	int mMeterFill = 0;
	int mMeterMax = 800;
	int mHealth = 1;
	int mHealthMax = 1;
	Vector2D mFacingDirection = Vector2D(1, 0);

	void selectWarrior();
	void selectWizard();
	void selectBandit();

	Timer mTimer;

	GraphicsSystem* mGraphics = nullptr;
	InputSystem* mInput = nullptr;
	InputTranslator* mInputTranslator = nullptr;

	PlayerManager* mPlayerManager = nullptr;
	EnemyManager* mEnemyManager = nullptr;
	GraphicsBufferManager* mGraphicsBufferManager = nullptr;
	AudioManager* mAudioManager = nullptr;
	AnimationManager* mAnimationManager = nullptr;

	Sprite* mBackgroundSprite = nullptr;
	Sprite* mTitleBackgroundSprite = nullptr;
	Sprite* mHealthSprite = nullptr;
	Sprite* mMeterSprite = nullptr;
	Sprite* mProjectileSprite = nullptr;
	Sprite* mTextBackgroundSprite = nullptr;

	AutoSave* mAutoSave = nullptr;
	FileData* mSaveData = nullptr;
	FileData* mSettingsData = nullptr;
	 
	HUD* mHUD = nullptr;
	Menu* mMenu = nullptr;

	static Game* mGame;
};

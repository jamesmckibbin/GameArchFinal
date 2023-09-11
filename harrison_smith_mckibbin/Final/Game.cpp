#include "Game.h"
#include "PlayerManager.h"
#include "MenuEvent.h"

Game* Game::mGame = NULL;

void Game::initGame(const int displayWidth, const int displayHeight)
{
	// Initializing GraphicsSystem, InputSystem, and InputTranslator
	mGraphics = new GraphicsSystem(displayWidth, displayHeight);
	mInput = new InputSystem();
	mInputTranslator = new InputTranslator();

	mGraphics->initDisplay();
	mInput->initInput();
	mInputTranslator->init();

	// Initializing GBManager, AnimationManager, and AudioManager
	mGraphicsBufferManager = new GraphicsBufferManager();
	mAudioManager = new AudioManager(2); // Change number to reflect # of sounds in-game
	mAnimationManager = new AnimationManager();

	// General Buffers
	mGraphicsBufferManager->createBuffer("TitleBackground", ART_ASSET_PATH + START_BACKGROUND_FILENAME);
	mGraphicsBufferManager->createBuffer("Background", ART_ASSET_PATH + BACKGROUND_FILENAME);
	mGraphicsBufferManager->createBuffer("Health", 800, 20, Color(255, 0, 0, 255));
	mGraphicsBufferManager->createBuffer("Meter", 800, 20, Color(0, 0, 255, 255));
	mGraphicsBufferManager->createBuffer("PauseBackground", 800, 600, Color(10, 10, 10, 100));

	// Player Buffers
	mGraphicsBufferManager->createBuffer("Bandit", ART_ASSET_PATH + BANDIT_ANIM_FILENAME);
	mGraphicsBufferManager->createBuffer("Wizard", ART_ASSET_PATH + WIZARD_ANIM_FILENAME);
	mGraphicsBufferManager->createBuffer("Warrior", ART_ASSET_PATH + WARRIOR_ANIM_FILENAME);
	mGraphicsBufferManager->createBuffer("Projectile", ART_ASSET_PATH + PROJECTILE_FILENAME);
	mGraphicsBufferManager->createBuffer("WarriorSpecial", ART_ASSET_PATH + WARRIOR_SECOND_ATTACK_FILENAME);
	// Enemy Buffers
	mGraphicsBufferManager->createBuffer("Enemy", ART_ASSET_PATH + ENEMY_FILENAME);

	// Audio
	mAudioManager->createAudioClip("MainMenuMusic", SOUND_ASSET_PATH + MAIN_MENU_MUSIC);
	mAudioManager->createAudioClip("LevelMusic", SOUND_ASSET_PATH + LEVEL_MUSIC);
	mAudioManager->createAudioClip("WarriorAttack", SOUND_ASSET_PATH + WARRIOR_ATTACK);
	mAudioManager->createAudioClip("WarriorHurt", SOUND_ASSET_PATH + WARRIOR_HURT);
	mAudioManager->createAudioClip("WarriorSpecial", SOUND_ASSET_PATH + WARRIOR_SPECIAL);
	mAudioManager->createAudioClip("BanditAttack", SOUND_ASSET_PATH + BANDIT_ATTACK);
	mAudioManager->createAudioClip("BanditHurt", SOUND_ASSET_PATH + BANDIT_HURT);
	mAudioManager->createAudioClip("BanditSpecial", SOUND_ASSET_PATH + BANDIT_SPECIAL);
	mAudioManager->createAudioClip("WizardAttack", SOUND_ASSET_PATH + WIZARD_ATTACK);
	mAudioManager->createAudioClip("WizardHurt", SOUND_ASSET_PATH + WIZARD_HURT);
	mAudioManager->createAudioClip("WizardSpecial", SOUND_ASSET_PATH + WIZARD_SPECIAL);

	// AnimationData
	mAnimationManager->createAnimationData("BanditSpecial", mGraphicsBufferManager->getBuffer("Bandit"), 2, Vector2D(48, 48), Vector2D(0, 48));
	mAnimationManager->createAnimationData("Bandit", mGraphicsBufferManager->getBuffer("Bandit"), 2, Vector2D(48, 48), Vector2D(0, 0));
	mAnimationManager->createAnimationData("WarriorSpecial", mGraphicsBufferManager->getBuffer("WarriorSpecial"), 1, Vector2D(96, 96), Vector2D(0, 0));
	mAnimationManager->createAnimationData("Warrior", mGraphicsBufferManager->getBuffer("Warrior"), 2, Vector2D(48, 48),Vector2D(0, 0));
	mAnimationManager->createAnimationData("Wizard", mGraphicsBufferManager->getBuffer("Wizard"), 2, Vector2D(48, 48), Vector2D(0, 0));
	mAnimationManager->createAnimationData("Enemy", mGraphicsBufferManager->getBuffer("Enemy"), 2, Vector2D(32, 32), Vector2D(0, 0));

	// Creating event listeners
	EventSystem::getInstance()->addListener(static_cast<EventType>(PAUSE_GAME), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(QUIT_GAME), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(RETURN_MAIN_MENU), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(OPTIONS), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(LANGUAGE), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(LOAD_SAVE), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(UNPAUSE_START_RESTART_GAME), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(PLAYER_MOVE_LEFT), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(PLAYER_MOVE_RIGHT), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(PLAYER_MOVE_UP), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(PLAYER_MOVE_DOWN), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(PLAYER_ATTACK), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(PLAYER_SPECIAL), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(CHARACTER_SELECT), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(WARRIOR_SELECT), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(BANDIT_SELECT), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(WIZARD_SELECT), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(DIFFICULTY), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(DIFFICULTY_ONE), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(DIFFICULTY_TWO), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(DIFFICULTY_THREE), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(TOGGLE_MUSIC), this);
	
	// Setting up backgrounds
	mBackgroundSprite = new Sprite(mGraphicsBufferManager->getBuffer("Background"), Vector2D(0, 0),
		mGraphicsBufferManager->getBuffer("Background")->getWidth(), mGraphicsBufferManager->getBuffer("Background")->getHeight());
	mTitleBackgroundSprite = new Sprite(mGraphicsBufferManager->getBuffer("TitleBackground"), Vector2D(0, 0), 
		mGraphicsBufferManager->getBuffer("TitleBackground")->getWidth(), mGraphicsBufferManager->getBuffer("TitleBackground")->getHeight());
	mTextBackgroundSprite = new Sprite(mGraphicsBufferManager->getBuffer("PauseBackground"), Vector2D(0, 0),
		mGraphicsBufferManager->getBuffer("PauseBackground")->getWidth(), mGraphicsBufferManager->getBuffer("PauseBackground")->getHeight());

	// Meter sprites
	mHealthSprite = new Sprite(mGraphicsBufferManager->getBuffer("Health"), Vector2D(0, 0),
		mGraphicsBufferManager->getBuffer("Health")->getWidth(), mGraphicsBufferManager->getBuffer("Health")->getHeight());
	mMeterSprite = new Sprite(mGraphicsBufferManager->getBuffer("Meter"), Vector2D(0, 0),
		mGraphicsBufferManager->getBuffer("Meter")->getWidth(), mGraphicsBufferManager->getBuffer("Meter")->getHeight());

	// Projectile sprite
	mProjectileSprite = new Sprite(mGraphicsBufferManager->getBuffer("Projectile"), Vector2D(0, 0),
		mGraphicsBufferManager->getBuffer("Projectile")->getWidth(), mGraphicsBufferManager->getBuffer("Projectile")->getHeight());

	// Initializing PlayerManager
	mPlayerManager = new PlayerManager(); 
	mPlayerManager->init();
	mPlayerManager->createPlayer(Vector2D(400, 300), 0);

	// Initializing EnemyManager
	mEnemyManager = new EnemyManager();
	mEnemyManager->init();

	//Initializing AutoSave
	mAutoSave = new AutoSave();

	//Initializing FileData
	mSaveData = new FileData();
	mSettingsData = new FileData();
	mSettingsData->loadData(DATA_ASSET_PATH + SETTINGS_FILENAME);

	// Initializing HUD and Menu
	mHUD = new HUD();
	mMenu = new Menu();
	mHUD->init();
	mMenu->init();
}

void Game::cleanupGame()
{
	// Cleaning up event listeners
	EventSystem::getInstance()->removeListener(static_cast<EventType>(PAUSE_GAME), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(QUIT_GAME), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(RETURN_MAIN_MENU), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(OPTIONS), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(LANGUAGE), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(UNPAUSE_START_RESTART_GAME), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(PLAYER_MOVE_LEFT), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(PLAYER_MOVE_RIGHT), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(PLAYER_MOVE_UP), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(PLAYER_MOVE_DOWN), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(PLAYER_ATTACK), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(CHARACTER_SELECT), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(WARRIOR_SELECT), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(BANDIT_SELECT), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(WIZARD_SELECT), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(DIFFICULTY), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(DIFFICULTY_ONE), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(DIFFICULTY_TWO), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(DIFFICULTY_THREE), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(TOGGLE_MUSIC), this);

	// Deleting AutoSave
	delete mAutoSave;
	mAutoSave = nullptr;

	//Delete FileData
	delete mSaveData;
	mSaveData = nullptr;
	delete mSettingsData;
	mSettingsData = nullptr;

	// Deleting background sprite
	delete mBackgroundSprite;
	mBackgroundSprite = nullptr;
	delete mTitleBackgroundSprite;
	mTitleBackgroundSprite = nullptr;
	delete mTextBackgroundSprite;
	mTextBackgroundSprite = nullptr;
	
	// Deleting meter sprites
	delete mHealthSprite;
	mHealthSprite = nullptr;
	delete mMeterSprite;
	mMeterSprite = nullptr;

	// Deleting projectile sprite
	delete mProjectileSprite;
	mProjectileSprite = nullptr;

	// Deleting managers
	delete mAudioManager;
	mAudioManager = nullptr;
	delete mGraphicsBufferManager;
	mGraphicsBufferManager = nullptr;
	delete mPlayerManager;
	mPlayerManager = nullptr;
	delete mEnemyManager;
	mEnemyManager = nullptr;
	delete mAnimationManager;
	mAnimationManager = nullptr;

	// Deleting systems
	delete mGraphics;
	mGraphics = nullptr;
	delete mInputTranslator;
	mInputTranslator = nullptr;
	delete mInput;
	mInput = nullptr;

	// Deleting HUD
	delete mHUD;
	mHUD = nullptr;
	delete mMenu;
	mMenu = nullptr;
}

void Game::checkArrowKeys()
{
	if (!mInput->getKeyState(UP_ARROW_KEY) && !mInput->getKeyState(DOWN_ARROW_KEY))
	{
		mPlayerManager->getUnit()->setVelocityY(0);
	}
	if (!mInput->getKeyState(LEFT_ARROW_KEY) && !mInput->getKeyState(RIGHT_ARROW_KEY))
	{
		mPlayerManager->getUnit()->setVelocityX(0);
	}
}

void Game::changeWave(const int num)
{
	mWave = num;
}

void Game::updateEnemies(Vector2D target)
{
	mEnemyManager->updateVelocity(target);
	mEnemyManager->updateUnits(mFrameTime);
}

void Game::updateMeter()
{
	if (mMeterFill < mMeterMax)
	{
		mMeterFill++;
	}
}

void Game::checkDamage()
{
	if (mEnemyManager->checkAtLocation(mPlayerManager->getUnit()->getPosition(), 10))
	{
		if (!mPlayerManager->getUnit()->isInvincible())
		{
			mHealth--;

			switch (mPlayerManager->getUnit()->getCharacter())
			{
			case 0:
				mAudioManager->playSound("WarriorHurt", false);
				break;
			case 1:
				mAudioManager->playSound("BanditHurt", false);
				break;
			case 2:
				mAudioManager->playSound("WizardHurt", false);
				break;
			}
		}
		mEnemyManager->deleteAtLocation(mPlayerManager->getUnit()->getPosition(), 10);
	}
}

void Game::setDifficulty(int difficulty)
{
	switch (difficulty)
	{
	case 1: mGameDifficulty = mSettingsData->getFloatData("MultiplierEasy");
		break;
	case 2: mGameDifficulty = mSettingsData->getFloatData("MultiplierNorm");
		break;
	case 3: mGameDifficulty = mSettingsData->getFloatData("MultiplierHard");
		break;
	}
}

// Game Loop
void Game::doLoop()
{
	while (mGameLooping)
	{
		if (mMusicPlaying)
		{
			mAudioManager->stopSound("LevelMusic");
			mAudioManager->playSound("MainMenuMusic", true);
		}
		// Main Menu loop
		while (!mGameStarted && mGameLooping)
		{
			if (mInCharSelect)
			{
				mTimer.start();

				mInput->update();

				mGraphics->draw(mGraphics->getBackBuffer(), Vector2D(0, 0), *mTitleBackgroundSprite);
				mGraphics->draw(mGraphics->getBackBuffer(), Vector2D(0, 0), *mTextBackgroundSprite);
				mMenu->updateCharacterMenu();
				mMenu->drawCharacterMenu();

				mGraphics->flip();

				mTimer.sleepUntilElapsed(mFrameTime);
				continue;
			}
			if (mInOptions)
			{
				mTimer.start();

				mInput->update();

				mGraphics->draw(mGraphics->getBackBuffer(), Vector2D(0, 0), *mTitleBackgroundSprite);
				mGraphics->draw(mGraphics->getBackBuffer(), Vector2D(0, 0), *mTextBackgroundSprite);
				mMenu->updateOptionsMenu();
				mMenu->drawOptionsMenu();

				mGraphics->flip();

				mTimer.sleepUntilElapsed(mFrameTime);
				continue;
			}
			if (mInLanguage)
			{
				mTimer.start();

				mInput->update();

				mGraphics->draw(mGraphics->getBackBuffer(), Vector2D(0, 0), *mTitleBackgroundSprite);
				mGraphics->draw(mGraphics->getBackBuffer(), Vector2D(0, 0), *mTextBackgroundSprite);
				mMenu->updateLanguageMenu();
				mMenu->drawLanguageMenu();

				mGraphics->flip();

				mTimer.sleepUntilElapsed(mFrameTime);
				continue;
			}
			if (mInDifficulty)
			{
				mTimer.start();

				mInput->update();

				mGraphics->draw(mGraphics->getBackBuffer(), Vector2D(0, 0), *mTitleBackgroundSprite);
				mGraphics->draw(mGraphics->getBackBuffer(), Vector2D(0, 0), *mTextBackgroundSprite);
				mMenu->updateDifficultyMenu();
				mMenu->drawDifficultyMenu();

				mGraphics->flip();

				mTimer.sleepUntilElapsed(mFrameTime);
				continue;
			}
			mTimer.start();

			mInput->update();

			mGraphics->draw(mGraphics->getBackBuffer(), Vector2D(0, 0), *mTitleBackgroundSprite);
			mGraphics->draw(mGraphics->getBackBuffer(), Vector2D(0, 0), *mTextBackgroundSprite);
			mMenu->updateMainMenu();
			mMenu->drawMainMenu();

			mGraphics->flip();

			mTimer.sleepUntilElapsed(mFrameTime);
		}

		if (mMusicPlaying)
		{
			mAudioManager->stopSound("MainMenuMusic");
			mAudioManager->playSound("LevelMusic", true);
		}

		while (mGameStarted && mGameLooping)
		{
			// Game Paused loop
			if (mGamePaused)
			{
				mTimer.start();

				mInput->update();

				mGraphics->draw(mGraphics->getBackBuffer(), Vector2D(0, 0), *mBackgroundSprite);
				mPlayerManager->drawUnits();
				mEnemyManager->drawUnits();
				mGraphics->draw(mGraphics->getBackBuffer(), Vector2D(0, 0), *mTextBackgroundSprite);
				mMenu->updatePauseScreen();
				mMenu->drawPauseScreen();

				mGraphics->flip();

				mTimer.sleepUntilElapsed(mFrameTime);
				mHUD->setLastFrameTime(mTimer.getElapsedTime());
				continue;
			}
			if (mHealth <= 0)
			{
				mHealth = mHealthMax;
				mGameOver = true;
				mMenu->setSelected(0);
			}
			if (mGameOver)
			{
				mTimer.start();

				mInput->update();

				mGraphics->draw(mGraphics->getBackBuffer(), Vector2D(0, 0), *mBackgroundSprite);
				mGraphics->draw(mGraphics->getBackBuffer(), Vector2D(0, 0), *mTextBackgroundSprite);
				mMenu->updateLossScreen();
				mMenu->drawLossScreen();

				mGraphics->flip();

				mTimer.sleepUntilElapsed(mFrameTime);
				mHUD->setLastFrameTime(mTimer.getElapsedTime());
				continue;
			}

			mTimer.start();

			mEnemySpawnRate = mMaxEnemySpawnRate / mGameDifficulty;
			//mEnemySpawnRate = 60;

			//cout << "Active Enemies: " << mEnemyManager->getActiveEnemyUnits() << endl;
			if (mEnemySpawnCounter < mWaveEnemyCount)
			{
				if (1 + (rand() % mEnemySpawnRate) == 1)
				{
					Vector2D location = mEnemyManager->randomSpawnLocation();
					mEnemyManager->createUnit(location);
					mEnemySpawnCounter++;
					cout << "Enemy Spawn Counter: " << mEnemySpawnCounter << endl;
				}
			}
			else if (mEnemyManager->getActiveEnemyUnits() == 0 && mEnemySpawnCounter >= mWaveEnemyCount -1)
			{
				mEnemySpawnCounter = 0;
				mWave++;
				Vector2D location = mEnemyManager->randomSpawnLocation();
				mEnemyManager->createUnit(location);
				mEnemySpawnCounter++;
				cout << "Enemy Spawn Counter: " << mEnemySpawnCounter << endl;
				changeWave(mWave);
				mWaveEnemyCount += mWaveEnemyCount / 2;
				cout << "Enemy Wave count: " << mWaveEnemyCount << endl;
				
			}

			Vector2D offset = mPlayerManager->getUnit()->getVelocity() * mPlayerManager->getUnit()->getAttackReach();
			if (offset != Vector2D(0, 0))
			{
				mFacingDirection = mPlayerManager->getUnit()->getPosition() + offset;
			}
			mAttackCooldown++;

			checkArrowKeys();
			mInput->update();
			mPlayerManager->updateUnits(mFrameTime);
			updateEnemies(mPlayerManager->getUnit()->getPosition());
			checkDamage();
			updateMeter();
			mHUD->updateHUD();

			if (mPlayerManager->getUnit()->getProjectileActive())
			{
				if (mEnemyManager->checkAtLocation(mPlayerManager->getUnit()->getProjectilePos(), mPlayerManager->getUnit()->getAttackRadius()))
				{
					mEnemyManager->deleteAtLocation(mPlayerManager->getUnit()->getProjectilePos(), mPlayerManager->getUnit()->getAttackRadius());

					mPlayerManager->getUnit()->despawnProjectile();
				}
			}

			mGraphics->draw(mGraphics->getBackBuffer(), Vector2D(0, 0), *mBackgroundSprite);
			mPlayerManager->drawUnits();
			mEnemyManager->drawUnits();
			if (mPlayerManager->getUnit()->getProjectileActive())
				mGraphics->draw(mGraphics->getBackBuffer(), mPlayerManager->getUnit()->getProjectilePos(), *mProjectileSprite);
			mGraphics->draw(mGraphics->getBackBuffer(), Vector2D(mMeterFill - 800, 580), *mMeterSprite);
			mGraphics->draw(mGraphics->getBackBuffer(), Vector2D((800 * mHealth / mHealthMax) - 800, 590), *mHealthSprite);
			mHUD->drawHUD();

			mGraphics->flip();

			mTimer.sleepUntilElapsed(mFrameTime);
			mHUD->setLastFrameTime(mTimer.getElapsedTime());
			mInGameTime += mTimer.getElapsedTime() / 1000;
		}
	}
}

// Instance Functions

void Game::initInstance()
{
	if (!mGame)
	{
		mGame = new Game;
	}
}

void Game::deleteInstance()
{
	delete mGame;
}

void Game::selectWarrior()
{
	mInCharSelect = false;
	mPlayerManager->createPlayer(Vector2D(400, 300), 0);

	std::cout << "Game started" << std::endl;
	mGameStarted = true;

	mInGameTime = 0.0;
	mMeterFill = 0.0;
	mHealthMax = mPlayerManager->getUnit()->getHealthMax();
	mHealth = mHealthMax;
}

void Game::selectWizard()
{
	mInCharSelect = false;
	mPlayerManager->createPlayer(Vector2D(400, 300), 2);

	std::cout << "Game started" << std::endl;
	mGameStarted = true;

	mInGameTime = 0.0;
	mMeterFill = 0.0;
	mHealthMax = mPlayerManager->getUnit()->getHealthMax();
	mHealth = mHealthMax;
}

void Game::selectBandit()
{
	mInCharSelect = false;
	mPlayerManager->createPlayer(Vector2D(400, 300), 1);

	std::cout << "Game started" << std::endl;
	mGameStarted = true;

	mInGameTime = 0.0;
	mMeterFill = 0.0;
	mHealthMax = mPlayerManager->getUnit()->getHealthMax();
	mHealth = mHealthMax;
}

// Event Handler

void Game::handleEvent(const Event& event)
{	
	if (event.getType() == PAUSE_GAME)
	{
		if (!mGamePaused && !mGameOver && mGameStarted)
		{
			mMenu->setSelected(0);
			std::cout << "Game paused" << std::endl;
			mGamePaused = true;
		}
	}
	else if (event.getType() == QUIT_GAME)
	{
		if (mGamePaused || mGameOver || !mGameStarted)
		{
			std::cout << "Game exited" << std::endl;
			mGameStarted = false;
			mGameLooping = false;
		}
	}
	else if (event.getType() == RETURN_MAIN_MENU)
	{
		mMenu->setSelected(0);
		mInCharSelect = false;
		mInOptions = false;
		mInLanguage = false;
		mInDifficulty = false;
		mGamePaused = false;
		mGameOver = false;
		mGameStarted = false;

		mAutoSave->savePlayerLocation(mPlayerManager->getUnit()->getPosition());
		mAutoSave->saveChosenCharacter(mPlayerManager->getUnit()->getCharacter());
		mAutoSave->saveNumEnemiesOnScreen(mEnemySpawnCounter);
		mAutoSave->saveWaveNumber(mWave);

		int i;
		for (i = 0; i < mEnemySpawnCounter; i++)
		{
			mAutoSave->saveEnemyLocation(mEnemyManager->getUnit(i)->getPosition(), i);
		}

		mAutoSave->saveAllData();

		mEnemyManager->clearUnits();
	}
	else if (event.getType() == CHARACTER_SELECT)
	{
		cout << "EEK\n";

		mInCharSelect = true;
		mMenu->setSelected(0);
	}
	else if (event.getType() == WARRIOR_SELECT)
	{
		mEnemyManager->clearUnits();
		mWave = 1;
		selectWarrior();
	}
	else if (event.getType() == BANDIT_SELECT)
	{
		mEnemyManager->clearUnits();
		mWave = 1;
		selectBandit();
	}
	else if (event.getType() == WIZARD_SELECT)
	{
		mEnemyManager->clearUnits();
		mWave = 1;
		selectWizard();
	}
	else if (event.getType() == OPTIONS)
	{
		mMenu->setSelected(0);
		mInOptions = true;
	}
	else if (event.getType() == LANGUAGE)
	{
		mMenu->setSelected(0);
		mInLanguage = true;
	}
	else if (event.getType() == LOAD_SAVE)
	{
		//load in data from autosave
		mSaveData->loadData("AutoSave.txt");
		float playerX = mSaveData->getFloatData("PlayerX");
		float playerY = mSaveData->getFloatData("PlayerY");
		int chosenCharacter = mSaveData->getIntData("ChosenCharacter");
		int waveNumber = mSaveData->getIntData("WaveNumber");
		int enemyNumber = mSaveData->getIntData("NumEnemies");

		mWave = waveNumber;
		int i; 
		for (i = 0; i < mWave - 1; i++)
		{
			mWaveEnemyCount += mWaveEnemyCount / 2;
		}

		string enemyXString;
		string enemyYString;

		//respawn the enemies back in
		
		switch (chosenCharacter)
		{
		case 0: selectWarrior();
			break;
		case 1: selectBandit();
			break;
		case 2: selectWizard();
			break;
		}
		for (i = 0; i < enemyNumber - 1; i++)
		{
			enemyXString = std::to_string(i) + "EnemyX";
			enemyYString = std::to_string(i) + "EnemyY";
			float enemyX = mSaveData->getFloatData(enemyXString);
			float enemyY = mSaveData->getFloatData(enemyYString);
			mEnemyManager->createUnit(Vector2D(enemyX, enemyY));
		}
		mEnemySpawnCounter = enemyNumber;
		mPlayerManager->getUnit()->setPosition(Vector2D(playerX, playerY));

	}
	else if (event.getType() == DIFFICULTY)
	{
		mMenu->setSelected(0);
		mInDifficulty = true;
		mInOptions = false;
	}
	else if (event.getType() == DIFFICULTY_ONE)
	{
		setDifficulty(1);
		cout << "Difficulty: EASY" << endl;
	}
	else if (event.getType() == DIFFICULTY_TWO)
	{
		setDifficulty(2);
		cout << "Difficulty: NORMAL" << endl;
	}
	else if (event.getType() == DIFFICULTY_THREE)
	{
		setDifficulty(3);
		cout << "Difficulty: HARD" << endl;
	}
	else if (event.getType() == TOGGLE_MUSIC)
	{
		if (mMusicPlaying)
		{
			mMusicPlaying = false;
			mAudioManager->stopSound("MainMenuMusic");
		}
		else
		{
			mMusicPlaying = true;
			mAudioManager->playSound("MainMenuMusic", true);
		}
	}
	else if (event.getType() == UNPAUSE_START_RESTART_GAME)
	{
		if (!mGameStarted)
		{
			std::cout << "Game started" << std::endl;
			mGameStarted = true;
		}
		else if (mGamePaused)
		{
			std::cout << "Game resumed" << std::endl;
			mGamePaused = false;
		}
		else if (mGameOver)
		{
			std::cout << "Game restarted" << std::endl;
			mGameOver = false;
			mWave = 1;
			mInGameTime = 0.0;
			mMeterFill = 0.0;
			mPlayerManager->getUnit()->setPosition(Vector2D(400, 300));
			mEnemyManager->clearUnits();
		}
	}
	else if (event.getType() == DESTROY_UNITS)
	{
		GameEvent gameEvent = static_cast<const GameEvent&>(event);

		mEnemyManager->deleteAtLocation(gameEvent.getPos(), 50);
	}
	else if (event.getType() == PLAYER_MOVE_LEFT)
	{
		mPlayerManager->getUnit()->setVelocityX(-1);
	}
	else if (event.getType() == PLAYER_MOVE_RIGHT)
	{
		mPlayerManager->getUnit()->setVelocityX(1);
	}
	else if (event.getType() == PLAYER_MOVE_UP)    
	{
		if (!mGamePaused && !mGameOver && mGameStarted)
		{
			mPlayerManager->getUnit()->setVelocityY(-1);
		}
		else if (mGamePaused || mGameOver || !mGameStarted)
		{
			EventSystem::getInstance()->fireEvent(MenuEvent(UP, ""));
		}
	}
	else if (event.getType() == PLAYER_MOVE_DOWN)
	{
		if (!mGamePaused && !mGameOver && mGameStarted)
		{
			mPlayerManager->getUnit()->setVelocityY(1);
		}
		else if (mGamePaused || mGameOver || !mGameStarted)
		{
			EventSystem::getInstance()->fireEvent(MenuEvent(DOWN, ""));
		}
	}
	else if (event.getType() == PLAYER_ATTACK)
	{
		if (!mGamePaused && !mGameOver && mGameStarted)
		{
			if (mPlayerManager->getUnit()->getCharacter() != 2)
			{
				if (mAttackCooldown >= mPlayerManager->getUnit()->getAttackRate())
				{
					mEnemyManager->deleteAtLocation(mFacingDirection, mPlayerManager->getUnit()->getAttackRadius());

					mAttackCooldown = 0;

					if (mPlayerManager->getUnit()->getCharacter() == 0)
						mAudioManager->playSound("WarriorAttack", false);
					else
						mAudioManager->playSound("BanditAttack", false);
				}
			}
			else
			{
				if (!mPlayerManager->getUnit()->getProjectileActive())
				{
					mPlayerManager->getUnit()->spawnProjectile();

					mAudioManager->playSound("WizardAttack", false);
				}
			}
		}
		else if (!mGameStarted && !mInOptions && !mInLanguage && !mInCharSelect && !mInDifficulty)
		{
			EventSystem::getInstance()->fireEvent(MenuEvent(SELECT, "MainMenu"));
		}
		else if (!mGameStarted && mInOptions)
		{
			EventSystem::getInstance()->fireEvent(MenuEvent(SELECT, "Options"));
		}
		else if (!mGameStarted && mInLanguage)
		{
			EventSystem::getInstance()->fireEvent(MenuEvent(SELECT, "Language"));
		}
		else if (!mGameStarted && mInCharSelect)
		{
			EventSystem::getInstance()->fireEvent(MenuEvent(SELECT, "CharacterSelect"));
		}
		else if (!mGameStarted && mInDifficulty)
		{
			EventSystem::getInstance()->fireEvent(MenuEvent(SELECT, "Difficulty"));
		}
		else if (mGameStarted && mGameOver)
		{
			EventSystem::getInstance()->fireEvent(MenuEvent(SELECT, "GameOver"));
		}
		else if (mGameStarted && mGamePaused)
		{
			EventSystem::getInstance()->fireEvent(MenuEvent(SELECT, "Paused"));
		}

	}
	else if (event.getType() == PLAYER_SPECIAL)
	{
		if (!mGamePaused && !mGameOver && mGameStarted)
		{
			if (mMeterFill >= mMeterMax)
			{
				mMeterFill = 0;

				switch (mPlayerManager->getUnit()->getCharacter())
				{
				case 0:
					mEnemyManager->deleteAtLocation(mPlayerManager->getUnit()->getPosition(), mPlayerManager->getUnit()->getSecondAttackRadius(), true);
					mAudioManager->playSound("WarriorSpecial", false);
					break;
				case 1:
					mPlayerManager->getUnit()->banditSpecial();
					mAudioManager->playSound("BanditSpecial", false);
					break;
				case 2:
					mEnemyManager->clearUnits();
					mAudioManager->playSound("WizardSpecial", false);
					break;
				default:
					break;
				}
			}
		}
	}
}

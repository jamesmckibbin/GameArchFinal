#include "Menu.h"
#include "MenuEvent.h"

void Menu::init()
{
	// Initialize font
	mMenuFont = new Font(ART_ASSET_PATH + "menu.ttf", 30);
	mCreditsFont = new Font(ART_ASSET_PATH + "menu.ttf", 20);

	// Initialize language data
	mLanguageData = new FileData();
	mLanguageData->loadData(DATA_ASSET_PATH + ENGLISH_LANGUAGE);

	// Adding listeners
	EventSystem::getInstance()->addListener(static_cast<EventType>(UP), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(DOWN), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(SELECT), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(BACK), this);
}

void Menu::cleanup()
{
	// Removing listeners
	EventSystem::getInstance()->removeListener(static_cast<EventType>(UP), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(DOWN), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(SELECT), this);
	EventSystem::getInstance()->removeListener(static_cast<EventType>(BACK), this);

	// Delete font and language data
	delete mMenuFont;
	mMenuFont = nullptr;
	delete mCreditsFont;
	mCreditsFont = nullptr;
	delete mLanguageData;
	mLanguageData = nullptr;
}

void Menu::updateMainMenu()
{
	mNumButtons = 5;
}

void Menu::drawMainMenu()
{
	// Draw start screen text
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mTitlePos, mMenuFont,
		mTitleColor, mLanguageData->getStringData("MainMenuTitle"));
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption1Pos, mMenuFont,
		isSelected(0), mLanguageData->getStringData("Start"));
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption2Pos, mMenuFont,
		isSelected(1), mLanguageData->getStringData("Options"));
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption3Pos, mMenuFont,
		isSelected(2), mLanguageData->getStringData("Language"));
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption4Pos, mMenuFont,
		isSelected(3), mLanguageData->getStringData("Load"));
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption5Pos, mMenuFont,
		isSelected(4), mLanguageData->getStringData("Quit"));

	// Music Credits
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), Vector2D(20, 480), mMenuFont,
		mUnselectedColor, mLanguageData->getStringData("CreditsTitle"));
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), Vector2D(20, 520), mCreditsFont,
		mUnselectedColor, "Main Menu Theme: fire wizards do battle in a dominos - wednesday");
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), Vector2D(20, 560), mCreditsFont,
		mUnselectedColor, "Level Theme: platypus - kleeder");
}

void Menu::updateCharacterMenu()
{
	mNumButtons = 3;
}

void Menu::drawCharacterMenu()
{
	// Draw start screen text
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mTitlePos, mMenuFont,
		mTitleColor, mLanguageData->getStringData("CharacterTitle"));
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption1Pos, mMenuFont,
		isSelected(0), mLanguageData->getStringData("Warrior"));
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption2Pos, mMenuFont,
		isSelected(1), mLanguageData->getStringData("Bandit"));
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption3Pos, mMenuFont,
		isSelected(2), mLanguageData->getStringData("Wizard"));
}

void Menu::updateOptionsMenu()
{
	mNumButtons = 3;
}

void Menu::drawOptionsMenu()
{
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mTitlePos, mMenuFont,
		mTitleColor, mLanguageData->getStringData("OptionsTitle"));
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption1Pos, mMenuFont,
		isSelected(0), mLanguageData->getStringData("Difficulty"));
	if (Game::getInstance()->mMusicPlaying)
	{
		Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption2Pos, mMenuFont,
			isSelected(1), mLanguageData->getStringData("SoundToggle") + " On");
	}
	else
	{
		Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption2Pos, mMenuFont,
			isSelected(1), mLanguageData->getStringData("SoundToggle") + " Off");
	}
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption3Pos, mMenuFont,
		isSelected(2), mLanguageData->getStringData("ReturnToMenu")); 
}

void Menu::updateLanguageMenu()
{
	mNumButtons = 4;
}

void Menu::drawLanguageMenu()
{
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mTitlePos, mMenuFont,
		mTitleColor, mLanguageData->getStringData("LanguageTitle"));
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption1Pos, mMenuFont,
		isSelected(0), mLanguageData->getStringData("English"));
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption2Pos, mMenuFont,
		isSelected(1), mLanguageData->getStringData("Pirate"));
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption3Pos, mMenuFont,
		isSelected(2), mLanguageData->getStringData("UWU"));
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption4Pos, mMenuFont,
		isSelected(3), mLanguageData->getStringData("ReturnToMenu"));
}

void Menu::updatePauseScreen()
{
	mNumButtons = 2;
}

void Menu::drawPauseScreen()
{
	// Draw pause screen text
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mTitlePos, mMenuFont,
		mTitleColor, mLanguageData->getStringData("PausedTitle"));
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption1Pos, mMenuFont,
		isSelected(0), mLanguageData->getStringData("Continue"));
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption2Pos, mMenuFont,
		isSelected(1), mLanguageData->getStringData("ReturnToMenu"));
}

void Menu::updateLossScreen()
{
	mNumButtons = 2;
}

void Menu::drawLossScreen()
{
	// Draw loss screen text
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mTitlePos, mMenuFont,
		mTitleColor, mLanguageData->getStringData("GameOverTitle"));
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption1Pos, mMenuFont,
		isSelected(0), mLanguageData->getStringData("Restart"));
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption2Pos, mMenuFont,
		isSelected(1), mLanguageData->getStringData("ReturnToMenu"));
}

void Menu::updateDifficultyMenu()
{
	mNumButtons = 4;
}

void Menu::drawDifficultyMenu()
{
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mTitlePos, mMenuFont,
		mTitleColor, mLanguageData->getStringData("DifficultyTitle"));  
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption1Pos, mMenuFont,
		isSelected(0), mLanguageData->getStringData("Difficulty1")); 
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption2Pos, mMenuFont,
		isSelected(1), mLanguageData->getStringData("Difficulty2")); 
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption3Pos, mMenuFont,
		isSelected(2), mLanguageData->getStringData("Difficulty3"));
	Game::getInstance()->getGraphics()->writeText(Game::getInstance()->getGraphics()->getBackBuffer(), mOption4Pos, mMenuFont,
		isSelected(3), mLanguageData->getStringData("ReturnToMenu"));
}

Color Menu::isSelected(int index)
{
	if (mButtonSelected == index)
	{
		return mSelectedColor;
	}
	else
	{
		return difficultySelected(index);
	}
}

Color Menu::difficultySelected(int index)
{
	if (mDifficultySelected == index && Game::getInstance()->mInDifficulty)
	{
		return mDifficultyColor;
	}
	else
	{
		return mUnselectedColor;
	}
}


void Menu::handleEvent(const Event& event)
{
	if (event.getType() == DOWN)
	{
		mButtonSelected += 1;
		if (mButtonSelected == mNumButtons)
		{
			mButtonSelected = 0;
		}
	}
	else if (event.getType() == UP)
	{
		mButtonSelected -= 1;
		if (mButtonSelected == -1)
		{
			mButtonSelected = mNumButtons - 1;
		}
	}
	else if (event.getType() == SELECT)
	{
		const MenuEvent& menuEvent = static_cast<const MenuEvent&>(event);

		if (menuEvent.getMenu() == "MainMenu")
		{
			if (mButtonSelected == 0)
			{
				EventSystem::getInstance()->fireEvent(GameEvent(CHARACTER_SELECT));
			}
			else if (mButtonSelected == 1)
			{
				EventSystem::getInstance()->fireEvent(GameEvent(OPTIONS));
			}
			else if (mButtonSelected == 2)
			{
				EventSystem::getInstance()->fireEvent(GameEvent(LANGUAGE));
			}
			else if (mButtonSelected == 3)
			{
				EventSystem::getInstance()->fireEvent(GameEvent(LOAD_SAVE));
			}
			else if (mButtonSelected == 4)
			{
				EventSystem::getInstance()->fireEvent(GameEvent(QUIT_GAME));
			}
		}
		else if (menuEvent.getMenu() == "Options")
		{
			if (mButtonSelected == 0)
			{
				EventSystem::getInstance()->fireEvent(GameEvent(DIFFICULTY));
			}
			else if (mButtonSelected == 1)
			{
				EventSystem::getInstance()->fireEvent(GameEvent(TOGGLE_MUSIC));
			}
			else if (mButtonSelected == 2)
			{
				EventSystem::getInstance()->fireEvent(GameEvent(RETURN_MAIN_MENU));
			}
		}
		else if (menuEvent.getMenu() == "Language")
		{
			if (mButtonSelected == 0)
			{
				mLanguageData->loadData(DATA_ASSET_PATH + ENGLISH_LANGUAGE);
			}
			else if (mButtonSelected == 1)
			{
				mLanguageData->loadData(DATA_ASSET_PATH + PIRATE_LANGUAGE);
			}
			else if (mButtonSelected == 2)
			{
				mLanguageData->loadData(DATA_ASSET_PATH + UWU_LANGUAGE);
			}
			else if (mButtonSelected == 3)
			{
				EventSystem::getInstance()->fireEvent(GameEvent(RETURN_MAIN_MENU));
			}
		}
		else if (menuEvent.getMenu() == "CharacterSelect")
		{
			if (mButtonSelected == 0)
			{
				EventSystem::getInstance()->fireEvent(GameEvent(WARRIOR_SELECT));
			}
			else if (mButtonSelected == 1)
			{
				EventSystem::getInstance()->fireEvent(GameEvent(BANDIT_SELECT));
			}
			else if (mButtonSelected == 2)
			{
				EventSystem::getInstance()->fireEvent(GameEvent(WIZARD_SELECT));
			}
		}
		else if (menuEvent.getMenu() == "Paused")
		{
			if (mButtonSelected == 0)
			{
				EventSystem::getInstance()->fireEvent(GameEvent(UNPAUSE_START_RESTART_GAME));
			}
			else if (mButtonSelected == 1)
			{
				EventSystem::getInstance()->fireEvent(GameEvent(RETURN_MAIN_MENU));
			}
		}
		else if (menuEvent.getMenu() == "GameOver")
		{
			if (mButtonSelected == 0)
			{
				EventSystem::getInstance()->fireEvent(GameEvent(UNPAUSE_START_RESTART_GAME));
			}
			else if (mButtonSelected == 1)
			{
				EventSystem::getInstance()->fireEvent(GameEvent(RETURN_MAIN_MENU));
			}
		}
		else if (menuEvent.getMenu() == "Difficulty")
		{
			if (mButtonSelected == 0)
			{
				mDifficultySelected = 0;
				EventSystem::getInstance()->fireEvent(GameEvent(DIFFICULTY_ONE));
			}
			else if (mButtonSelected == 1)
			{
				mDifficultySelected = 1;
				EventSystem::getInstance()->fireEvent(GameEvent(DIFFICULTY_TWO));
			}
			else if (mButtonSelected == 2)
			{
				mDifficultySelected = 2;
				EventSystem::getInstance()->fireEvent(GameEvent(DIFFICULTY_THREE));
			}
			else if (mButtonSelected == 3)
			{
				EventSystem::getInstance()->fireEvent(GameEvent(RETURN_MAIN_MENU));
			}
		}
	}
}
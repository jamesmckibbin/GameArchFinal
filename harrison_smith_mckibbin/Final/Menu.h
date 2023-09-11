#pragma once

#include "Game.h"

class Menu : public EventListener
{
public:
	Menu() {}
	~Menu() {
		cleanup();
	}
	void init();
	void cleanup();

	void updateMainMenu();
	void drawMainMenu();
	void updateCharacterMenu();
	void drawCharacterMenu();
	void updateOptionsMenu();
	void drawOptionsMenu();
	void updateLanguageMenu();
	void drawLanguageMenu();
	void updatePauseScreen();
	void drawPauseScreen();
	void updateLossScreen();
	void drawLossScreen();
	void updateDifficultyMenu();
	void drawDifficultyMenu();

	void setSelected(int num) { mButtonSelected = num; }
	Color isSelected(int index);
	Color difficultySelected(int index);

	void handleEvent(const Event& event);
private:
	int mButtonSelected = 0;
	int mNumButtons = 0;
	int mDifficultySelected = 1;
	Font* mMenuFont = nullptr;
	Font* mCreditsFont = nullptr;
	FileData* mLanguageData = nullptr;
	
	Color mTitleColor = Color(255, 0, 255, 255);
	Color mUnselectedColor = Color(255, 255, 255, 255);
	Color mSelectedColor = Color(255, 255, 0, 255);
	Color mDifficultyColor = Color(255, 0, 0, 255);

	Vector2D mTitlePos = Vector2D(20, 20);
	Vector2D mOption1Pos = Vector2D(20, 200);
	Vector2D mOption2Pos = Vector2D(20, 240);
	Vector2D mOption3Pos = Vector2D(20, 280);
	Vector2D mOption4Pos = Vector2D(20, 320);
	Vector2D mOption5Pos = Vector2D(20, 360);
};
#pragma once
#include <Vector2D.h>
#include <fstream>

class AutoSave
{
public:

	void saveAllData();
	void savePlayerLocation(Vector2D location);
	void saveEnemyLocation(Vector2D location, int i);
	void saveWaveNumber(int waveNumber);
	void saveNumEnemiesOnScreen(int numEnemiesOnScreen);
	void saveChosenCharacter(int selectedCharacter);
	
private:

	const std::string FILE_NAME = "AutoSave.txt";
	
	float mPlayerLocationX;
	float mPlayerLocationY;
	int mWaveNumber;
	int mNumEnemiesOnScreen;
	float mEnemyLocationsX[100];
	float mEnemyLocationsY[100];
	int mChosenCharacter;


};
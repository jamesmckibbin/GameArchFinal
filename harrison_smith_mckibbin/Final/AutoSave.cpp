#include "AutoSave.h"


void AutoSave::saveAllData()
{
	std::ofstream outFile(FILE_NAME);
	if (outFile.good())
	{
		outFile << "PlayerX " << mPlayerLocationX << "\n";
		outFile << "PlayerY " << mPlayerLocationY << "\n";
		outFile << "ChosenCharacter " << mChosenCharacter << "\n";
		outFile << "WaveNumber " << mWaveNumber << "\n";
		outFile << "NumEnemies " << mNumEnemiesOnScreen << "\n";

		for (int i = 0; i < mNumEnemiesOnScreen; i++)
		{
			outFile << i << "EnemyX " << mEnemyLocationsX[i] << "\n";
			outFile << i << "EnemyY " << mEnemyLocationsY[i] << "\n";
		}

		outFile.close();
	}

}

void AutoSave::savePlayerLocation(Vector2D location)
{
	mPlayerLocationX = location.getX();
	mPlayerLocationY = location.getY();
}

void AutoSave::saveEnemyLocation(Vector2D location, int i)
{
	mEnemyLocationsX[i] = location.getX();
	mEnemyLocationsY[i] = location.getY();
}

void AutoSave::saveWaveNumber(int waveNumber)
{
	mWaveNumber = waveNumber;
}

void AutoSave::saveNumEnemiesOnScreen(int numEnemiesOnScreen)
{
	mNumEnemiesOnScreen = numEnemiesOnScreen;
}

void AutoSave::saveChosenCharacter(int selectedCharacter)
{
	mChosenCharacter = selectedCharacter;
}

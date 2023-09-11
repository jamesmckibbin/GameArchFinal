#include "EnemyManager.h"
#include "Game.h"


void EnemyManager::createUnit(const Vector2D& pos)
{
	if (!mIndexes.empty())
	{
		int unitIndex = mIndexes.front();
		mIndexes.erase(mIndexes.begin());
		mUnits[unitIndex] = Enemy(Game::getInstance()->getAnimationManager()->getAnimation("Enemy", 250, true), 
			Game::getInstance()->getAnimationManager()->getAnimation("Enemy", 250, true), pos);
		mActiveEnemyUnits++;
	}
}

void EnemyManager::deleteUnit(int unitToDelete)
{
	if (unitExists(unitToDelete))
	{
		mUnits[unitToDelete] = Enemy();
		mIndexes.push_back(unitToDelete);
		mActiveEnemyUnits--;
	}
}

bool EnemyManager::checkAtLocation(const Vector2D& loc, const int radius)
{
	for (int i = 0; i < NUM_UNITS; i++)
	{
		if (unitExists(i))
		{
			if (mUnits[i].getPosition().getX() < loc.getX() + radius &&
				mUnits[i].getPosition().getX() > loc.getX() - radius &&
				mUnits[i].getPosition().getY() < loc.getY() + radius &&
				mUnits[i].getPosition().getY() > loc.getY() - radius)
			{
				return true;
			}
		}
	}

	return false;
}

void EnemyManager::deleteAtLocation(const Vector2D& loc, const int radius)
{
	for (int i = 0; i < NUM_UNITS; i++)
	{
		if (unitExists(i))
		{
			if (mUnits[i].getPosition().getX() < loc.getX() + radius &&
				mUnits[i].getPosition().getX() > loc.getX() - radius &&
				mUnits[i].getPosition().getY() < loc.getY() + radius &&
				mUnits[i].getPosition().getY() > loc.getY() - radius)
			{
				deleteUnit(i);

				return;
			}
		}
	}
}

void EnemyManager::deleteAtLocation(const Vector2D& loc, int radius, bool multipleUnits)
{
	for (int i = 0; i < NUM_UNITS; i++)
	{
		if (unitExists(i))
		{
			if (mUnits[i].getPosition().getX() < loc.getX() + radius &&
				mUnits[i].getPosition().getX() > loc.getX() - radius &&
				mUnits[i].getPosition().getY() < loc.getY() + radius &&
				mUnits[i].getPosition().getY() > loc.getY() - radius)
			{
				deleteUnit(i);

				if (!multipleUnits)
				{
					return;
				}
			}
		}
	}
}

void EnemyManager::clearUnits()
{
	for (int i = 0; i < NUM_UNITS; i++)
	{
		if (unitExists(i))
		{ 
			deleteUnit(i);
		}
	}
}


void EnemyManager::init()
{
	// Initializing indexes
	for (int i = 0; i < NUM_UNITS; i++)
	{
		mIndexes.push_back(i);
	}
}

void EnemyManager::cleanup()
{
	clearUnits();
	mIndexes.clear();
}

void EnemyManager::updateUnits(const float deltaTime)
{
	if (mShouldAnimate)
	{
		for (int i = 0; i < 40; i++)
		{
			if (unitExists(i))
			{
				mUnits[i].updateUnit(deltaTime);
			}
		}
	}
}

void EnemyManager::updateVelocity(Vector2D target)
{
	if (mShouldAnimate)
	{
		for (int i = 0; i < NUM_UNITS; i++)
		{
			if (unitExists(i))
			{
				mUnits[i].setVelocity(target - mUnits[i].getPosition());
			}
		}
	}
}

void EnemyManager::drawUnits()
{
	for (int i = 0; i < NUM_UNITS; i++)
	{
		if (unitExists(i))
		{
			mUnits[i].drawUnit();
		}
	}
}

void EnemyManager::pauseUnits()
{
	if (mShouldAnimate)
	{
		mShouldAnimate = false;
	}
}

void EnemyManager::unPauseUnits()
{
	if (!mShouldAnimate)
	{
		mShouldAnimate = true;
	}
}

bool EnemyManager::unitExists(int unitToFind)
{
	for (auto it = mIndexes.begin(); it != mIndexes.end(); it++)
	{
		if (*it == unitToFind)
		{
			return false;
		}
	}
	return true;
}

Vector2D EnemyManager::randomSpawnLocation()
{
	Game* game = Game::getInstance();

	int x;
	int y;

	//Random Y value
	if (rand() % 2 == 0)
	{
		//gets random y from the bottom 
		y = 0;
	}
	else
	{
		//gets random y from the top side
		y = game->getGraphics()->getScreenHeight();
	}

	//Random X value
	if (rand() % 2 == 0)
	{
		//gets random x from the left side
		x = 0;
	}
	else
	{
		//gets random x from the right side
		x = game->getGraphics()->getScreenWidth();
	}

	Vector2D location = Vector2D(x, y);
	return location; //returns a random spawn location

	
}
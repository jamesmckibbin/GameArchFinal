#include "PlayerManager.h"

void PlayerManager::createPlayer(const Vector2D& pos, const int& character)
{
	if (mPlayer != NULL)
	{
		deleteUnit();
	}

	switch (character)
	{
	case 0:
		mPlayer = new Warrior(pos);
		break;
	case 1:
		mPlayer = new Bandit(pos);
		break;
	default:
		mPlayer = new Wizard(pos);
		break;
	}
}

void PlayerManager::deleteUnit()
{
	delete mPlayer;
	mPlayer = nullptr;
}

void PlayerManager::clearUnits()
{
	delete mPlayer;
	mPlayer = nullptr;
}


void PlayerManager::init()
{
	
}

void PlayerManager::cleanup()
{
	clearUnits();
}

void PlayerManager::updateUnits(const float deltaTime)
{
	if (mShouldAnimate)
	{
		for (int i = 0; i < 1; i++)
		{
			if (unitExists())
			{
				Vector2D oldPos = mPlayer->getPosition();
				mPlayer->updateUnit(deltaTime);

				if (playerOffScreen(i))
				{
					mPlayer->setPosition(oldPos);
				}
			}
		}
	}
}

void PlayerManager::drawUnits()
{
	for (int i = 0; i < 1; i++)
	{
		if (unitExists())
		{
			mPlayer->drawUnit();
		}
	}
}

void PlayerManager::pauseUnits()
{
	if (mShouldAnimate)
	{
		mShouldAnimate = false;
	}
}

void PlayerManager::unPauseUnits()
{
	if (!mShouldAnimate)
	{
		mShouldAnimate = true;
	}
}

void PlayerManager::changeUnitAnim(const Vector2D& pos)
{
	for (int i = 0; i < 1; i++)
	{
		if (unitExists() && mouseOnUnit(pos, i))
		{
			return;
		}
	}
}

bool PlayerManager::unitExists()
{
	if (mPlayer != NULL)
		return true;
	else
		return false;
}

bool PlayerManager::mouseOnUnit(const Vector2D& mousePos, unsigned int index)
{
	if (
		mousePos.getX() < mPlayer->getPosition().getX() ||
		mousePos.getY() < mPlayer->getPosition().getY() ||
		mousePos.getX() > mPlayer->getPosition().getX() + mPlayer->getAnimation()->getCurrentSprite().getWidth() ||
		mousePos.getY() > mPlayer->getPosition().getY() + mPlayer->getAnimation()->getCurrentSprite().getHeight()
		)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool PlayerManager::playerOffScreen(int index)
{
	if (
		mPlayer->getPosition().getX() < 0 ||
		mPlayer->getPosition().getY() < 0 ||
		mPlayer->getPosition().getX() > SCREEN_WIDTH - mPlayerHitbox.getX() ||
		mPlayer->getPosition().getY() > SCREEN_HEIGHT - mPlayerHitbox.getY()
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}
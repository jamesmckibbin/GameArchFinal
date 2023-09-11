#include "Player.h"
#include "Game.h"

void Player::updateUnit(const float deltaTime)
{
	// Update animation
	getAnimation()->update(deltaTime);

	// Move player
	mPos += mVelocity * mSpeed * (deltaTime / 1000);

	// Move projectile
	if (mProjectileActive)
	{
		mProjectilePos += mProjectileVelocity * mProjectileSpeed * (deltaTime / 1000);

		if (mProjectilePos.getX() < 0 ||
			mProjectilePos.getX() > 800 ||
			mProjectilePos.getY() < 0 ||
			mProjectilePos.getY() > 600)
		{
			mProjectileActive = false;
		}
	}

	// Check Bandit special
	if (mInvincibleTime > 0.0f)
	{
		mInvincibleTime -= deltaTime;
		cout << mInvincibleTime << endl;
	}
	if (mInvincibleTime <= 0)
	{
		mInvincible = false;
		mInvincibleTime = 0.0f;
	}

}

void Player::drawUnit()
{
	Game::getInstance()->getGraphics()->draw(Game::getInstance()->getGraphics()->getBackBuffer(), mPos, getAnimation()->getCurrentSprite());
}

void Player::spawnProjectile()
{
	if (!mProjectileActive)
	{
		mProjectileActive = true;
		mProjectilePos = mPos;

		if (getVelocity() != Vector2D(0, 0))
			mProjectileVelocity = getVelocity();
	}
}

void Player::despawnProjectile()
{
	mProjectileActive = false;
}

void Player::setPosition(const Vector2D& newPos)
{
	mPos = newPos;
}

void Player::setVelocityX(float newVelX)
{
	Vector2D newVector = Vector2D(newVelX, mVelocity.getY()).getNormalizedVector();
	mVelocity = newVector;
}

void Player::setVelocityY(float newVelY)
{
	Vector2D newVector = Vector2D(mVelocity.getX(), newVelY).getNormalizedVector();
	mVelocity = newVector;
}

void Player::banditSpecial()
{
	if (mInvincible == false)
	{
		mInvincible = true;
		mInvincibleTime = 5000.0f;
	}
}


Animation* Player::getAnimation()
{
	return &mMainAnim;
}





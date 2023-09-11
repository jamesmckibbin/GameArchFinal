#include "Enemy.h"
#include "Game.h"

void Enemy::updateUnit(const float deltaTime)
{
	// Update animation
	setAnimation();
	mCurrentAnim->update(deltaTime);

	// Move player
	mPos += mVelocity * mSpeed * (deltaTime / 1000);
}

void Enemy::drawUnit()
{
	setAnimation();
	Game::getInstance()->getGraphics()->draw(Game::getInstance()->getGraphics()->getBackBuffer(), mPos, mCurrentAnim->getCurrentSprite());
}

void Enemy::setPosition(const Vector2D& newPos)
{
	mPos = newPos;
}

void Enemy::setVelocity(const Vector2D& newVel)
{
	Vector2D normVel = newVel.getNormalizedVector();
	mVelocity = normVel;
}

void Enemy::setAnimation()
{
	mCurrentAnim = &mMainAnim;
}

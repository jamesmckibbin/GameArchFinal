#pragma once
#include "Animation.h"
#include "Vector2D.h"
#include "Game.h"

class Player : public Trackable
{
public:
	Player() {}
	Player(Animation* anim1, const Vector2D& pos) :
	mPos(pos), mMainAnim(*anim1) {}
	~Player() {}

	void updateUnit(float deltaTime);
	void drawUnit();

	void setPosition(const Vector2D& newPos);
	void setVelocityX(float newVelX);
	void setVelocityY(float newVelY);
	void spawnProjectile();
	void despawnProjectile();
	void banditSpecial();

	Animation* getAnimation();
	Vector2D getPosition() { return Vector2D(mPos.getX(), mPos.getY()); }
	Vector2D getVelocity() { return mVelocity; }
	Vector2D getProjectilePos() { return mProjectilePos; }
	bool getProjectileActive() { return mProjectileActive; }
	int getAttackReach() { return mAttackReach; }
	int getAttackRadius() { return mAttackRadius; }
	int getSecondAttackRadius() { return mSecondAttackRadius; }
	int getAttackRate() { return mAttackRate; }
	int getHealthMax() { return mHealthMax; }
	float getInvincibleTime() { return mInvincibleTime; }
	bool isInvincible() { return mInvincible; }

	virtual int getCharacter() { return 0; }

protected:
	Vector2D mPos;
	Vector2D mProjectilePos;
	Vector2D mVelocity = Vector2D(0, 0);
	Vector2D mProjectileVelocity = Vector2D(1, 0);
	float mSpeed = 200.0f;
	float mInvincibleTime = 0.0f;
	int mProjectileSpeed = 300;
	int mAttackReach = 30;
	int mAttackRadius = 50;
	int mSecondAttackRadius = 150;
	int mAttackRate = 30;
	int mHealthMax = 6;

	bool mInvincible = false;
	bool mProjectileActive = false;

	Animation mMainAnim;
};

class Warrior :
	public Player
{
public:
	Warrior() {}
	Warrior(const Vector2D& pos) :
		Player(Game::getInstance()->getAnimationManager()->getAnimation("Warrior", 250, true), pos)
	{
		mSpeed = 200.0f;
		mAttackReach = 30;
		mAttackRadius = 80;
		mAttackRate = 50;
		mHealthMax = 6;
	}
	~Warrior() {}

	int getCharacter() { return 0; }
};

class Bandit :
	public Player
{
public:
	Bandit() {}
	Bandit(const Vector2D& pos) :
		Player(Game::getInstance()->getAnimationManager()->getAnimation("Bandit", 250, true), pos)
	{
		mSpeed = 300.0f;
		mAttackReach = 30;
		mAttackRadius = 50;
		mAttackRate = 30;
		mHealthMax = 4;
	}
	~Bandit() {}

	int getCharacter() { return 1; }
};

class Wizard :
	public Player
{
public:
	Wizard() {}
	Wizard(const Vector2D& pos) :
		Player(Game::getInstance()->getAnimationManager()->getAnimation("Wizard", 250, true), pos)
	{
		mSpeed = 100.0f;
		mAttackRadius = 30;
		mHealthMax = 5;
	}
	~Wizard() {}

	int getCharacter() { return 2; }
};
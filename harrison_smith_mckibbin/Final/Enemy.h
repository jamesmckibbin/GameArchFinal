#pragma once
#include "Animation.h"
#include "Vector2D.h"

class Enemy : public Trackable
{
public:
	Enemy() {}
	Enemy(Animation* anim1, Animation* anim2, const Vector2D& pos) :
		mPos(pos), mMainAnim(*anim1), mAltAnim(*anim2), mCurrentAnim(&mMainAnim) {
	};
	~Enemy() {}

	void updateUnit(float deltaTime);
	void drawUnit();
	void swapAnimation();

	void setPosition(const Vector2D& newPos);
	void setVelocity(const Vector2D& newVel);
	void setAnimation();

	Animation* getAnimation() { return mCurrentAnim; }
	Vector2D getPosition() { return mPos; }
private:
	Vector2D mPos;
	Vector2D mVelocity = Vector2D(0, 0);
	float mSpeed = 70.0f;

	Animation mMainAnim;
	Animation mAltAnim;
	Animation* mCurrentAnim = nullptr;
};
#pragma once

#include "Sprite.h"
#include "AnimationData.h"

class Animation : public Trackable
{

public:
	Animation() {}
	Animation(AnimationData* animData, const float& targetTime, const bool loop) :
	mAnimData(animData), mShouldLoop(loop), mTimePerFrame(targetTime), mTimeTillNextFrame(targetTime) {}
	~Animation() {}
	void update(float deltaTime);
	Sprite getCurrentSprite() const { return mAnimData->getSpriteList()[mCurrentSpriteIndex]; }
	void speedUpAnim();
	void slowDownAnim();

private:
	AnimationData* mAnimData = nullptr;
	unsigned int mCurrentSpriteIndex = 0;
	bool mShouldLoop = false;
	float mTimePerFrame = 0;
	float mTimeTillNextFrame = 0;
};

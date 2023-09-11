#include "Animation.h"


void Animation::update(const float deltaTime)
{
	mTimeTillNextFrame -= deltaTime;

	if (mTimeTillNextFrame <= 0)
	{
		if (mCurrentSpriteIndex < mAnimData->getSpriteList().size() - 1)
		{
			mTimeTillNextFrame = mTimePerFrame;
			mCurrentSpriteIndex++;
		}
		else if (mShouldLoop)
		{
			mTimeTillNextFrame = mTimePerFrame;
			mCurrentSpriteIndex = 0;
		}
	}

}

void Animation::speedUpAnim()
{
	mTimePerFrame -= 50;
}

void Animation::slowDownAnim()
{
	mTimePerFrame += 50;
}

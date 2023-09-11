#pragma once

#include "Sprite.h"
#include <vector>

class Sprite;

class AnimationData : public Trackable
{
public:
	AnimationData(std::vector<Sprite> spriteList) : mSpriteList(spriteList) {}
	~AnimationData() {}

	std::vector<Sprite> getSpriteList() { return mSpriteList; }
private:
	std::vector<Sprite> mSpriteList;
};

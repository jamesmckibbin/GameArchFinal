#pragma once

#include "Game.h"
#include "AnimationData.h"
#include <unordered_map>

typedef std::string Key;

class AnimationManager : public Trackable
{
public:
	AnimationManager() {}
	~AnimationManager(){
		cleanup();
	}
	void cleanup();

	void createAnimationData(const Key& key, GraphicsBuffer* buffer, const int numSprites, const Vector2D& spriteSize, const Vector2D& source);
	Animation* getAnimation(const Key& key, const int animSpeed, bool looping);
	void deleteAnimationData(const Key& key);

	bool animKeyExists(const Key& key);

private:
	std::unordered_map<Key, AnimationData*> mAnimMap;
	Animation* mTempAnim = nullptr;
};

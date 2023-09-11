#include "AnimationManager.h"

void AnimationManager::cleanup()
{
	delete mTempAnim;
	mTempAnim = nullptr;

	for (auto it : mAnimMap)
	{
		delete it.second;
	}

	mAnimMap.clear();
}

void AnimationManager::createAnimationData(const Key& key, GraphicsBuffer* buffer, const int numSprites, const Vector2D& spriteSize, const Vector2D& source)
{
	if (!animKeyExists(key))
	{
		std::vector<Sprite> spriteList = std::vector<Sprite>();
		AnimationData* animData = nullptr;

		for (int i = 0; i < numSprites; i++)
		{
			spriteList.push_back(Sprite(buffer, Vector2D(spriteSize.getX() * i, source.getY()),
				spriteSize.getX(), spriteSize.getY()));
		}

		animData = new AnimationData(spriteList);
		mAnimMap[key] = animData;
	}
}

Animation* AnimationManager::getAnimation(const Key& key, const int animSpeed, bool looping)
{
	if (mTempAnim != nullptr)
	{
		delete mTempAnim;
		mTempAnim = nullptr;
	}
	mTempAnim = new Animation(mAnimMap[key], animSpeed, looping);
	return mTempAnim;
}

void AnimationManager::deleteAnimationData(const Key& key)
{
	for (auto it : mAnimMap)
	{
		if (it.first == key)
		{
			delete it.second;
			mAnimMap.erase(key);
			return;
		}
	}
}

bool AnimationManager::animKeyExists(const Key& key)
{
	auto it = mAnimMap.find(key);

	if (it != mAnimMap.end())
	{
		return true;
	}

	return false;
}

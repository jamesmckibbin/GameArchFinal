#include "AudioManager.h"

AudioManager::AudioManager(int samplesToReserve)
{
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(samplesToReserve);
}

void AudioManager::cleanup()
{
	for (auto it : mAudioMap)
	{
		delete it.second;
	}

	mAudioMap.clear();
}

AudioClip* AudioManager::createAudioClip(const Key& key, std::string filename)
{
	AudioClip* newAudioClip = nullptr;

	if (!audioKeyExists(key))
	{
		newAudioClip = new AudioClip(filename);
		mAudioMap[key] = newAudioClip;
	}

	return newAudioClip;
}

void AudioManager::playSound(const Key& key, bool looping)
{
	mAudioMap[key]->playAudioClip(looping);
}

void AudioManager::stopSound(const Key& key)
{
	mAudioMap[key]->stopAudioClip();
}

void AudioManager::deleteAudioClip(const Key& key)
{
	for (auto it : mAudioMap)
	{
		if (it.first == key)
		{
			delete it.second;
			mAudioMap.erase(key);
			return;
		}
	}
}


bool AudioManager::audioKeyExists(const Key& key)
{
	auto it = mAudioMap.find(key);

	if (it != mAudioMap.end())
	{
		return true;
	}

	return false;
}
#pragma once

#include <unordered_map>
#include "Game.h"
#include "GameData.h"
#include "AudioClip.h"

typedef std::string Key;

class AudioManager : public Trackable
{
public:
	AudioManager(int samplesToReserve);
	~AudioManager() {
		cleanup();
	}
	void cleanup();

	AudioClip* createAudioClip(const Key& key, std::string filename);
	void playSound(const Key& key, bool looping);
	void stopSound(const Key& key);
	void deleteAudioClip(const Key& key);

	bool audioKeyExists(const Key& key);
private:
	std::unordered_map<Key, AudioClip*> mAudioMap;
};
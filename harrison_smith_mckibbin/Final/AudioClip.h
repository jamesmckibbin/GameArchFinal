#pragma once

#include "Trackable.h"
#include <allegro5/allegro_audio.h>
#include "allegro5/allegro.h"
#include <string>

class AudioManager;

class AudioClip : public Trackable
{
	friend class AudioManager;

public:
	AudioClip(std::string filename);
	~AudioClip() {
		al_destroy_sample(mSample);
	}

	void playAudioClip(bool loop);
	void stopAudioClip();
private:
	ALLEGRO_SAMPLE* mSample = nullptr;
	ALLEGRO_SAMPLE_ID mSampleID;
};

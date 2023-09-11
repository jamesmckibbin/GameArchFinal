#include "AudioClip.h"

AudioClip::AudioClip(std::string filename)
{
	mSample = al_load_sample(filename.c_str());
}

void AudioClip::playAudioClip(bool loop)
{
	ALLEGRO_PLAYMODE loopSetting;
	if (loop) { loopSetting = ALLEGRO_PLAYMODE_LOOP; }
	else { loopSetting = ALLEGRO_PLAYMODE_ONCE; }

	al_play_sample(mSample, 1.0f, ALLEGRO_AUDIO_PAN_NONE, 1.0f, loopSetting, &mSampleID);
}

void AudioClip::stopAudioClip()
{
	al_stop_sample(&mSampleID);
}
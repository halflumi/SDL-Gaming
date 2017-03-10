#pragma once

#include <iostream>
#include <map>
#include <string>
#include "SDL_mixer.h"

using namespace std;

enum sound_type
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class SoundLoader
{
private:
	static SoundLoader* INSTANCE;
	SoundLoader() {};
	~SoundLoader();
	SoundLoader(const SoundLoader&);
	SoundLoader& operator=(const SoundLoader&) {};

	map<string, Mix_Chunk*> sfxs;
	map<string, Mix_Music*> musics;
public:
	static SoundLoader* Inst()
	{
		if (INSTANCE == 0)
		{
			INSTANCE = new SoundLoader();
			return INSTANCE;
		}
		return INSTANCE;
	}

	bool load(string fileName, string id, sound_type type);

	void playSound(string id, int loop = 0);
	void playMusic(string id, int loop = 0);
};
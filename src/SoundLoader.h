#pragma once

#include <iostream>
#include <unordered_map>
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
private:
	unordered_map<int, Mix_Chunk*> sfxs;
	unordered_map<int, Mix_Music*> musics;
public:
	bool load(string fileName, int id, sound_type type);

	void applyVolumn();
	void playSound(int id, int loop = 0);
	void playMusic(int id, int loop = 0);
};
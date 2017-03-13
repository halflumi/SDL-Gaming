#include "SoundLoader.h"

SoundLoader* SoundLoader::INSTANCE = 0;

SoundLoader::SoundLoader()
{
	Mix_OpenAudio(22050, AUDIO_S16, 2, (4096 / 2));
}

SoundLoader::~SoundLoader()
{
	Mix_CloseAudio();
}

bool SoundLoader::load(string fileName, string id, sound_type type)
{
	if (type == SOUND_MUSIC)
	{
		Mix_Music* newMusic = Mix_LoadMUS(fileName.c_str());
		if (newMusic == 0)
		{
			cout << "SDL_MIXER_ERROR loading music from file: " << Mix_GetError() << endl;
			return false;
		}

		musics[id] = newMusic;
		return true;
	}
	else if (type == SOUND_SFX)
	{
		Mix_Chunk* newChunk = Mix_LoadWAV(fileName.c_str());
		if (newChunk == 0)
		{
			cout << "SDL_MIXER_ERROR loading sfx from file: " << Mix_GetError() << endl;
			return false;
		}

		sfxs[id] = newChunk;
		return true;
	}
	return false;
}

void SoundLoader::playMusic(string id, int loop)
{
	Mix_PlayMusic(musics[id], loop);
}

void SoundLoader::playSound(string id, int loop)
{
	Mix_PlayChannel(-1, sfxs[id], loop);
}
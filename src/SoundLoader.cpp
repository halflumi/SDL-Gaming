#include "SoundLoader.h"
#include "XmlParser.h"

SoundLoader* SoundLoader::INSTANCE = 0;

SoundLoader::~SoundLoader()
{
	Mix_CloseAudio();
}

bool SoundLoader::load(string fileName, int id, sound_type type)
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

void SoundLoader::applyVolumn()
{
	Mix_VolumeMusic(XmlParser::Inst()->volumn_master * XmlParser::Inst()->volumn_music);
	Mix_Volume(-1, XmlParser::Inst()->volumn_master * XmlParser::Inst()->volumn_sfx);
}

void SoundLoader::playMusic(int id, int loop)
{
	Mix_PlayMusic(musics[id], loop);
}

void SoundLoader::playSound(int id, int loop)
{
	Mix_PlayChannel(-1, sfxs[id], loop);
}
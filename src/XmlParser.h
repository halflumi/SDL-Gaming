#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include "tinyxml2.h"
#include "IDSheet.h"

using namespace std;
using namespace tinyxml2;

class XmlParser
{
private:
	XmlParser();
	~XmlParser() {}
	XmlParser(const XmlParser&);
	static XmlParser* INSTANCE;
public:
	int window_x = 100;
	int window_y = 100;
	int window_w = 1024;
	int window_h = 768;
	bool fullscreen = false;
	int volumn_master = 10;
	int volumn_music = 10;
	int volumn_sfx = 10;
	SDL_Scancode key_movingUp = SDL_SCANCODE_W;
	SDL_Scancode key_movingDown = SDL_SCANCODE_S;
	SDL_Scancode key_movingLeft = SDL_SCANCODE_A;
	SDL_Scancode key_movingRight = SDL_SCANCODE_D;
	SDL_Scancode key_openCharacter = SDL_SCANCODE_C;
	SDL_Scancode key_openSkill = SDL_SCANCODE_K;
	SDL_Scancode key_openInventory = SDL_SCANCODE_I;
	SDL_Scancode key_skillHotkey1 = SDL_SCANCODE_F;
	SDL_Scancode key_skillHotkey2 = SDL_SCANCODE_G;
	SDL_Scancode key_skillHotkey3 = SDL_SCANCODE_H;
	SDL_Scancode key_skillHotkey4 = SDL_SCANCODE_F;
	SDL_Scancode key_skillHotkey5 = SDL_SCANCODE_G;
	SDL_Scancode key_skillHotkey6 = SDL_SCANCODE_H;


	int mapID = MapTest01;
	int level = 1;
	int xp = 0;
	int life = 100;
	int mana = 30;
	vector<int> inventory;

	static XmlParser* Inst()
	{
		if (INSTANCE == 0)
		{
			INSTANCE = new XmlParser();
			return INSTANCE;
		}

		return INSTANCE;
	}

	void load();
	void save();
	void loadCharacter();
	void saveCharacter();
};
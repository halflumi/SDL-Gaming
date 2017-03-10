#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Main.h"
#include "Inputor.h"
#include "TextureLoader.h"
#include "SoundLoader.h"
#include "IDSheet.h"
#include "World.h"
#include "Player.h"
#include "Button.h"

Main* Main::INSTANCE = 0;

bool Main::initialize(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL_ERROR initializing video and audio: %s\n", SDL_GetError());
		return false;
	}

	if (Mix_OpenAudio(22050, AUDIO_S16, 2, (4096 / 2)) < 0)
	{
		printf("SDL_MIXER_ERROR opening audio: %s\n", Mix_GetError());
		return false;
	}

	if(fullscreen)
		window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_FULLSCREEN);
	else
		window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("SDL_ERROR creating window: %s\n", SDL_GetError());
		return false;
	}
	windowWidth = width;
	windowHeight = height; 

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("SDL_ERROR creating renderer: %s\n", SDL_GetError());
		return false;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_IMAGE_ERROR initializing IMAGE: %s\n", IMG_GetError());
		return false;
	}

	if (TTF_Init() < 0)
	{
		printf("SDL_TTF_ERROR initializing ttf: %s\n", TTF_GetError());
		return false;
	}

	theFont[segoeui18] = TTF_OpenFont(segoeuiFile, 18);
	if (theFont[segoeui18] == NULL)
	{
		printf("SDL_TTF_ERROR loading .ttf: %s\n", TTF_GetError());
		return false;
	}
	theFont[segoeui22] = TTF_OpenFont(segoeuiFile, 22);
	if (theFont[segoeui22] == NULL)
	{
		printf("SDL_TTF_ERROR loading .ttf: %s\n", TTF_GetError());
		return false;
	}
	theFont[segoeui28] = TTF_OpenFont(segoeuiFile, 28);
	if (theFont[segoeui28] == NULL)
	{
		printf("SDL_TTF_ERROR loading .ttf: %s\n", TTF_GetError());
		return false;
	}
	theFont[arial48] = TTF_OpenFont(arialFile, 28);
	if (theFont[arial48] == NULL)
	{
		printf("SDL_TTF_ERROR loading .ttf: %s\n", TTF_GetError());
		return false;
	}
	TTF_SetFontStyle(theFont[arial48], TTF_STYLE_BOLD);

	TextureLoader::Inst()->load(MainMenuFile, MainMenu);
	TextureLoader::Inst()->load(NewGameButtonFile, NewGameButton);
	TextureLoader::Inst()->load(ExitButtonFile, ExitButton);
	TextureLoader::Inst()->load(OptionButtonFile, OptionButton);
	SoundLoader::Inst()->load(MenuMouseClickFile, MenuMouseClick, SOUND_SFX);
	menuElments.push_back(new Button(NewGameButton));
	menuElments.push_back(new Button(ExitButton));
	menuElments.push_back(new Button(OptionButton));

	_running = true;
	inMainMenu = true;
	return true;
}

void Main::prossessing()
{
	renderWidth = windowWidth;
	renderHeight = windowHeight - UIHEIGHT;
	Inputor::Inst()->updating();

	SDL_RenderClear(Main::Inst()->getRenderer());

	if (inMainMenu)
		updateMainMenu();
	if (inMainMenu)
		renderMainMenu();
	else
	{
		World::Inst()->updating();
		World::Inst()->rendering();
	}

	SDL_RenderPresent(renderer);
}

void Main::updateMainMenu()
{
	int i, len;
	len = menuElments.size();
	for (i = 0; i < len; i++)
		if(inMainMenu)
			menuElments[i]->update();
}

void Main::renderMainMenu()
{
	int i, len;
	TextureLoader::Inst()->drawEx2(MainMenu, 0, 0, 1024, 768, windowWidth, windowHeight);
	len = menuElments.size();
	for (i = 0; i < len; i++)
		menuElments[i]->draw();
}

void Main::close()
{
	cout << "Closing game..." << endl;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
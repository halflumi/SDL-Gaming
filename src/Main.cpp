#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Main.h"
#include "Inputor.h"
#include "TextureLoader.h"
#include "SoundLoader.h"
#include "IDSheet.h"
#include "World.h"
#include "Player.h"
#include "XmlParser.h"

using namespace tinyxml2;

Main* Main::INSTANCE = 0;

bool Main::initialize(const char* title, int xpos, int ypos, int width, int height)
{
	///init sdl_video and sdl_audio
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL_ERROR initializing video and audio: %s\n", SDL_GetError());
		return false;
	}
	///init sdl_mixer
	if (Mix_OpenAudio(22050, AUDIO_S16, 2, (4096 / 2)) < 0)
	{
		printf("SDL_MIXER_ERROR opening audio: %s\n", Mix_GetError());
		return false;
	}
	///create window
	//temporary xml loading here
	XmlParser::Inst()->load();

	if(XmlParser::Inst()->fullscreen)
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
	///create renderer for the window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("SDL_ERROR creating renderer: %s\n", SDL_GetError());
		return false;
	}
	///init sdl_image
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_IMAGE_ERROR initializing IMAGE: %s\n", IMG_GetError());
		return false;
	}
	///init sdl_ttf
	if (TTF_Init() < 0)
	{
		printf("SDL_TTF_ERROR initializing ttf: %s\n", TTF_GetError());
		return false;
	}
	///create fonts
	//segoeui
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
	//arial
	theFont[arial28] = TTF_OpenFont(arialFile, 28);
	if (theFont[arial28] == NULL)
	{
		printf("SDL_TTF_ERROR loading .ttf: %s\n", TTF_GetError());
		return false;
	}
	TTF_SetFontStyle(theFont[arial28], TTF_STYLE_BOLD);
	theFont[arial48] = TTF_OpenFont(arialFile, 48);
	if (theFont[arial48] == NULL)
	{
		printf("SDL_TTF_ERROR loading .ttf: %s\n", TTF_GetError());
		return false;
	}
	TTF_SetFontStyle(theFont[arial48], TTF_STYLE_BOLD);

	TextureLoader::Inst()->load(MainMenuFile, MainMenu);
	TextureLoader::Inst()->load(FullscreenCheckboxFile, FullscreenCheckbox);
	SoundLoader::Inst()->load(MenuMouseClickFile, MenuMouseClick, SOUND_SFX);
	changeMenu(Menu_Main);

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

	if (HandleMenuEvents())
		return;

	if (inMainMenu)
	{
		updateMainMenu();
		renderMainMenu();
	}
	else
	{
		World::Inst()->updating();
		World::Inst()->rendering();
	}

	SDL_RenderPresent(renderer);
}

bool Main::HandleMenuEvents()
{
	int i, len;
	len = menuButtons.size();
	for (i = 0; i < len; i++)
	{
		if (menuButtons[i]->outsideUpdate())
		{
			if (menuButtons[i]->getUniqueID() == NewGameButton)
			{
				SoundLoader::Inst()->playSound(MenuMouseClick);
				inMainMenu = false;
				menuButtons.clear();
				TextureLoader::Inst()->clearTextureMap();
				World::Inst()->initialize();
				return true;
			}
			if (menuButtons[i]->getUniqueID() == OptionButton)
			{
				SoundLoader::Inst()->playSound(MenuMouseClick);
				changeMenu(Menu_Options);
				return true;
			}
			if (menuButtons[i]->getUniqueID() == ExitButton)
			{
				SoundLoader::Inst()->playSound(MenuMouseClick);
				SDL_Delay(350);
				quit();
				return true;
			}
			if (menuButtons[i]->getUniqueID() == FullscreenCheckbox)
			{
				SoundLoader::Inst()->playSound(MenuMouseClick);
				XmlParser::Inst()->fullscreen = !XmlParser::Inst()->fullscreen;
				return false;
			}
			if (menuButtons[i]->getUniqueID() == BackButton)
			{
				SoundLoader::Inst()->playSound(MenuMouseClick);
				changeMenu(Menu_Main);
				return true;
			}
		}
	}
	return false;
}

void Main::changeMenu(int menuID)
{
	menuButtons.clear();
	switch (menuID)
	{
	case Menu_Main:
		menuButtons.push_back(new Button(NewGameButton));
		menuButtons.push_back(new Button(ExitButton));
		menuButtons.push_back(new Button(OptionButton));
		break;
	case Menu_Options:
		menuButtons.push_back(new Button(FullscreenCheckbox));
		menuButtons.push_back(new Button(FullscreenText));
		menuButtons.push_back(new Button(BackButton));
		break;
	}
}

void Main::updateMainMenu()
{
	int i, len;
	len = menuButtons.size();
	for (i = 0; i < len; i++)
		menuButtons[i]->update();
}

void Main::renderMainMenu()
{
	TextureLoader::Inst()->drawEx2(MainMenu, 0, 0, 1024, 768, windowWidth, windowHeight);

	int i, len;
	len = menuButtons.size();
	for (i = 0; i < len; i++)
		menuButtons[i]->draw();
}

void Main::close()
{
	cout << "Closing game..." << endl;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	cout << "Saving settings to xml..." << endl;
	XmlParser::Inst()->save();

	SDL_Quit();
}
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
#include "Camera.h"

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
	theFont[arial28_bold] = TTF_OpenFont(arialFile, 28);
	if (theFont[arial28_bold] == NULL)
	{
		printf("SDL_TTF_ERROR loading .ttf: %s\n", TTF_GetError());
		return false;
	}
	TTF_SetFontStyle(theFont[arial28_bold], TTF_STYLE_BOLD);
	theFont[arial48_bold] = TTF_OpenFont(arialFile, 48);
	if (theFont[arial48_bold] == NULL)
	{
		printf("SDL_TTF_ERROR loading .ttf: %s\n", TTF_GetError());
		return false;
	}
	TTF_SetFontStyle(theFont[arial48_bold], TTF_STYLE_BOLD);
	theFont[arial72_bold] = TTF_OpenFont(arialFile, 48);
	if (theFont[arial72_bold] == NULL)
	{
		printf("SDL_TTF_ERROR loading .ttf: %s\n", TTF_GetError());
		return false;
	}
	TTF_SetFontStyle(theFont[arial72_bold], TTF_STYLE_BOLD);
	///load menu res
	TextureLoader::Inst()->load(MainMenuPicFile, MainMenuPic);
	TextureLoader::Inst()->load(FullscreenCheckboxFile, FullscreenCheckbox);
	TextureLoader::Inst()->load(VolumnLButtonFile, VolumnLButton);
	TextureLoader::Inst()->load(VolumnRButtonFile, VolumnRButton);
	SoundLoader::Inst()->load(Music01File, Music01, SOUND_MUSIC);
	//SoundLoader::Inst()->playMusic(Music01, 2);
	SoundLoader::Inst()->load(MenuMouseClickFile, MenuMouseClick, SOUND_SFX);
	changeMenu(MenuMain);

	_running = true;
	inMainMenu = true;
	inGameMenu = false;
	return true;
}

void Main::prossessing()
{
	renderWidth = windowWidth;
	renderHeight = windowHeight - UIHEIGHT;
	
	Inputor::Inst()->updating();

	SDL_RenderClear(Main::Inst()->getRenderer());

	if (!inMainMenu && !inGameMenu)
		World::Inst()->updating();
	if (!inMainMenu)
		World::Inst()->rendering();
	if (inMainMenu|| inGameMenu)
	{
		if (HandleMenuEvents())
			return;
		UpdateMenu();
		RenderMenu();
	}

	SDL_RenderPresent(renderer);
	SoundLoader::Inst()->applyVolumn();
}

bool Main::HandleMenuEvents()
{
	Player* player = Camera::Inst()->getTarget_nonConst();
	if (Inputor::Inst()->isKeyDown(SDL_SCANCODE_ESCAPE) && keyCooldown.getTicks() > PRESSCOOLDOWN)
	{
		switch (currentMenu)
		{
		case MenuOptions:
			changeMenu(MenuMain);
			return true;
			break;
		case MenuGameMain:
			inGameMenu = false;
			player->keyCooldown.start();
			return true;
			break;
		}
	}

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
				World::Inst()->startNewGame();
				World::Inst()->initialize();
				return true;
			}
			if (menuButtons[i]->getUniqueID() == ContinueButton)
			{
				SoundLoader::Inst()->playSound(MenuMouseClick);
				inMainMenu = false;
				menuButtons.clear();
				World::Inst()->startOldGame();
				World::Inst()->initialize();
				return true;
			}
			if (menuButtons[i]->getUniqueID() == OptionButton)
			{
				SoundLoader::Inst()->playSound(MenuMouseClick);
				changeMenu(MenuOptions);
				return true;
			}
			if (menuButtons[i]->getUniqueID() == ExitButton)
			{
				SoundLoader::Inst()->playSound(MenuMouseClick);
				SDL_Delay(350);
				quit();
				return true;
			}
			if (menuButtons[i]->getUniqueID() == ResolutionListbox)
			{
				SoundLoader::Inst()->playSound(MenuMouseClick);
				menuButtons[i]->flag++;
				return false;
			}
			if (menuButtons[i]->getUniqueID() == FullscreenCheckbox)
			{
				SoundLoader::Inst()->playSound(MenuMouseClick);
				XmlParser::Inst()->fullscreen = !XmlParser::Inst()->fullscreen;
				return false;
			}
			if (menuButtons[i]->getUniqueID() == VolumnLButton)
			{
				switch (menuButtons[i]->flag)
				{
				case 0:
					XmlParser::Inst()->volumn_master--;
					if (XmlParser::Inst()->volumn_master == -1)
						XmlParser::Inst()->volumn_master = 10;
					break;
				case 1:
					XmlParser::Inst()->volumn_music--;
					if (XmlParser::Inst()->volumn_music == -1)
						XmlParser::Inst()->volumn_music = 10;
					break;
				case 2:
					XmlParser::Inst()->volumn_sfx--;
					if (XmlParser::Inst()->volumn_sfx == -1)
						XmlParser::Inst()->volumn_sfx = 10;
					break;
				}
			}
			if (menuButtons[i]->getUniqueID() == VolumnRButton)
			{
				switch (menuButtons[i]->flag)
				{
				case 0:
					XmlParser::Inst()->volumn_master++;
					if (XmlParser::Inst()->volumn_master == 11)
						XmlParser::Inst()->volumn_master = 0;
					break;
				case 1:
					XmlParser::Inst()->volumn_music++;
					if (XmlParser::Inst()->volumn_music == 11)
						XmlParser::Inst()->volumn_music = 0;
					break;
				case 2:
					XmlParser::Inst()->volumn_sfx++;
					if (XmlParser::Inst()->volumn_sfx == 11)
						XmlParser::Inst()->volumn_sfx = 0;
					break;
				}
			}
			if (menuButtons[i]->getUniqueID() == BackButton)
			{
				SoundLoader::Inst()->playSound(MenuMouseClick);
				changeMenu(MenuMain);
				return true;
			}
		
			if (menuButtons[i]->getUniqueID() == ResumeButton)
			{
				inGameMenu = false;
				player->mouseCooldown.start();
				return true;
			}
			if (menuButtons[i]->getUniqueID() == ExittoMainMenuButton)
			{
				XmlParser::Inst()->saveCharacter();
				World::Inst()->clearWorld();
				World::Inst()->getLayer_player().clear();
				inGameMenu = false;
				changeMenu(MenuMain);
				return true;
			}
			if (menuButtons[i]->getUniqueID() == ExittoDestopButton)
			{
				XmlParser::Inst()->saveCharacter();
				quit();
				return true;
			}
		}
	}
	return false;
}

void Main::changeMenu(int menuID)
{
	keyCooldown.start();

	menuButtons.clear();
	currentMenu = menuID;
	switch (menuID)
	{
	case MenuMain:
		inMainMenu = true;
		menuButtons.push_back(new Button(NewGameButton));
		menuButtons.push_back(new Button(ContinueButton));
		menuButtons.push_back(new Button(ExitButton));
		menuButtons.push_back(new Button(OptionButton));
		break;
	case MenuOptions:
		menuButtons.push_back(new Button(ResolutionText));
		menuButtons.push_back(new Button(ResolutionListbox));
		menuButtons.push_back(new Button(FullscreenCheckbox));
		menuButtons.push_back(new Button(FullscreenText));
		menuButtons.push_back(new Button(VolumnMasterText));
		menuButtons.push_back(new Button(VolumnLButton, 0));
		menuButtons.push_back(new Button(VolumnRButton, 0));
		menuButtons.push_back(new Button(VolumnMasterNumber));
		menuButtons.push_back(new Button(VolumnMusicText));
		menuButtons.push_back(new Button(VolumnLButton, 1));
		menuButtons.push_back(new Button(VolumnRButton, 1));
		menuButtons.push_back(new Button(VolumnMusicNumber));
		menuButtons.push_back(new Button(VolumnSfxText));
		menuButtons.push_back(new Button(VolumnLButton, 2));
		menuButtons.push_back(new Button(VolumnRButton, 2));
		menuButtons.push_back(new Button(VolumnSfxNumber));
		menuButtons.push_back(new Button(BackButton));
		break;
	case MenuGameMain:
		inGameMenu = true;
		menuButtons.push_back(new Button(GameMenuBackground));
		menuButtons.push_back(new Button(ResumeButton));
		menuButtons.push_back(new Button(ExittoMainMenuButton));
		menuButtons.push_back(new Button(ExittoDestopButton));
		break;
	}
}

void Main::UpdateMenu()
{
	int i, len;
	len = menuButtons.size();
	for (i = 0; i < len; i++)
		menuButtons[i]->update();
}

void Main::RenderMenu()
{
	if(inMainMenu)
		TextureLoader::Inst()->drawEx2(MainMenuPic, 0, 0, 1920, 1080, windowWidth, windowHeight);
	if(inGameMenu)
		TextureLoader::Inst()->drawFrameEx(InventoryGridMask, 0, 0, 10, 10, windowWidth, windowHeight, 0, 0, 0, 255);

	int i, len;
	len = menuButtons.size();
	for (i = 0; i < len; i++)
		menuButtons[i]->draw();
}

void Main::close()
{
	cout << "Saving settings to xml..." << endl;
	XmlParser::Inst()->save();
	cout << "Closing game..." << endl;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();
}
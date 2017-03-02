#include <SDL_image.h>
#include "Main.h"
#include "Inputor.h"
#include "TextureLoader.h"
#include "SoundLoader.h"
#include "IDSheet.h"
#include "World.h"
#include "Player.h"

Main* Main::INSTANCE = 0;

bool Main::Initialize(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not be initialized! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

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

	//Get a white background
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_IMAGE_ERROR initializing IMAGE: %s\n", IMG_GetError());
		return false;
	}

	//loading world test
	World::Inst()->load();

	_running = true;
	return true;
}

void Main::handleEvents()
{
	Inputor::Inst()->updating();
}

void Main::updating()
{
	World::Inst()->updating();
}

void Main::rendering()
{
	World::Inst()->rendering();
}

void Main::close()
{
	cout << "Closing game..." << endl;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
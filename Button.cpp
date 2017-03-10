#include "Button.h"
#include "Main.h"
#include "World.h"
#include "TextureLoader.h"
#include "SoundLoader.h"
#include "Inputor.h"
#include "Vector2D.h"

#define NEWGAME_X 351
#define NEWGAME_Y 313
#define NEWGAME_W 281
#define NEWGAME_H 36
#define EXIT_X 351
#define EXIT_Y 562
#define EXIT_W 100
#define EXIT_H 35
#define OPTION_X 351
#define OPTION_Y 429
#define OPTION_W 199
#define OPTION_H 44

Button::Button(string id)
{
	uniqueID = id;
	Load();
}

void Button::Load()
{
	if (uniqueID == NewGameButton)
	{
		position.x = NEWGAME_X;
		position.y = NEWGAME_Y;
		width = NEWGAME_W;
		height = NEWGAME_H;
		numFrames = 2;
		return;
	}
	if (uniqueID == ExitButton)
	{
		position.x = EXIT_X;
		position.y = EXIT_Y;
		width = EXIT_W;
		height = EXIT_H;
		numFrames = 2;
		return;
	}
	if (uniqueID == OptionButton)
	{
		position.x = OPTION_X;
		position.y = OPTION_Y;
		width = OPTION_W;
		height = OPTION_H;
		numFrames = 2;
		return;
	}
	if (uniqueID == InventoryCloseButton)
	{
		width = height = 42;
		numFrames = 2;
	}
}

void Button::update()
{
	if (uniqueID == NewGameButton)
	{
		if (CheckMouseOver())
		{
			currentRow = 1;
			if (Inputor::Inst()->getMouseButtonState(MOUSE_LEFT))
			{
				Main::Inst()->inMainMenu = false;
				SoundLoader::Inst()->playSound(MenuMouseClick);
				Main::Inst()->menuElments.clear();
				TextureLoader::Inst()->clearTextureMap();
				World::Inst()->initialize();
			}
		}
		else
			currentRow = 0;
		return;
	}
	if (uniqueID == ExitButton)
	{
		if (CheckMouseOver())
		{
			currentRow = 1;
			if (Inputor::Inst()->getMouseButtonState(MOUSE_LEFT))
			{
				SoundLoader::Inst()->playSound(MenuMouseClick);
				SDL_Delay(350);
				Main::Inst()->quit();
			}
		}
		else
			currentRow = 0;
		return;
	}
	if (uniqueID == OptionButton)
	{
		if (CheckMouseOver())
		{
			currentRow = 1;
			if (Inputor::Inst()->getMouseButtonState(MOUSE_LEFT))
			{
				SoundLoader::Inst()->playSound(MenuMouseClick);
			}
		}
		else
			currentRow = 0;
		return;
	}
}

void Button::draw()
{
	TextureLoader::Inst()->drawFrame(uniqueID, position.x, position.y, width, height, currentRow, currentFrame, angle, alpha);
}

bool Button::CheckMouseOver()
{
	Vector2D* mousepos = Inputor::Inst()->getMouseRelativePosition();
	if (mousepos->x <= position.x + width && mousepos->x >= position.x && mousepos->y >= position.y && mousepos->y <= position.y + height)
		return true;
	return false;
}

bool Button::outsideUpdate()
{
	if (uniqueID == InventoryCloseButton)
	{
		if (CheckMouseOver())
		{
			currentRow = 1;
			if (Inputor::Inst()->getMouseButtonState(MOUSE_LEFT))
			{
				SoundLoader::Inst()->playSound(MenuMouseClick);
				return true;
			}
		}
		else
			currentRow = 0;
		return false;
	}
	return false;
}
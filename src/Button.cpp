#include "Button.h"
#include "Main.h"
#include "World.h"
#include "TextureLoader.h"
#include "SoundLoader.h"
#include "Inputor.h"
#include "Vector2D.h"
#include "XmlParser.h"

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

Button::Button(string id) : clickCooldown(true)
{
	uniqueID = id;
	Load();
}

void Button::Load()
{
	buttonText = NULL;
	if (uniqueID == NewGameButton)
	{
		position.x = NEWGAME_X;
		position.y = NEWGAME_Y;
		buttonText = new Textbox(position, "New Game", arial48, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial48), "New Game", &width, &height);
		return;
	}
	if (uniqueID == OptionButton)
	{
		position.x = OPTION_X;
		position.y = OPTION_Y;
		buttonText = new Textbox(position, "Options", arial48, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial48), "Options", &width, &height);
		numFrames = 2;
		return;
	}
	if (uniqueID == ExitButton)
	{
		position.x = EXIT_X;
		position.y = EXIT_Y;
		buttonText = new Textbox(position, "Exit", arial48, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial48), "Exit", &width, &height);
		return;
	}
	if (uniqueID == FullscreenCheckbox)
	{
		position.x = NEWGAME_X;
		position.y = NEWGAME_Y + 5;
		width = 20;
		height = 20;
		return;
	}
	if (uniqueID == FullscreenText)
	{
		position.x = NEWGAME_X + 25;
		position.y = NEWGAME_Y;
		buttonText = new Textbox(position, "Fullscreen", arial28, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28), "Fullscreen", &width, &height);
		return;
	}
	if (uniqueID == BackButton)
	{
		position.x = EXIT_X;
		position.y = EXIT_Y;
		buttonText = new Textbox(position, "Back to the Main Menu", arial28, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28), "Back to the Main Menu", &width, &height);
		return;
	}

	//ui
	if (uniqueID == InventoryCloseButton)
	{
		width = height = 42;
		numFrames = 2;
		return;
	}
}

void Button::update()
{
	if (uniqueID == NewGameButton)
	{
		if (CheckMouseOver())
		{
			currentRow = 1;
			buttonText->changeColor(COLOR_RED);
		}
		else if (currentRow == 1)
		{
			currentRow = 0;
			buttonText->changeColor(COLOR_WHITE);
		}
		return;
	}
	if (uniqueID == OptionButton)
	{
		if (CheckMouseOver())
		{
			currentRow = 1;
			buttonText->changeColor(COLOR_ORANGE);
		}
		else if (currentRow == 1)
		{
			currentRow = 0;
			buttonText->changeColor(COLOR_WHITE);
		}
		return;
	}
	if (uniqueID == ExitButton)
	{
		if (CheckMouseOver())
		{
			currentRow = 1;
			buttonText->changeColor(COLOR_BLUE);
		}
		else if (currentRow == 1)
		{
			currentRow = 0;
			buttonText->changeColor(COLOR_WHITE);
		}
		return;
	}
	if (uniqueID == FullscreenCheckbox)
	{
		if (CheckMouseOver())
			currentFrame = 1;
		else
			currentFrame = 0;

		if (XmlParser::Inst()->fullscreen)
			currentRow = 1;
		else
			currentRow = 0;
		return;
	}
	if (uniqueID == BackButton)
	{
		if (CheckMouseOver())
		{
			currentRow = 1;
			buttonText->changeColor(COLOR_ORANGE);
		}
		else if (currentRow == 1)
		{
			currentRow = 0;
			buttonText->changeColor(COLOR_WHITE);
		}
		return;
	}
	//ui
	if (uniqueID == InventoryCloseButton)
	{
		if (CheckMouseOver())
			currentRow = 1;
		else
			currentRow = 0;
		return;
	}
}

void Button::draw()
{
	if(buttonText == NULL)
		TextureLoader::Inst()->drawFrame(uniqueID, position.x, position.y, width, height, currentRow, currentFrame, angle, alpha);
	else
		buttonText->draw();
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
	if (CheckMouseOver() && Inputor::Inst()->getMouseButtonState(MOUSE_LEFT) && clickCooldown.getTicks() > CLICKCOOLDOWN)
	{
		SoundLoader::Inst()->playSound(MenuMouseClick);
		clickCooldown.start();
		return true;
	}

	return false;
}
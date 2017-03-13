#include "Button.h"
#include "Main.h"
#include "World.h"
#include "TextureLoader.h"
#include "SoundLoader.h"
#include "Inputor.h"
#include "Vector2D.h"
#include "XmlParser.h"

#define NEWGAME_X Main::Inst()->getWindowWidth()/2 - 150
#define NEWGAME_Y Main::Inst()->getWindowHeight()/2 - 75
//#define NEWGAME_W 281
//#define NEWGAME_H 36
#define OPTION_X Main::Inst()->getWindowWidth()/2 - 150
#define OPTION_Y Main::Inst()->getWindowHeight()/2 + 25
//#define OPTION_W 199
//#define OPTION_H 44
#define EXIT_X Main::Inst()->getWindowWidth()/2 - 150
#define EXIT_Y Main::Inst()->getWindowHeight()/2 + 125
//#define EXIT_W 100
//#define EXIT_H 35

Button::Button(int id) : clickCooldown(true)
{
	uniqueID = id;
	flag = 0;
	Load();
}

Button::Button(int id, int _flag) : clickCooldown(true)
{
	uniqueID = id;
	flag = _flag;
	Load();
}

void Button::Load()
{
	buttonText = NULL;
	buttonClass = ButtonTypeButton;
	//main menu
	if (uniqueID == NewGameButton)
	{
		position.x = NEWGAME_X;
		position.y = NEWGAME_Y;
		buttonText = new Textbox(position, "New Game", arial48_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial48_bold), "New Game", &width, &height);
		return;
	}
	if (uniqueID == OptionButton)
	{
		position.x = OPTION_X;
		position.y = OPTION_Y;
		buttonText = new Textbox(position, "Options", arial48_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial48_bold), "Options", &width, &height);
		numFrames = 2;
		return;
	}
	if (uniqueID == ExitButton)
	{
		position.x = EXIT_X;
		position.y = EXIT_Y;
		buttonText = new Textbox(position, "Exit", arial48_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial48_bold), "Exit", &width, &height);
		return;
	}
	if (uniqueID == ResolutionText)
	{
		buttonClass = ButtonTypeTextbox;
		position.x = NEWGAME_X;
		position.y = NEWGAME_Y;
		buttonText = new Textbox(position, "Resolution", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Resolution", &width, &height);
		return;
	}
	if (uniqueID == ResolutionListbox)
	{
		position.x = NEWGAME_X + 200;
		position.y = NEWGAME_Y;
		buttonText = new Textbox(position, "", arial28_bold, COLOR_WHITE, -1);
		switch (XmlParser::Inst()->window_w)
		{
		case 800:
			flag = 0;
			break;
		case 1024:
			flag = 1;
			break;
		case 1280:
			flag = 2;
			break;
		case 1600:
			flag = 3;
			break;
		}
		return;
	}
	if (uniqueID == FullscreenText)
	{
		buttonClass = ButtonTypeTextbox;
		position.x = NEWGAME_X;
		position.y = NEWGAME_Y + 50;
		buttonText = new Textbox(position, "Fullscreen", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Fullscreen", &width, &height);
		return;
	}
	if (uniqueID == FullscreenCheckbox)
	{
		position.x = NEWGAME_X + 205;
		position.y = NEWGAME_Y + 57;
		width = 20;
		height = 20;
		return;
	}
	if (uniqueID == VolumnLButton)
	{
		switch (flag)
		{
		case 0:
			position.x = NEWGAME_X + 225;
			position.y = NEWGAME_Y + 110;
			break;
		case 1:
			position.x = NEWGAME_X + 225;
			position.y = NEWGAME_Y + 160;
			break;
		case 2:
			position.x = NEWGAME_X + 225;
			position.y = NEWGAME_Y + 210;
			break;
		}
		width = 15;
		height = 20;
	}
	if (uniqueID == VolumnRButton)
	{
		switch (flag)
		{
		case 0:
			position.x = NEWGAME_X + 290;
			position.y = NEWGAME_Y + 110;
			break;
		case 1:
			position.x = NEWGAME_X + 290;
			position.y = NEWGAME_Y + 160;
			break;
		case 2:
			position.x = NEWGAME_X + 290;
			position.y = NEWGAME_Y + 210;
			break;
		}
		width = 15;
		height = 20;
	}
	if (uniqueID == VolumnMasterText)
	{
		buttonClass = ButtonTypeTextbox;
		position.x = NEWGAME_X;
		position.y = NEWGAME_Y + 100;
		buttonText = new Textbox(position, "Master Volumn", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Master Volumn", &width, &height);
		return;
	}
	if (uniqueID == VolumnMasterNumber)
	{
		buttonClass = ButtonTypeTextbox;
		position.x = NEWGAME_X + 245;
		position.y = NEWGAME_Y + 100;
		buttonText = new Textbox(position, to_string(XmlParser::Inst()->volumn_master), arial28_bold, COLOR_WHITE, -1);
	}
	if (uniqueID == VolumnMusicText)
	{
		buttonClass = ButtonTypeTextbox;
		position.x = NEWGAME_X;
		position.y = NEWGAME_Y + 150;
		buttonText = new Textbox(position, "Music Volumn", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Master Volumn", &width, &height);
		return;
	}
	if (uniqueID == VolumnMusicNumber)
	{
		buttonClass = ButtonTypeTextbox;
		position.x = NEWGAME_X + 245;
		position.y = NEWGAME_Y + 150;
		buttonText = new Textbox(position, to_string(XmlParser::Inst()->volumn_music), arial28_bold, COLOR_WHITE, -1);
	}
	if (uniqueID == VolumnSfxText)
	{
		buttonClass = ButtonTypeTextbox;
		position.x = NEWGAME_X;
		position.y = NEWGAME_Y + 200;
		buttonText = new Textbox(position, "Sfx Volumn", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Master Volumn", &width, &height);
		return;
	}
	if (uniqueID == VolumnSfxNumber)
	{
		buttonClass = ButtonTypeTextbox;
		position.x = NEWGAME_X + 245;
		position.y = NEWGAME_Y + 200;
		buttonText = new Textbox(position, to_string(XmlParser::Inst()->volumn_sfx), arial28_bold, COLOR_WHITE, -1);
	}
	if (uniqueID == BackButton)
	{
		position.x = EXIT_X;
		position.y = EXIT_Y + 100;
		buttonText = new Textbox(position, "Back to the Main Menu", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Back to the Main Menu", &width, &height);
		return;
	}
	//game menu
	if (uniqueID == GameMenuBackground)
	{
		buttonClass = ButtonTypeTextbox;
		width = 600;
		height = 400;
		position.x = Main::Inst()->getWindowWidth() / 2 - width / 2;
		position.y = Main::Inst()->getRenderHeight() / 2 - height / 2;
	}
	if (uniqueID == ResumeButton)
	{
		TTF_SizeText(Main::Inst()->getFont(arial48_bold), "Resume", &width, &height);
		position.x = Main::Inst()->getWindowWidth() / 2 - width / 2;
		position.y = Main::Inst()->getRenderHeight() / 2 - height / 2 - 50;
		buttonText = new Textbox(position, "Resume", arial48_bold, COLOR_WHITE, -1);
		return;
	}
	if (uniqueID == ExittoMainMenuButton)
	{
		TTF_SizeText(Main::Inst()->getFont(arial48_bold), "Exit to Main Menu", &width, &height);
		position.x = Main::Inst()->getWindowWidth() / 2 - width / 2;
		position.y = Main::Inst()->getRenderHeight() / 2 - height / 2 + 50;
		buttonText = new Textbox(position, "Exit to Main Menu", arial48_bold, COLOR_WHITE, -1);
		return;
	}
	if (uniqueID == ExittoDestopButton)
	{
		TTF_SizeText(Main::Inst()->getFont(arial48_bold), "Exit to Desktop", &width, &height);
		position.x = Main::Inst()->getWindowWidth() / 2 - width / 2;
		position.y = Main::Inst()->getRenderHeight() / 2 - height / 2 + 150;
		buttonText = new Textbox(position, "Exit to Desktop", arial48_bold, COLOR_WHITE, -1);
		return;
	}
	//ui
	if (uniqueID == InventoryCloseButton)
	{
		width = height = 42;
		return;
	}
}

void Button::update()
{
	//main menu
	if (uniqueID == NewGameButton)
	{
		if (CheckMouseOver())
			buttonText->changeColor(COLOR_RED);
		else
			buttonText->changeColor(COLOR_WHITE);
		return;
	}
	if (uniqueID == OptionButton || uniqueID == BackButton)
	{
		if (CheckMouseOver())
			buttonText->changeColor(COLOR_ORANGE);
		else
			buttonText->changeColor(COLOR_WHITE);
		return;
	}
	if (uniqueID == ExitButton)
	{
		if (CheckMouseOver())
			buttonText->changeColor(COLOR_BLUE);
		else
			buttonText->changeColor(COLOR_WHITE);
		return;
	}
	if (uniqueID == ResolutionListbox)
	{
		if (CheckMouseOver())
			buttonText->changeColor(COLOR_RED);
		else
			buttonText->changeColor(COLOR_WHITE);

		switch (flag % 4)
		{
		case 0:
			if (buttonText->changeText("800x600"))
			{
				TTF_SizeText(Main::Inst()->getFont(arial28_bold), "800x600", &width, &height);
				XmlParser::Inst()->window_w = 800;
				XmlParser::Inst()->window_h = 600;
			}
			break;
		case 1:
			if (buttonText->changeText("1024x768"))
			{
				TTF_SizeText(Main::Inst()->getFont(arial28_bold), "1024x768", &width, &height);
				XmlParser::Inst()->window_w = 1024;
				XmlParser::Inst()->window_h = 768;
			}
			break;
		case 2:
			if (buttonText->changeText("1280x720"))
			{
				TTF_SizeText(Main::Inst()->getFont(arial28_bold), "1280x720", &width, &height);
				XmlParser::Inst()->window_w = 1280;
				XmlParser::Inst()->window_h = 720;
			}
			break;
		case 3:
			if (buttonText->changeText("1600x900"))
			{
				TTF_SizeText(Main::Inst()->getFont(arial28_bold), "1600x900", &width, &height);
				XmlParser::Inst()->window_w = 1600;
				XmlParser::Inst()->window_h = 900;
			}
			break;
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
	if (uniqueID == VolumnLButton || uniqueID == VolumnRButton)
	{
		if (CheckMouseOver())
			currentRow = 1;
		else
			currentRow = 0;
		return;
	}
	if (uniqueID == VolumnMasterNumber)
	{
		buttonText->changeText(to_string(XmlParser::Inst()->volumn_master));
	}
	if (uniqueID == VolumnMusicNumber)
	{
		buttonText->changeText(to_string(XmlParser::Inst()->volumn_music));
	}
	if (uniqueID == VolumnSfxNumber)
	{
		buttonText->changeText(to_string(XmlParser::Inst()->volumn_sfx));
	}
	//game menu
	if (uniqueID == ResumeButton || uniqueID == ExittoMainMenuButton || uniqueID == ExittoDestopButton)
	{
		if (CheckMouseOver())
			buttonText->changeColor(COLOR_CLAN);
		else
			buttonText->changeColor(COLOR_WHITE);
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
	if (buttonClass == ButtonTypeTextbox)
		return false;

	if (CheckMouseOver() && Inputor::Inst()->getMouseButtonState(MOUSE_LEFT) && clickCooldown.getTicks() > CLICKCOOLDOWN)
	{
		SoundLoader::Inst()->playSound(MenuMouseClick);
		clickCooldown.start();
		return true;
	}

	return false;
}
#include "Button.h"
#include "Main.h"
#include "World.h"
#include "TextureLoader.h"
#include "SoundLoader.h"
#include "Inputor.h"
#include "Vector2D.h"
#include "XmlParser.h"

#define MAINMENU_X 100
#define MAINMENU_Y Main::Inst()->getWindowHeight()/2
#define NewGamePos				MAINMENU_X,MAINMENU_Y - 80
#define ContinuePos				MAINMENU_X,MAINMENU_Y
#define OptionsPos				MAINMENU_X,MAINMENU_Y + 80
#define ControlSettingsPos		MAINMENU_X,MAINMENU_Y + 160
#define ExitPos					MAINMENU_X,MAINMENU_Y + 240
#define ResolutionTextPos		MAINMENU_X,MAINMENU_Y - 100
#define ResolutionListPos		MAINMENU_X + 200,MAINMENU_Y - 100
#define FullscreenTextPos		MAINMENU_X,MAINMENU_Y - 50
#define FullscreenBoxPos		MAINMENU_X + 200,MAINMENU_Y - 43
#define VolumnLButton1Pos		MAINMENU_X + 225,MAINMENU_Y + 60
#define VolumnLButton2Pos		MAINMENU_X + 225,MAINMENU_Y + 110
#define VolumnLButton3Pos		MAINMENU_X + 225,MAINMENU_Y + 160
#define VolumnRButton1Pos		MAINMENU_X + 290,MAINMENU_Y + 60
#define VolumnRButton2Pos		MAINMENU_X + 290,MAINMENU_Y + 110
#define VolumnRButton3Pos		MAINMENU_X + 290,MAINMENU_Y + 160
#define VolumnMasterTextPos		MAINMENU_X,MAINMENU_Y + 50
#define VolumnMasterNumPos		MAINMENU_X + 245,MAINMENU_Y + 50
#define VolumnMusicTextPos		MAINMENU_X,MAINMENU_Y + 100
#define VolumnMusicNumPos		MAINMENU_X + 245,MAINMENU_Y + 100
#define VolumnSfxTextPos		MAINMENU_X,MAINMENU_Y + 150
#define VolumnSfxNumPos			MAINMENU_X + 245,MAINMENU_Y + 150
#define BackButtonPos			MAINMENU_X,MAINMENU_Y + 200
#define ControlUpTextPos		MAINMENU_X,MAINMENU_Y - 50
#define ControlUpButtonPos		MAINMENU_X + 300,MAINMENU_Y - 50
#define ControlDownTextPos		MAINMENU_X,MAINMENU_Y
#define ControlDownButtonPos	MAINMENU_X + 300,MAINMENU_Y
#define ControlLeftTextPos		MAINMENU_X,MAINMENU_Y + 50
#define ControlLeftButtonPos	MAINMENU_X + 300,MAINMENU_Y + 50
#define ControlRightTextPos		MAINMENU_X,MAINMENU_Y + 100
#define ControlRightButtonPos	MAINMENU_X + 300,MAINMENU_Y + 100

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
	if (uniqueID == MainMenuBackgroundView)
	{
		buttonClass = ButtonTypeBackground;
		position.set(0, 0);
		width = 1920;
		height = 1080;
	}
	if (uniqueID == NewGameButton)
	{
		position.set(NewGamePos);
		buttonText = new Textbox(position, "New Game", arial48_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial48_bold), "New Game", &width, &height);
		return;
	}
	if (uniqueID == ContinueButton)
	{
		position.set(ContinuePos);
		buttonText = new Textbox(position, "Continue", arial48_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial48_bold), "Continue", &width, &height);
		return;

	}
	if (uniqueID == OptionButton)
	{
		position.set(OptionsPos);
		buttonText = new Textbox(position, "Options", arial48_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial48_bold), "Options", &width, &height);
		numFrames = 2;
		return;
	}
	if (uniqueID == ControlSettingsButton)
	{
		position.set(ControlSettingsPos);
		buttonText = new Textbox(position, "Contorl Settings", arial48_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial48_bold), "Contorl Settings", &width, &height);
		numFrames = 2;
		return;
	}
	if (uniqueID == ExitButton)
	{
		position.set(ExitPos);
		buttonText = new Textbox(position, "Exit", arial48_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial48_bold), "Exit", &width, &height);
		return;
	}
	//options menu
	if (uniqueID == OptionsMenuView)
	{
		buttonClass = ButtonTypeBackground;
		position.set(0, 0);
		width = 1920;
		height = 1080;
	}
	if (uniqueID == ResolutionText)
	{
		buttonClass = ButtonTypeTextbox;
		position.set(ResolutionTextPos);
		buttonText = new Textbox(position, "Resolution", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Resolution", &width, &height);
		return;
	}
	if (uniqueID == ResolutionListbox)
	{
		position.set(ResolutionListPos);
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
		position.set(FullscreenTextPos);
		buttonText = new Textbox(position, "Fullscreen", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Fullscreen", &width, &height);
		return;
	}
	if (uniqueID == FullscreenCheckbox)
	{
		position.set(FullscreenBoxPos);
		width = 20;
		height = 20;
		return;
	}
	if (uniqueID == VolumnLButton)
	{
		switch (flag)
		{
		case 0:
			position.set(VolumnLButton1Pos);
			break;
		case 1:
			position.set(VolumnLButton2Pos);
			break;
		case 2:
			position.set(VolumnLButton3Pos);
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
			position.set(VolumnRButton1Pos);
			break;
		case 1:
			position.set(VolumnRButton2Pos);
			break;
		case 2:
			position.set(VolumnRButton3Pos);
			break;
		}
		width = 15;
		height = 20;
	}
	if (uniqueID == VolumnMasterText)
	{
		buttonClass = ButtonTypeTextbox;
		position.set(VolumnMasterTextPos);
		buttonText = new Textbox(position, "Master Volumn", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Master Volumn", &width, &height);
		return;
	}
	if (uniqueID == VolumnMasterNumber)
	{
		buttonClass = ButtonTypeTextbox;
		position.set(VolumnMasterNumPos);
		buttonText = new Textbox(position, to_string(XmlParser::Inst()->volumn_master), arial28_bold, COLOR_WHITE, -1);
	}
	if (uniqueID == VolumnMusicText)
	{
		buttonClass = ButtonTypeTextbox;
		position.set(VolumnMusicTextPos);
		buttonText = new Textbox(position, "Music Volumn", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Master Volumn", &width, &height);
		return;
	}
	if (uniqueID == VolumnMusicNumber)
	{
		buttonClass = ButtonTypeTextbox;
		position.set(VolumnMusicNumPos);
		buttonText = new Textbox(position, to_string(XmlParser::Inst()->volumn_music), arial28_bold, COLOR_WHITE, -1);
	}
	if (uniqueID == VolumnSfxText)
	{
		buttonClass = ButtonTypeTextbox;
		position.set(VolumnSfxTextPos);
		buttonText = new Textbox(position, "Sfx Volumn", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Master Volumn", &width, &height);
		return;
	}
	if (uniqueID == VolumnSfxNumber)
	{
		buttonClass = ButtonTypeTextbox;
		position.set(VolumnSfxNumPos);
		buttonText = new Textbox(position, to_string(XmlParser::Inst()->volumn_sfx), arial28_bold, COLOR_WHITE, -1);
	}
	if (uniqueID == BackButton)
	{
		position.set(BackButtonPos);
		buttonText = new Textbox(position, "Back to the Main Menu", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Back to the Main Menu", &width, &height);
		return;
	}
	//control menu
	if (uniqueID == ControlMovingUpText)
	{
		buttonClass = ButtonTypeTextbox;
		position.set(ControlUpTextPos);
		buttonText = new Textbox(position, "Moving up&interact", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Moving up&interact", &width, &height);
		return;
	}
	if (uniqueID == ControlMovingUpButton)
	{
		position.set(ControlUpButtonPos);
		buttonText = new Textbox(position, ScancodeToString(XmlParser::Inst()->key_movingUp), arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), ScancodeToString(XmlParser::Inst()->key_movingUp).c_str(), &width, &height);
		return;
	}
	if (uniqueID == ControlMovingDownText)
	{
		buttonClass = ButtonTypeTextbox;
		position.set(ControlDownTextPos);
		buttonText = new Textbox(position, "Moving Down", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Moving Down", &width, &height);
		return;
	}
	if (uniqueID == ControlMovingDownButton)
	{
		position.set(ControlDownButtonPos);
		buttonText = new Textbox(position, ScancodeToString(XmlParser::Inst()->key_movingDown), arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), ScancodeToString(XmlParser::Inst()->key_movingDown).c_str(), &width, &height);
		return;
	}
	if (uniqueID == ControlMovingLeftText)
	{
		buttonClass = ButtonTypeTextbox;
		position.set(ControlLeftTextPos);
		buttonText = new Textbox(position, "Moving Left", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Moving Left", &width, &height);
		return;
	}
	if (uniqueID == ControlMovingLeftButton)
	{
		position.set(ControlLeftButtonPos);
		buttonText = new Textbox(position, ScancodeToString(XmlParser::Inst()->key_movingLeft), arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), ScancodeToString(XmlParser::Inst()->key_movingLeft).c_str(), &width, &height);
		return;
	}
	if (uniqueID == ControlMovingRightText)
	{
		buttonClass = ButtonTypeTextbox;
		position.set(ControlRightTextPos);
		buttonText = new Textbox(position, "Moving Right", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Moving Right", &width, &height);
		return;
	}
	if (uniqueID == ControlMovingRightButton)
	{
		position.set(ControlRightButtonPos);
		buttonText = new Textbox(position, ScancodeToString(XmlParser::Inst()->key_movingRight), arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), ScancodeToString(XmlParser::Inst()->key_movingRight).c_str(), &width, &height);
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
	if (uniqueID == NewGameButton || uniqueID == ContinueButton)
	{
		if (CheckMouseOver())
			buttonText->changeColor(COLOR_RED);
		else
			buttonText->changeColor(COLOR_WHITE);
		return;
	}
	if (uniqueID == OptionButton || uniqueID == BackButton || uniqueID == ControlSettingsButton)
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
	//control menu
	if (uniqueID == ControlMovingUpButton || uniqueID == ControlMovingDownButton || uniqueID == ControlMovingLeftButton || uniqueID == ControlMovingRightButton)
	{
		if (CheckMouseOver())
			buttonText->changeColor(COLOR_PURPLE);
		else
			buttonText->changeColor(COLOR_WHITE);
		return;

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
	if (buttonClass == ButtonTypeBackground)
		TextureLoader::Inst()->drawEx2(uniqueID, 0, 0, width, height, Main::Inst()->getWindowWidth(), Main::Inst()->getWindowHeight());
	else if(buttonText == NULL)
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
	if (buttonClass != ButtonTypeButton)
		return false;

	if (CheckMouseOver() && Inputor::Inst()->getMouseButtonState(MOUSE_LEFT) && clickCooldown.getTicks() > CLICKCOOLDOWN)
	{
		SoundLoader::Inst()->playSound(MenuMouseClick);
		clickCooldown.start();
		return true;
	}

	return false;
}
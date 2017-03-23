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
#define NewGamePos						MAINMENU_X,MAINMENU_Y - 80
#define ContinuePos						MAINMENU_X,MAINMENU_Y
#define OptionsPos						MAINMENU_X,MAINMENU_Y + 80
#define ControlSettingsPos				MAINMENU_X,MAINMENU_Y + 160
#define ExitPos							MAINMENU_X,MAINMENU_Y + 240
#define ResolutionTextPos				MAINMENU_X,MAINMENU_Y - 100
#define ResolutionListPos				MAINMENU_X + 200,MAINMENU_Y - 100
#define FullscreenTextPos				MAINMENU_X,MAINMENU_Y - 50
#define FullscreenBoxPos				MAINMENU_X + 200,MAINMENU_Y - 43
#define VolumnLButton1Pos				MAINMENU_X + 225,MAINMENU_Y + 60
#define VolumnLButton2Pos				MAINMENU_X + 225,MAINMENU_Y + 110
#define VolumnLButton3Pos				MAINMENU_X + 225,MAINMENU_Y + 160
#define VolumnRButton1Pos				MAINMENU_X + 290,MAINMENU_Y + 60
#define VolumnRButton2Pos				MAINMENU_X + 290,MAINMENU_Y + 110
#define VolumnRButton3Pos				MAINMENU_X + 290,MAINMENU_Y + 160
#define VolumnMasterTextPos				MAINMENU_X,MAINMENU_Y + 50
#define VolumnMasterNumPos				MAINMENU_X + 245,MAINMENU_Y + 50
#define VolumnMusicTextPos				MAINMENU_X,MAINMENU_Y + 100
#define VolumnMusicNumPos				MAINMENU_X + 245,MAINMENU_Y + 100
#define VolumnSfxTextPos				MAINMENU_X,MAINMENU_Y + 150
#define VolumnSfxNumPos					MAINMENU_X + 245,MAINMENU_Y + 150
#define BackButtonPos					MAINMENU_X,MAINMENU_Y + 250

#define ControlUpTextPos				MAINMENU_X,MAINMENU_Y - 150
#define ControlUpButtonPos				MAINMENU_X + 300,MAINMENU_Y - 150
#define ControlDownTextPos				MAINMENU_X,MAINMENU_Y - 100
#define ControlDownButtonPos			MAINMENU_X + 300,MAINMENU_Y - 100
#define ControlLeftTextPos				MAINMENU_X,MAINMENU_Y - 50
#define ControlLeftButtonPos			MAINMENU_X + 300,MAINMENU_Y - 50
#define ControlRightTextPos				MAINMENU_X,MAINMENU_Y
#define ControlRightButtonPos			MAINMENU_X + 300,MAINMENU_Y
#define ControlCharacterTextPos			MAINMENU_X,MAINMENU_Y + 50
#define ControlCharacterButtonPos		MAINMENU_X + 300,MAINMENU_Y + 50
#define ControlSkillPanelTextPos		MAINMENU_X,MAINMENU_Y + 100
#define ControlSkillPanelButtonPos		MAINMENU_X + 300,MAINMENU_Y + 100
#define ControlInventoryTextPos			MAINMENU_X,MAINMENU_Y + 150
#define ControlInventoryButtonPos		MAINMENU_X + 300,MAINMENU_Y + 150
#define ControlSkillHotkey1TestPos		MAINMENU_X + 400,MAINMENU_Y - 150
#define ControlSkillHotkey1ButtonPos	MAINMENU_X + 650,MAINMENU_Y - 150
#define ControlSkillHotkey2TestPos		MAINMENU_X + 400,MAINMENU_Y - 100
#define ControlSkillHotkey2ButtonPos	MAINMENU_X + 650,MAINMENU_Y - 100
#define ControlSkillHotkey3TestPos		MAINMENU_X + 400,MAINMENU_Y - 50
#define ControlSkillHotkey3ButtonPos	MAINMENU_X + 650,MAINMENU_Y - 50

#define GAMEMENU_X 50
#define GAMEMENU_Y Main::Inst()->getWindowHeight()
#define GameResumeButtonPos				GAMEMENU_X,GAMEMENU_Y - 175
#define GameExittoMenuButtonPos			GAMEMENU_X,GAMEMENU_Y - 125
#define GameExittoDesktopButtonPos		GAMEMENU_X,GAMEMENU_Y - 75
#define GameOverTextPos					(Main::Inst()->getWindowWidth() - width)/2, (Main::Inst()->getWindowHeight() - height)/2

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
		case 1024:
			flag = 0;
			break;
		case 1280:
			flag = 1;
			break;
		case 1600:
			flag = 2;
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
	if (uniqueID == ControlCharacterPanelText)
	{
		buttonClass = ButtonTypeTextbox;
		position.set(ControlCharacterTextPos);
		buttonText = new Textbox(position, "Character Panel", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Character Panel", &width, &height);
		return;
	}
	if (uniqueID == ControlCharacterPanelButton)
	{
		position.set(ControlCharacterButtonPos);
		buttonText = new Textbox(position, ScancodeToString(XmlParser::Inst()->key_openCharacter), arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), ScancodeToString(XmlParser::Inst()->key_openCharacter).c_str(), &width, &height);
		return;
	}
	if (uniqueID == ControlSkillPanelText)
	{
		buttonClass = ButtonTypeTextbox;
		position.set(ControlSkillPanelTextPos);
		buttonText = new Textbox(position, "Skill Panel", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Skill Panel", &width, &height);
		return;
	}
	if (uniqueID == ControlSkillPanelButton)
	{
		position.set(ControlSkillPanelButtonPos);
		buttonText = new Textbox(position, ScancodeToString(XmlParser::Inst()->key_openSkill), arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), ScancodeToString(XmlParser::Inst()->key_openSkill).c_str(), &width, &height);
		return;
	}
	if (uniqueID == ControlInventoryText)
	{
		buttonClass = ButtonTypeTextbox;
		position.set(ControlInventoryTextPos);
		buttonText = new Textbox(position, "Inventory", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Inventory", &width, &height);
		return;
	}
	if (uniqueID == ControlInventoryButton)
	{
		position.set(ControlInventoryButtonPos);
		buttonText = new Textbox(position, ScancodeToString(XmlParser::Inst()->key_openInventory), arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), ScancodeToString(XmlParser::Inst()->key_openInventory).c_str(), &width, &height);
		return;
	}
	if (uniqueID == ControlSkillHotkey1Text)
	{
		buttonClass = ButtonTypeTextbox;
		position.set(ControlSkillHotkey1TestPos);
		buttonText = new Textbox(position, "Skill Hotkey1", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Skill Hotkey1", &width, &height);
		return;
	}
	if (uniqueID == ControlSkillHotkey1Button)
	{
		position.set(ControlSkillHotkey1ButtonPos);
		buttonText = new Textbox(position, ScancodeToString(XmlParser::Inst()->key_skillHotkey1), arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), ScancodeToString(XmlParser::Inst()->key_skillHotkey1).c_str(), &width, &height);
		return;
	}
	if (uniqueID == ControlSkillHotkey2Text)
	{
		buttonClass = ButtonTypeTextbox;
		position.set(ControlSkillHotkey2TestPos);
		buttonText = new Textbox(position, "Skill Hotkey2", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Skill Hotkey2", &width, &height);
		return;
	}
	if (uniqueID == ControlSkillHotkey2Button)
	{
		position.set(ControlSkillHotkey2ButtonPos);
		buttonText = new Textbox(position, ScancodeToString(XmlParser::Inst()->key_skillHotkey2), arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), ScancodeToString(XmlParser::Inst()->key_skillHotkey2).c_str(), &width, &height);
		return;
	}
	if (uniqueID == ControlSkillHotkey3Text)
	{
		buttonClass = ButtonTypeTextbox;
		position.set(ControlSkillHotkey3TestPos);
		buttonText = new Textbox(position, "Skill Hotkey3", arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Skill Hotkey3", &width, &height);
		return;
	}
	if (uniqueID == ControlSkillHotkey3Button)
	{
		position.set(ControlSkillHotkey3ButtonPos);
		buttonText = new Textbox(position, ScancodeToString(XmlParser::Inst()->key_skillHotkey3), arial28_bold, COLOR_WHITE, -1);
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), ScancodeToString(XmlParser::Inst()->key_skillHotkey3).c_str(), &width, &height);
		return;
	}
	//game menu
	if (uniqueID == GameMenuBackground)
	{
		buttonClass = ButtonTypeBackground;
		width = height = 10;
	}
	if (uniqueID == ResumeButton)
	{
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Resume", &width, &height);
		position.set(GameResumeButtonPos);
		buttonText = new Textbox(position, "Resume", arial28_bold, COLOR_WHITE, -1);
		return;
	}
	if (uniqueID == ExittoMainMenuButton)
	{
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Exit to Main Menu", &width, &height);
		position.set(GameExittoMenuButtonPos);
		buttonText = new Textbox(position, "Exit to Main Menu", arial28_bold, COLOR_WHITE, -1);
		return;
	}
	if (uniqueID == ExittoDesktopButton)
	{
		TTF_SizeText(Main::Inst()->getFont(arial28_bold), "Exit to Desktop", &width, &height);
		position.set(GameExittoDesktopButtonPos);
		buttonText = new Textbox(position, "Exit to Desktop", arial28_bold, COLOR_WHITE, -1);
		return;
	}
	if (uniqueID == GameOverText)
	{
		buttonClass = ButtonTypeTextbox;
		TTF_SizeText(Main::Inst()->getFont(arial72_bold), "GAME OVER", &width, &height);
		position.set(GameOverTextPos);
		buttonText = new Textbox(position, "GAME OVER", arial72_bold, COLOR_WHITE, -1);
		return;
	}
	//ui
	if (uniqueID == InventoryCloseButton)
	{
		width = height = 42;
		return;
	}
	if (uniqueID == InventoryArrangeButton)
	{
		width = 38;
		height = 33;
		return;
	}
	if (uniqueID == SkillPanelAddSkillButton || uniqueID == SkillPanelMinusSkillButton)
	{
		width = height = 10;
		return;
	}
}

void Button::update()
{
	//main menu
	if (uniqueID == NewGameButton || uniqueID == ContinueButton)
	{
		if (checkMouseOver())
			buttonText->changeColor(COLOR_RED);
		else
			buttonText->changeColor(COLOR_WHITE);
		return;
	}
	if (uniqueID == OptionButton || uniqueID == BackButton || uniqueID == ControlSettingsButton)
	{
		if (checkMouseOver())
			buttonText->changeColor(COLOR_ORANGE);
		else
			buttonText->changeColor(COLOR_WHITE);
		return;
	}
	if (uniqueID == ExitButton)
	{
		if (checkMouseOver())
			buttonText->changeColor(COLOR_BLUE);
		else
			buttonText->changeColor(COLOR_WHITE);
		return;
	}
	if (uniqueID == ResolutionListbox)
	{
		if (checkMouseOver())
			buttonText->changeColor(COLOR_RED);
		else
			buttonText->changeColor(COLOR_WHITE);

		switch (flag % 3)
		{
		case 0:
			if (buttonText->changeText("1024x768"))
			{
				TTF_SizeText(Main::Inst()->getFont(arial28_bold), "1024x768", &width, &height);
				XmlParser::Inst()->window_w = 1024;
				XmlParser::Inst()->window_h = 768;
			}
			break;
		case 1:
			if (buttonText->changeText("1280x720"))
			{
				TTF_SizeText(Main::Inst()->getFont(arial28_bold), "1280x720", &width, &height);
				XmlParser::Inst()->window_w = 1280;
				XmlParser::Inst()->window_h = 720;
			}
			break;
		case 2:
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
		if (checkMouseOver())
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
		if (checkMouseOver())
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
	if (uniqueID == ControlMovingUpButton || uniqueID == ControlMovingDownButton || uniqueID == ControlMovingLeftButton || uniqueID == ControlMovingRightButton || uniqueID == ControlCharacterPanelButton || uniqueID == ControlSkillPanelButton || uniqueID == ControlInventoryButton)
	{
		if (checkMouseOver())
			buttonText->changeColor(COLOR_PURPLE);
		else
			buttonText->changeColor(COLOR_WHITE);
		return;

	}
	//game menu
	if (uniqueID == ResumeButton || uniqueID == ExittoMainMenuButton || uniqueID == ExittoDesktopButton)
	{
		if (checkMouseOver())
			buttonText->changeColor(COLOR_CLAN);
		else
			buttonText->changeColor(COLOR_WHITE);
		return;
	}
	//ui
	if (uniqueID == InventoryCloseButton || uniqueID == InventoryArrangeButton || uniqueID == SkillPanelAddSkillButton || uniqueID == SkillPanelMinusSkillButton)
	{
		if (checkMouseOver())
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

bool Button::checkMouseOver()
{
	Vector2D mousepos = Inputor::Inst()->getMouseRelativePosition();
	if (mousepos.x <= position.x + width && mousepos.x >= position.x && mousepos.y >= position.y && mousepos.y <= position.y + height)
		return true;
	return false;
}

bool Button::outsideUpdate()
{
	if (buttonClass != ButtonTypeButton)
		return false;

	if (checkMouseOver() && Inputor::Inst()->getMouseButtonState(MOUSE_LEFT) && clickCooldown.getTicks() > CLICKCOOLDOWN)
	{
		SoundLoader::Inst()->playSound(MenuMouseClick);
		clickCooldown.start();
		return true;
	}

	return false;
}
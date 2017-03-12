#include "CharacterPanel.h"
#include "Main.h"
#include "TextureLoader.h"
#include "Inputor.h"
#include "Camera.h"

#define TITLEHEIGHT 53
#define LEVEL_X 97
#define LEVEL_Y 232
#define EXP_X 29
#define EXP_Y 310
#define EXPNEXT_X 291
#define EXPNEXT_Y 310
#define RHAND_X 55
#define RHAND_Y 141
#define LHAND_X 205
#define LHAND_Y 141
#define HELMET_X 130
#define HELMET_Y 68
#define EXPBAR_X 33
#define EXPBAR_Y 296
#define EXPBAR_LENGTH 254.f
#define EXPBAR_HEIGHT 14

CharacterPanel::CharacterPanel() : closeButton(InventoryCloseButton)
{
	uniqueID = CharacterPanelPic;
	Load();
}

void CharacterPanel::Load()
{
	width = 304;
	height = 354;
	position.x = 100;
	position.y = 100;
	rightHandSlot = new InventoryItem(-2);
	leftHandSlot = new InventoryItem(-2);
	helmetSlot = new InventoryItem(-2);
}

void CharacterPanel::update()
{
	Player* player = Camera::Inst()->getTarget_nonConst();
	int length;

	closeButton.setPosition(position.x + 260, position.y + 2);
	closeButton.update();
	if (closeButton.outsideUpdate())
		active = false;

	Vector2D levelpos(position.x + LEVEL_X, position.y + LEVEL_Y);
	levelText = new Textbox(levelpos, to_string(player->level), arial48, { 0,0,0 }, -1);
	Vector2D exppos(position.x + EXP_X, position.y + EXP_Y);
	expText = new Textbox(exppos, to_string(player->exp), segoeui22, { 0,0,0 }, -1);
	TTF_SizeText(Main::Inst()->getFont(segoeui22), to_string(player->expToNextLevel).c_str(), &length, NULL);
	Vector2D expnextpos(position.x + EXPNEXT_X - length, position.y + EXPNEXT_Y);
	expNextText = new Textbox(expnextpos, to_string(player->expToNextLevel), segoeui22, { 0,0,0 }, -1);

	rightHandSlot->setPosition(position.x + RHAND_X, position.y + RHAND_Y);
	leftHandSlot->setPosition(position.x + LHAND_X, position.y + LHAND_Y);
	helmetSlot->setPosition(position.x + HELMET_X, position.y + HELMET_Y);
	rightHandSlot->update();
	leftHandSlot->update();
	helmetSlot->update();
	player->rightHand_equ = rightHandSlot;
	player->leftHand_equ = leftHandSlot;
	player->helmet_equ = helmetSlot;
}

void CharacterPanel::draw()
{
	Player* player = Camera::Inst()->getTarget_nonConst();

	TextureLoader::Inst()->draw(uniqueID, position.x, position.y, width, height);
	TextureLoader::Inst()->draw(ExpBar, position.x + EXPBAR_X, position.y + EXPBAR_Y, player->exp * EXPBAR_LENGTH / player->expToNextLevel, EXPBAR_HEIGHT);
	closeButton.draw();

	levelText->draw();
	expText->draw();
	expNextText->draw();
	delete levelText;
	delete expText;
	delete expNextText;

	rightHandSlot->draw();
	leftHandSlot->draw();
	helmetSlot->draw();
}

bool CharacterPanel::outsideCheckMouseTitle()
{
	Vector2D* mousepos = Inputor::Inst()->getMouseRelativePosition();
	if (mousepos->y <= position.y + TITLEHEIGHT)
		return true;
	return false;
}

bool CharacterPanel::outsideCheckMouseOver()
{
	Vector2D* mousepos = Inputor::Inst()->getMouseRelativePosition();
	if (mousepos->x <= position.x + width && mousepos->x >= position.x && mousepos->y >= position.y && mousepos->y <= position.y + height)
		return true;
	return false;
}
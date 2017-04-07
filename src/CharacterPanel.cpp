#include "CharacterPanel.h"
#include "Main.h"
#include "TextureLoader.h"
#include "Inputor.h"
#include "Camera.h"

#define GRIDSIZE 46
#define TITLEHEIGHT 53
#define CloseButtonpos		position.x + 260,		position.y + 2
#define LevelTextPos		position.x + 97,		position.y + 232
#define ExpTextPos			position.x + 29,		position.y + 310
#define ExpNextTextPos(s)	position.x + 291 - s,	position.y + 310
#define RightHandPos		position.x + 55,		position.y + 141
#define LeftHandPos			position.x + 205,		position.y + 141
#define HelmetPos			position.x + 130,		position.y + 68
#define XPBarPos			position.x + 33,		position.y + 296
#define EXPBAR_LENGTH 254
#define EXPBAR_HEIGHT 14

CharacterPanel::CharacterPanel() : closeButton(InventoryCloseButton), xpBar(CharacterXPBar, EXPBAR_LENGTH, EXPBAR_HEIGHT)
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
	rightHandSlot = new InventoryItem(NULL, NULL, ItemslotTypeRighthand);
	leftHandSlot = new InventoryItem(NULL, NULL, ItemslotTypeLefthand);
	helmetSlot = new InventoryItem(NULL, NULL, ItemslotTypeHelmet);

	levelText = new Textbox(position, "", arial48_bold, { 0,0,0 }, -1);
	expText = new Textbox(position, "", segoeui22, { 0,0,0 }, -1);
	expNextText = new Textbox(position, "", segoeui22, { 0,0,0 }, -1);

}

void CharacterPanel::update()
{
	Player* player = Camera::Inst()->getTarget_nonConst();
	int length;

	closeButton.setPosition(CloseButtonpos);
	closeButton.update();
	if (closeButton.outsideUpdate())
	{
		active = false;
		player->mouseCooldown.start();
	}
	xpBar.setPosition(XPBarPos);
	xpBar.updateTarget(player->exp, player->expToNextLevel);

	if (to_string(player->level) != levelText->text)
		levelText->changeText(to_string(player->level));
	if (to_string(player->exp) != expText->text)
		expText->changeText(to_string(player->exp));
	if (to_string(player->expToNextLevel) != expNextText->text)
		expNextText->changeText(to_string(player->expToNextLevel));
	levelText->setPosition(LevelTextPos);
	expText->setPosition(ExpTextPos);
	TTF_SizeText(Main::Inst()->getFont(segoeui22), to_string(player->expToNextLevel).c_str(), &length, NULL);
	expNextText->setPosition(ExpNextTextPos(length));

	rightHandSlot->setPosition(RightHandPos);
	leftHandSlot->setPosition(LeftHandPos);
	helmetSlot->setPosition(HelmetPos);
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
	closeButton.draw();
	xpBar.draw();

	levelText->draw();
	expText->draw();
	expNextText->draw();

	rightHandSlot->draw();
	leftHandSlot->draw();
	helmetSlot->draw();

	if (rightHandSlot->mouseAbove && rightHandSlot->active && !rightHandSlot->beingPicked)
		rightHandSlot->itemInfoTexts.draw();
	if (leftHandSlot->mouseAbove && leftHandSlot->active && !leftHandSlot->beingPicked)
		leftHandSlot->itemInfoTexts.draw();
	if (helmetSlot->mouseAbove && helmetSlot->active && !helmetSlot->beingPicked)
		helmetSlot->itemInfoTexts.draw();

	if (!rightHandSlot->active) // empty sword icon
		TextureLoader::Inst()->draw(CharacterWeaponSlot, rightHandSlot->position.x, rightHandSlot->position.y, GRIDSIZE, GRIDSIZE);
}

bool CharacterPanel::outsideCheckMouseTitle()
{
	Vector2D mousepos = Inputor::Inst()->getMouseRelativePosition();
	if (mousepos.y <= position.y + TITLEHEIGHT)
		return true;
	return false;
}

bool CharacterPanel::outsideCheckMouseOver()
{
	Vector2D mousepos = Inputor::Inst()->getMouseRelativePosition();
	if (mousepos.x <= position.x + width && mousepos.x >= position.x && mousepos.y >= position.y && mousepos.y <= position.y + height)
		return true;
	return false;
}
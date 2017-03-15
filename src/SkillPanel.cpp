#include "SkillPanel.h"
#include "TextureLoader.h"
#include "Inputor.h"
#include "Camera.h"
#include "Player.h"

#define TITLEHEIGHT 53


SkillPanel::SkillPanel() : closeButton(InventoryCloseButton)
{
	uniqueID = SkillPanelPic;
	Load();
}

void SkillPanel::Load()
{
	width = 304;
	height = 354;
	position.x = 400;
	position.y = 100;
}

void SkillPanel::update()
{
	Player* player = Camera::Inst()->getTarget_nonConst();
	//int length;

	closeButton.setPosition(position.x + 260, position.y + 2);
	closeButton.update();
	if (closeButton.outsideUpdate())
	{
		active = false;
		player->mouseCooldown.start();
	}

}

void SkillPanel::draw()
{
	TextureLoader::Inst()->draw(uniqueID, position.x, position.y, width, height);
	closeButton.draw();
}

bool SkillPanel::outsideCheckMouseTitle()
{
	Vector2D* mousepos = Inputor::Inst()->getMouseRelativePosition();
	if (mousepos->y <= position.y + TITLEHEIGHT)
		return true;
	return false;
}

bool SkillPanel::outsideCheckMouseOver()
{
	Vector2D* mousepos = Inputor::Inst()->getMouseRelativePosition();
	if (mousepos->x <= position.x + width && mousepos->x >= position.x && mousepos->y >= position.y && mousepos->y <= position.y + height)
		return true;
	return false;
}
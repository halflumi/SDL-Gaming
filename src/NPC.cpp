#include "NPC.h"
#include "Main.h"
#include "World.h"
#include "TextureLoader.h"
#include "Inputor.h"
#include "Camera.h"
#include "Dice.h"

#define INTERACTDISTENCE 100

NPC::NPC(int x, int y, string id)
{
	position.x = x;
	position.y = y;
	uniqueID = id;
	Load();
}

void NPC::Load()
{
	clickCooldown = new MyTimer(true);
	if (uniqueID == LeafNPC)
	{
		width = 114;
		height = 80;
		numFrames = 9;
		return;
	}
	if (uniqueID == TestPortal)
	{
		width = 85;
		height = 105;
		numFrames = 14;
		animatedSpeed = 200;
		return;
	}
	if (uniqueID == GhostNPC)
	{
		width = 51;
		height = 43;
		numFrames = 16;
		animatedSpeed = 150;
		return;
	}
}

void NPC::update()
{
	VisiableCheck();

	currentFrame = int(((SDL_GetTicks() / animatedSpeed) % numFrames));

	if (uniqueID == LeafNPC)
	{
		if (checkMouseOver() && CheckPlayerNearby())
		{
			if (Inputor::Inst()->getMouseButtonState(MOUSE_LEFT) && clickCooldown->getTicks() > CLICKCOOLDOWN )
			{
				World::Inst()->newHostile(2000 + Dice::Inst()->rand(500), Dice::Inst()->rand(600, 800), BlackBlock);
			}
			currentRow = 1;
		}
		else
			currentRow = 0;
		return;
	}
	if (uniqueID == GhostNPC)
	{
		if (checkMouseOver() && CheckPlayerNearby())
		{
			if (Inputor::Inst()->getMouseButtonState(MOUSE_LEFT) && clickCooldown->getTicks() > CLICKCOOLDOWN)
			{
				Camera::Inst()->getTarget_nonConst()->dialog = new Dialog();
			}
			currentRow = 1;
		}
		else
			currentRow = 0;
		return;
	}
}

void NPC::draw()
{
	if (visiable)
	{
		TextureLoader::Inst()->drawFrame(uniqueID, position.x - Camera::Inst()->getPosition().x + Main::Inst()->getRenderWidth() / 2, position.y - Camera::Inst()->getPosition().y + Main::Inst()->getRenderHeight() / 2, width, height, currentRow, currentFrame, angle, alpha);
	}
}

bool NPC::checkMouseOver()
{
	Vector2D* mousepos = Inputor::Inst()->getMouseDefinitePosition();
	if (mousepos->x <= position.x + width && mousepos->x >= position.x && mousepos->y >= position.y && mousepos->y <= position.y + height)
		return true;
	return false;
}

bool NPC::CheckPlayerNearby()
{
	Player* player = Camera::Inst()->getTarget_nonConst();
	//if (player->entityCenter.x <= position.x + width + INTERACTDISTENCE && player->entityCenter.x >= position.x - INTERACTDISTENCE && player->entityCenter.y >= position.y - INTERACTDISTENCE && player->entityCenter.y <= position.y + height + INTERACTDISTENCE)
		return true;
	return false;
}
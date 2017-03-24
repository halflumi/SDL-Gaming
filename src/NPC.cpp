#include "NPC.h"
#include "Main.h"
#include "World.h"
#include "TextureLoader.h"
#include "Inputor.h"
#include "Camera.h"
#include "Dice.h"
#include "XmlParser.h"

#define INTERACTDISTENCE 100

NPC::NPC(int id, int x, int y) : clickCooldown(true)
{
	position.x = x;
	position.y = y;
	uniqueID = id;
	Load();
}

void NPC::Load()
{
	messageBox = NULL;
	if (uniqueID == LeafNPC)
	{
		width = 114;
		height = 80;
		numFrames = 9;
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
	if (uniqueID == MapleFlagNPC)
	{
		width = 99;
		height = 177;
		return;
	}
	if (uniqueID == SavePointNPC)
	{
		width = 95;
		height = 208;
		return;
	}
	if (uniqueID == ShopNPC)
	{
		width = 216;
		height = 215;
		return;
	}
}

void NPC::update()
{
	if(messageBox!= NULL && messageBox->active)
		messageBox->update();

	VisiableCheck();

	currentFrame = int(((SDL_GetTicks() / animatedSpeed) % numFrames));

	if (uniqueID == LeafNPC)
	{
		if (checkMouseOver() && CheckPlayerNearby())
		{
			if (Inputor::Inst()->getMouseButtonState(MOUSE_LEFT) && clickCooldown.getTicks() > CLICKCOOLDOWN )
			{
				World::Inst()->newHostile(BlackBlock, 1800 + Dice::Inst()->rand(500), Dice::Inst()->rand(600, 800));
				clickCooldown.start();
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
			if (Inputor::Inst()->getMouseButtonState(MOUSE_LEFT) && clickCooldown.getTicks() > CLICKCOOLDOWN)
			{
				Camera::Inst()->getTarget_nonConst()->dialog = new Dialog();
				clickCooldown.start();
			}
			currentRow = 1;
		}
		else
			currentRow = 0;
		return;
	}
	if (uniqueID == MapleFlagNPC)
	{
		if (checkMouseOver() && CheckPlayerNearby())
		{
			if (Inputor::Inst()->getMouseButtonState(MOUSE_LEFT) && clickCooldown.getTicks() > CLICKCOOLDOWN)
			{
				if (messageBox != NULL)
					delete messageBox;
				if(Dice::Inst()->rand(2))
					messageBox = new Textbox(position, "I'm talking okay?", segoeui22, COLOR_WHITE, 60, true);
				else
					messageBox = new Textbox(position, "I doubt why people always think I'm a flag", segoeui22, COLOR_WHITE, 60, true);
				clickCooldown.start();
			}
			currentRow = 1;
		}
		else
			currentRow = 0;
		return;
	}
	if (uniqueID == SavePointNPC)
	{
		if (checkMouseOver() && CheckPlayerNearby())
		{
			if (Inputor::Inst()->getMouseButtonState(MOUSE_LEFT) && clickCooldown.getTicks() > CLICKCOOLDOWN)
			{
				if (messageBox != NULL)
					delete messageBox;
				messageBox = new Textbox(position, "The game has been saved!", segoeui22, COLOR_WHITE, 60, true);
				XmlParser::Inst()->mapID = World::Inst()->currentMapID;
				XmlParser::Inst()->saveCharacter();
				clickCooldown.start();
			}
			currentRow = 1;
		}
		else
			currentRow = 0;
		return;
	}
	if (uniqueID == ShopNPC)
	{
		if (checkMouseOver() && CheckPlayerNearby())
		{
			if (Inputor::Inst()->getMouseButtonState(MOUSE_LEFT) && clickCooldown.getTicks() > CLICKCOOLDOWN)
			{

				clickCooldown.start();
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
	if (messageBox != NULL && messageBox->active)
		messageBox->draw();
}

bool NPC::checkMouseOver()
{
	Vector2D mousepos = Inputor::Inst()->getMouseDefinitePosition();
	if (mousepos.x <= position.x + width && mousepos.x >= position.x && mousepos.y >= position.y && mousepos.y <= position.y + height)
		return true;
	return false;
}

bool NPC::CheckPlayerNearby()
{
	Player* player = Camera::Inst()->getTarget_nonConst();
	if (player->entityCenter.x <= position.x + width + INTERACTDISTENCE && player->entityCenter.x >= position.x - INTERACTDISTENCE && player->entityCenter.y >= position.y - INTERACTDISTENCE && player->entityCenter.y <= position.y + height + INTERACTDISTENCE)
		return true;
	return false;
}
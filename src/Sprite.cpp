#include "Sprite.h"
#include "Main.h"
#include "TextureLoader.h"
#include "Camera.h"

Sprite::Sprite(int id, int x, int y)
{
	position.x = x;
	position.y = y;
	uniqueID = id;
	Load();
}

void Sprite::Load()
{
	if (uniqueID == WaterMushroomFrame)
	{
		width = 161;
		height = 136;
		numFrames = 14;
		return;
	}
	if (uniqueID == LadderSprite)
	{
		width = 54;
		height = 244;
		return;
	}
	if (uniqueID == MapGate)
	{
		width = 109;
		height = 154;
		return;
	}
	if (uniqueID == MapGate2)
	{
		width = 108;
		height = 154;
		return;
	}
}

void Sprite::update()
{
	VisiableCheck();

	currentFrame = int(((SDL_GetTicks() / animatedSpeed) % numFrames));
}


void Sprite::draw()
{
	if (visiable)
	{
		TextureLoader::Inst()->drawFrame(uniqueID, position.x - Camera::Inst()->getPosition().x + Main::Inst()->getRenderWidth() / 2, position.y - Camera::Inst()->getPosition().y + Main::Inst()->getRenderHeight() / 2, width, height, currentRow, currentFrame, angle, alpha);
	}

}

bool Sprite::outsideCheckPlayerWithin()
{
	Player* player = Camera::Inst()->getTarget_nonConst();
	if (player->entityCenter.x <= position.x + width && player->entityCenter.x >= position.x && player->entityCenter.y >= position.y && player->entityCenter.y <= position.y + height)
		return true;
	return false;
}
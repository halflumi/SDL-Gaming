#include "Sprite.h"
#include "Main.h"
#include "TextureLoader.h"
#include "Camera.h"

Sprite::Sprite(int x, int y, string id)
{
	position.x = x;
	position.y = y;
	uniqueID = id;
}

void Sprite::load()
{
	if (uniqueID == WaterMushroomFrame)
	{
		width = 161;
		height = 136;
		numFrames = 14;
	}
}

void Sprite::update()
{
	if (position.x - Camera::Inst()->getPosition().x < Main::Inst()->getWindowWidth() / 2)
		visiable = true;
	else if (Camera::Inst()->getPosition().x - (position.x + width) < Main::Inst()->getWindowWidth() / 2)
		visiable = true;
	else
		visiable = false;

	currentFrame = int(((SDL_GetTicks() / 250) % numFrames));
}


void Sprite::draw()
{
	if(visiable)
		TextureLoader::Inst()->drawFrame(uniqueID, position.x - Camera::Inst()->getPosition().x + Main::Inst()->getWindowWidth() / 2, position.y, width, height, currentRow, currentFrame, angle, alpha);
}


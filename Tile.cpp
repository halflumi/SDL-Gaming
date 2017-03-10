#include "Tile.h"
#include "Main.h"
#include "IDSheet.h"
#include "TextureLoader.h"
#include "Camera.h"

Tile::Tile(int x, int y, string id)
{
	position.x = x;
	position.y = y;
	uniqueID = id;
	Load();
}

void Tile::Load()
{
	if(uniqueID == Tile01)
	{
		width = 308;
		height = 293;
		return;
	}
	if (uniqueID == Brick)
	{
		width = 47;
		height = 37;
		return;
	}
}

void Tile::update()
{
	VisiableCheck();
}

void Tile::draw()
{
	if(visiable)
		TextureLoader::Inst()->draw(uniqueID, position.x - Camera::Inst()->getPosition().x + Main::Inst()->getRenderWidth() / 2, position.y - Camera::Inst()->getPosition().y + Main::Inst()->getRenderHeight() / 2, width, height);
}
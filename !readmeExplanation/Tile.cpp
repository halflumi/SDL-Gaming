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
	load();
}

void Tile::load()
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
	if (position.x - Camera::Inst()->getPosition().x < Main::Inst()->getWindowWidth() / 2)
		visiable = true;
	else if(Camera::Inst()->getPosition().x - (position.x + width) < Main::Inst()->getWindowWidth() / 2)
		visiable = true;
	else
		visiable = false;
}

void Tile::draw()
{
	if(visiable)
		TextureLoader::Inst()->draw(uniqueID, position.x - Camera::Inst()->getPosition().x + Main::Inst()->getWindowWidth() / 2, position.y, width, height);
}
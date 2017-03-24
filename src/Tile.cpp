#include "Tile.h"
#include "Main.h"
#include "IDSheet.h"
#include "TextureLoader.h"
#include "Camera.h"

Tile::Tile(int id, int x, int y)
{
	position.x = x;
	position.y = y;
	uniqueID = id;
	Load();
}

void Tile::Load()
{
	if (uniqueID == Brick)
	{
		width = 47;
		height = 37;
		return;
	}
	if (uniqueID == Tile01 || uniqueID == Tile02 || uniqueID == Tile03)
	{
		width = 90;
		height = 60;
		return;
	}
	if (uniqueID == Tile04 || uniqueID == Tile05 || uniqueID == Tile06)
	{
		width = 90;
		height = 28;
		return;
	}
	if (uniqueID == Tile07)
	{
		width = 57;
		height = 27;
		return;
	}
	if (uniqueID == Tile08)
	{
		width = 43;
		height = 27;
		return;
	}
	if (uniqueID == Tile09)
	{
		width = 26;
		height = 60;
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
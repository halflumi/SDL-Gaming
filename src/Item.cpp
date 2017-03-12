#include "Item.h"
#include "Main.h"
#include "World.h"
#include "TextureLoader.h"
#include "Inputor.h"
#include "Camera.h"
#include "Dice.h"

Item::Item(int id, int _stack, int x, int y) : stack(_stack)
{
	position.x = x;
	position.y = y;
	uniqueID = id;
	Load();
}

Item::Item(int id, int _stack, int x, int y, float velocity_x, float velocity_y) : stack(_stack)
{
	position.x = x;
	position.y = y;
	velocity.set(velocity_x, velocity_y);
	uniqueID = id;
	Load();
}

void Item::Load()
{
	acceleration.y = GRAVITY;
	maxStack = 1;
	if (uniqueID == WoodenSword)
	{
		width = 40;
		height = 40;
		return;
	}
	if (uniqueID == OrichalcumShortsword)
	{
		width = 38;
		height = 38;
		return;
	}
}

void Item::update()
{
	Entity::update();
	Vector2D newposition = position + velocity;
	if(!CollisionCheck(newposition))
		position += velocity;

	VisiableCheck();

	currentFrame = int(((SDL_GetTicks() / animatedSpeed) % numFrames));
}

void Item::draw()
{
	if (visiable)
	{
		TextureLoader::Inst()->drawFrame(uniqueID, position.x - Camera::Inst()->getPosition().x + Main::Inst()->getRenderWidth() / 2, position.y - Camera::Inst()->getPosition().y + Main::Inst()->getRenderHeight() / 2, width, height, currentRow, currentFrame, angle, alpha);
	}
}

bool Item::CollisionCheck(Vector2D newpos)
{
	int iRight = newpos.x + width;
	int iBottom = newpos.y + height;
	//touch world border
	if (newpos.x < 0)
		return true;
	if (iRight > World::Inst()->getWorldWidth())
		return true;
	if (newpos.y < 0)
		return true;
	if (newpos.y + height > World::Inst()->getWorldHeight())
		return true;

	//touch tile or enemy
	vector<Tile*>& objects = World::Inst()->getLayer_tile();
	int i;
	int len = objects.size();
	for (i = 0; i < len; i++)
	{
		if (iBottom <= objects[i]->getPosition().y)
			continue;
		if (newpos.y >= objects[i]->getPosition().y + objects[i]->getHeight())
			continue;
		if (iRight <= objects[i]->getPosition().x)
			continue;
		if (newpos.x >= objects[i]->getPosition().x + objects[i]->getWidth())
			continue;

		return true;
	}

	return false;
}
#include "Item.h"
#include "Main.h"
#include "World.h"
#include "TextureLoader.h"
#include "Inputor.h"
#include "Camera.h"
#include "Dice.h"

Item::Item(int id, int _stack, int x, int y) : frameTimer(true)
{
	position.set(x, y);
	uniqueID = id;
	stack = _stack;
	Load();
}

Item::Item(int id, int _stack, int x, int y, float velocity_x, float velocity_y) : frameTimer(true)
{
	position.set(x, y);
	velocity.set(velocity_x, velocity_y);
	uniqueID = id;
	stack = _stack;
	Load();
}

void Item::Load()
{
	bumping = false;
	acceleration.y = GRAVITY;
	if (uniqueID == IronDartItem)
	{
		width = 27;
		height = 27;
		return;
	}
	if(uniqueID == CrystalDartItem)
	{
		width = 27;
		height = 27;
		return;
	}
	if (uniqueID == MokbiDartItem)
	{
		width = 28;
		height = 28;
		return;
	}
	if (uniqueID == GoldCoinItem)
	{
		width = 25;
		height = 24;
		numFrames = 4;
		return;
	}
	if (uniqueID == SteelyThrowingKnivesItem)
	{
		width = height = 29;
		return;
	}
}

void Item::update()
{
	Entity::update();
	Vector2D newposition = position + velocity;
	if (!CollisionCheck(newposition))
		position += velocity;
	else
		bumping = true;

	VisiableCheck();

	currentFrame = int(((frameTimer.getTicks() / animatedSpeed) % numFrames));

	///bumping up and down
	if(bumping)
		switch ((frameTimer.getTicks() / 40) % 4)
		{
		case 0:
			position.y += 0.1f;
			break;
		case 1:
		case 2:
			position.y -= 0.1f;
			break;
		case 3:
			position.y += 0.1f;
			break;
		}
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
		if (iBottom <= objects[i]->position.y)
			continue;
		if (newpos.y >= objects[i]->position.y + objects[i]->height)
			continue;
		if (iRight <= objects[i]->position.x)
			continue;
		if (newpos.x >= objects[i]->position.x + objects[i]->width)
			continue;

		return true;
	}

	return false;
}
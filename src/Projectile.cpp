#include "Projectile.h"
#include "IDSheet.h"
#include "Main.h"
#include "World.h"
#include "TextureLoader.h"
#include "SoundLoader.h"
#include "Camera.h"
#include "Dice.h"

#define PI 3.1415926F

Projectile::Projectile(int id, int _worldID, Vector2D pos, float velocity_x, float velocity_y, Entity* _owner, bool gravitational)
{
	position = pos;
	uniqueID = id;
	worldID = _worldID;
	velocity.x = velocity_x;
	velocity.y = velocity_y;
	owner = _owner;
	Load();
}

void Projectile::Load()
{
	if (uniqueID == IchorKnifeProjectile)
	{
		width = 14;
		height = 28;
		
		penetrate = 2;
	}
	if (uniqueID == OrichalcumShortswordProjectile)
	{
		width = 38;
		height = 38;

		penetrate = -1;
	}
	if (uniqueID == PurificationBulletProjectile)
	{
		width = 2;
		height = 20;

		penetrate = -1;
	}
	if (uniqueID == ChlorophyteTrackerProjectile)
	{
		width = 32;
		height = 32;

		penetrate = 1;
	}
}

void Projectile::update()
{
	Entity::update();

	Vector2D newposition = position + velocity;
	if (CollisionCheck_tile(newposition))
	{
		Kill();
		SoundLoader::Inst()->playSound(CollisionSound);
		return;
	}
	else
		position = newposition;

	if (CollisionCheck_entity(newposition))
	{
		Kill();
		return;
	}

	VisiableCheck();

	if (uniqueID == IchorKnifeProjectile)
	{
		if (life <= 40)
			angle = atan2(velocity.y, velocity.x) * 180.F / PI + 90.F;
		else
		{
			acceleration.y = GRAVITY;
			angle += velocity.x * 2.f;
		}
		if (life > 300)
			Kill();
		life++;
		return;
	}
	if (uniqueID == OrichalcumShortswordProjectile)
	{
		if (velocity.x > 0)
			angle = 45;
		else
			angle = 225;
		if (life > 120)
			Kill();
		life++;
		return;
	}
	if (uniqueID == PurificationBulletProjectile)
	{
		angle = atan2(velocity.y, velocity.x) * 180.F / PI + 90.F;
		if (life > 300)
			Kill();
		life++;
		return;
	}
	if (uniqueID == ChlorophyteTrackerProjectile)
	{
		angle = atan2(velocity.y, velocity.x) * 180.F / PI + 45.F;
		if (life > 60)
			acceleration.y = GRAVITY;
		if (life > 300)
			Kill();
		life++;
		return;
	}
}

void Projectile::Kill()
{
	active = false;
	dead = true;
}

void Projectile::draw()
{
	if(visiable)
		TextureLoader::Inst()->drawFrame(uniqueID, position.x - Camera::Inst()->getPosition().x + Main::Inst()->getRenderWidth() / 2, position.y - Camera::Inst()->getPosition().y + Main::Inst()->getRenderHeight() / 2, width, height, currentRow, currentFrame, angle, alpha);
}

bool Projectile::CollisionCheck_tile(Vector2D newpos)
{
	int pRight = newpos.x + width;
	int pBottom = newpos.y + height;
	//touch world border
	if (newpos.x < 0)
		return true;
	if (pRight > World::Inst()->getWorldWidth())
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
		if (pBottom <= objects[i]->getPosition().y)
			continue;
		if (newpos.y >= objects[i]->getPosition().y + objects[i]->getHeight())
			continue;
		if (pRight <= objects[i]->getPosition().x)
			continue;
		if (newpos.x >= objects[i]->getPosition().x + objects[i]->getWidth())
			continue;

		return true;
	}

	return false;
}

bool Projectile::CollisionCheck_entity(Vector2D newpos)
{
	int pRight = newpos.x + width;
	int pBottom = newpos.y + height;

	vector<Entity*>& entities = World::Inst()->getLayer_entity();
	int i;
	int len = entities.size();
	bool attacked;
	for (i = 0; i < len; i++)
	{
		if (entities[i]->type() != TypeHostile)
			continue;
		if (!entities[i]->active)
			continue;
		attacked = false;
		for (auto it = attackedTargets.begin(); it != attackedTargets.end(); it++)
			if (*it == entities[i]->worldID)
			{
				attacked = true;
				break;
			}
		if (attacked)
			continue;

		if (pBottom <= entities[i]->getPosition().y)
			continue;
		if (newpos.y >= entities[i]->getPosition().y + entities[i]->getHeight())
			continue;
		if (pRight <= entities[i]->getPosition().x)
			continue;
		if (newpos.x >= entities[i]->getPosition().x + entities[i]->getWidth())
			continue;

		attackedTargets.push_back(entities[i]->worldID);
		entities[i]->onHit(Dice::Inst()->rand(owner->minATT, owner->maxATT), owner->critChance);
		owner->heal(1);
		penetrate--;
		if(penetrate == 0)
			return true;
	}
	return false;
}
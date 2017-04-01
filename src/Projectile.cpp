#include "Projectile.h"
#include "IDSheet.h"
#include "Main.h"
#include "World.h"
#include "TextureLoader.h"
#include "SoundLoader.h"
#include "Camera.h"
#include "Dice.h"
#include "Hostile.h"

#define PI 3.1415926F

Projectile::Projectile(int id, int _worldID, Vector2D pos, float velocity_x, float velocity_y, int _minATT, int _maxATT, int _critChance, bool _friendly, bool gravitational)
{
	friendly = _friendly;
	position = pos;
	uniqueID = id;
	worldID = _worldID;
	velocity.set(velocity_x,velocity_y);
	minATT = _minATT;
	maxATT = _maxATT;
	critChance = _critChance;
	Load();
}

void Projectile::Load()
{
	penetrate = 1;

	///darts
	if (uniqueID == SubiDartProjectile)
	{
		width = 19;
		height = 19;
		numFrames = 2;
		return;
	}
	if (uniqueID == IronDartProjectile)
	{
		width = 19;
		height = 20;
		numFrames = 2;
		return;
	}
	if (uniqueID == CrystalDartProjectile)
	{
		width = 27;
		height = 27;
		numFrames = 2;
		return;
	}
	if (uniqueID == MokbiDartProjectile)
	{
		width = 23;
		height = 22;
		numFrames = 2;
		penetrate = 2;
		return;
	}
	if (uniqueID == SteelyThrowingKnivesProjectile)
	{
		width = 48;
		height = 9;
		numFrames = 2;
		penetrate = 2;
		return;
	}
	///skill effects
	if (uniqueID == SummonMagicProjectile)
	{
		width = 120;
		height = 20;
		penetrate = -1;
		return;
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
	currentFrame = int(((frameTimer.getTicks() / animatedSpeed) % numFrames));

	///darts
	if (uniqueID == SubiDartProjectile)
	{
		angle += 10.F;
		if (life > 60)
			acceleration.y = GRAVITY;
		if (life > 300)
			Kill();
		life++;
		return;
	}
	if (uniqueID == IronDartProjectile)
	{
		angle += 10.F;
		if (life > 60)
			acceleration.y = GRAVITY;
		if (life > 300)
			Kill();
		life++;
		return;
	}
	if (uniqueID == CrystalDartProjectile)
	{
		angle += 10.F;
		if (life > 60)
			acceleration.y = GRAVITY;
		if (life > 300)
			Kill();
		life++;
		return;
	}
	if (uniqueID == MokbiDartProjectile)
	{
		angle += 10.F;
		if (life > 60)
			acceleration.y = GRAVITY;
		if (life > 300)
			Kill();
		life++;
		return;
	}
	if (uniqueID == SteelyThrowingKnivesProjectile)
	{
		angle = atan2(velocity.y, velocity.x) * 180.F / PI + 180.F;
		if (life > 120)
			acceleration.y = GRAVITY;
		if (life > 300)
			Kill();
		life++;
		return;
	}
	///skill effects
	if (uniqueID == SummonMagicProjectile)
	{
		if (life > 15)
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
		if (pBottom <= objects[i]->position.y)
			continue;
		if (newpos.y >= objects[i]->position.y + objects[i]->height)
			continue;
		if (pRight <= objects[i]->position.x)
			continue;
		if (newpos.x >= objects[i]->position.x + objects[i]->width)
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
	Hostile* mob;
	int i;
	int len = entities.size();
	bool attacked;
	for (i = 0; i < len; i++)
	{
		if (entities[i]->type() != TypeHostile)
			continue;
		if (!entities[i]->active || entities[i]->friendly == friendly)
			continue;
		mob = (Hostile*)entities[i];
		attacked = false;
		for (auto it = attackedTargets.begin(); it != attackedTargets.end(); it++)
			if (*it == mob->worldID)
			{
				attacked = true;
				break;
			}
		if (attacked)
			continue;

		if (pBottom <= mob->position.y)
			continue;
		if (newpos.y >= mob->position.y + mob->height)
			continue;
		if (pRight <= mob->position.x)
			continue;
		if (newpos.x >= mob->position.x + mob->width)
			continue;
		//cout << uniqueID << ' ' << friendly << endl;

		attackedTargets.push_back(mob->worldID);
		mob->onHit(Dice::Inst()->rand(minATT, maxATT), Dice::Inst()->rand(100) < critChance);
		penetrate--;
		if(penetrate == 0)
			return true;
	}
	return false;
}
#include "Hostile.h"
#include "Main.h"
#include "World.h"
#include "Camera.h"
#include "TextureLoader.h"
#include "SoundLoader.h"
#include "Inputor.h"
#include "Dice.h"

#define DAMAGETICK 10
#define MIDAIR 1
#define PLAYERACCERLATION 0.7f

Hostile::Hostile(int id, int _worldID, int x, int y) : timer(true)
{
	position.x = x;
	position.y = y;
	uniqueID = id;
	worldID = _worldID;
	Load();
}

void Hostile::Load()
{
	color = COLOR_WHITE;
	damageTick = 0;
	midair = false;
	stasis = false;
	if (uniqueID == BlackBlock)
	{
		width = 80;
		height = 80;

		stasis = true;
		level = 1;
		exp = 5;
		life = 100;
		minATT = 10;
		maxATT = 20;
		defense = 2;
		return;
	}
	if (uniqueID == DemonHostile)
	{
		width = 177;
		height = 163;
		numFrames = 4;

		maxSpeed = 2.f;
		acceleration.y = GRAVITY;
		level = 1;
		exp = 20;
		life = 300;
		minATT = 20;
		maxATT = 40;
		defense = 5;
		return;
	}
	if (uniqueID == HostileGhostMob)
	{
		width = 71;
		height = 64;
		numFrames = 3;

		maxSpeed = 2.f;
		acceleration.y = GRAVITY;
		level = 1;
		exp = 20;
		life = 300;
		minATT = 20;
		maxATT = 40;
		defense = 5;
		return;
	}
	if (uniqueID == HostileSkeleton)
	{
		width = 84;
		height = 95;
		numFrames = 4;
		animatedSpeed = 350;

		maxSpeed = 1.f;
		acceleration.y = GRAVITY;
		level = 1;
		exp = 20;
		life = 300;
		minATT = 20;
		maxATT = 40;
		defense = 5;
		return;
	}
	if (uniqueID == HostileWoodMob)
	{
		width = 74;
		height = 77;
		numFrames = 4;
		animatedSpeed = 350;

		maxSpeed = 1.f;
		acceleration.y = GRAVITY;
		level = 1;
		exp = 20;
		life = 300;
		minATT = 20;
		maxATT = 40;
		defense = 5;
		return;
	}
	if (uniqueID == HostileGiantCat)
	{
		width = 165;
		height = 96;
		numFrames = 5;
		animatedSpeed = 150;

		maxSpeed = 4.f;
		acceleration.y = GRAVITY;
		level = 1;
		exp = 20;
		life = 300;
		minATT = 20;
		maxATT = 40;
		defense = 5;
		return;
	}
}

void Hostile::update()
{
	Entity::update();
	VisiableCheck();

	if (active)
	{
		///update living mob
		if (!stasis)
		{
			MovingAI();

			if (movingLeft || movingRight)
				currentFrame = int(((timer.getTicks() / animatedSpeed) % numFrames));
			else
				currentFrame = 0;
		}
		///death check
		if (life <= 0)
		{
			kill();
			return;
		}
		///damage updating
		if (damageTick)
			damageTick--;
		else
		{
			color = COLOR_WHITE;
			currentFrame = int((timer.getTicks() / animatedSpeed) % numFrames);
		}
	}
	///dying
	else
	{
		if (alpha <= 0)
		{
			dead = true;
			return;
		}
		alpha -= 10;
	}
}

void Hostile::MovingAI()
{
	int player_x = Camera::Inst()->getTarget_nonConst()->getPosition().x;
	if (position.x < player_x)
	{
		movingRight = true;
		movingLeft = false;
	}
	else
	{
		movingRight = false;
		movingLeft = true;
	}
	//calculate speed
	if (!midair)
	{
		if (movingLeft)
		{
			currentRow = 0;
			acceleration.x = -PLAYERACCERLATION;
			if (velocity.x > 0) //turn around from right
				velocity.x = 0;
		}
		else if (movingRight)
		{
			currentRow = 1;
			acceleration.x = PLAYERACCERLATION;
			if (velocity.x < 0) //turn around from left
				velocity.x = 0;
		}
		else
		{
			velocity.x = 0;
			acceleration.x = 0;
		}
	}
	//calculate position
	Vector2D newposition = position + velocity;

	if (!CheckCollision_tileX(newposition.x)) {
		position.x = newposition.x;
	}
	if (!CheckCollision_tileY(newposition.y)) {
		position.y = newposition.y;
	}
}

bool Hostile::CheckCollision_tileX(float& x)
{
	//touch world border
	if (x < 0)
	{
		position.x = 0;
		return true;
	}
	if (x + width > World::Inst()->getWorldWidth())
	{
		position.x = World::Inst()->getWorldWidth() - width;
		return true;
	}

	//touch tile or enemy
	vector<Tile*>& objects = World::Inst()->getLayer_tile();
	int i;
	int len = objects.size();
	for (i = 0; i < len; i++)
	{
		if (objects[i]->type() != TypeTile)
			continue;

		float& objectLeft = objects[i]->getPosition().x;
		float objectRight = objectLeft + objects[i]->getWidth();
		float& objectTop = objects[i]->getPosition().y;
		float objectBottom = objectTop + objects[i]->getHeight();


		if (!(position.y >= objectBottom || position.y + height <= objectTop))
		{
			if (x + width <= objectLeft || x >= objectRight)
				continue;
			else if (x + width >= objectLeft && position.x + width <= objectLeft)
			{
				position.x = objectLeft - width;
				velocity.x = 0;
				acceleration.x = 0;
				return true;
			}
			else if (x <= objectRight && position.x >= objectRight)
			{
				position.x = objectRight;
				velocity.x = 0;
				acceleration.x = 0;
				return true;
			}
		}
	}
	//cout << position.x << endl;
	return false;
}

bool Hostile::CheckCollision_tileY(float& y)
{
	if (y < 0)
	{
		position.y = 0;
		return true;
	}
	if (y + height >= World::Inst()->getWorldHeight())
	{
		position.y = World::Inst()->getWorldHeight() - height;
		HitGround();
		return true;
	}
	//touch tile or enemy
	vector<Tile*>& objects = World::Inst()->getLayer_tile();
	int i;
	int len = objects.size();
	for (i = 0; i < len; i++)
	{
		if (objects[i]->type() != TypeTile)
			continue;

		float& objectLeft = objects[i]->getPosition().x;
		float objectRight = objectLeft + objects[i]->getWidth();
		float& objectTop = objects[i]->getPosition().y;
		float objectBottom = objectTop + objects[i]->getHeight();

		if (!(position.x + width <= objectLeft || position.x >= objectRight))
		{
			if (y >= objectBottom || y + height <= objectTop)
			{
				continue;
			}
			else {
				if (y + height >= objectTop && position.y + height <= objectTop)
				{
					position.y = objectTop - height;
					HitGround();
					return true;
				}
				else if (y <= objectBottom && position.y >= objectBottom) {
					position.y = objectBottom + 1;
					velocity.y = -velocity.y * 0.6;
					return true;
				}
			}
		}
	}
	midair = MIDAIR;
	return false;
}

void Hostile::HitGround()
{
	midair = false;
	velocity.y = 0;
	acceleration.y = 0;
	maxSpeed = maxSpeed;
}

void Hostile::draw()
{
	if (visiable)
	{
		TextureLoader::Inst()->drawFrameSp(uniqueID, position.x - Camera::Inst()->getPosition().x + Main::Inst()->getRenderWidth() / 2, position.y - Camera::Inst()->getPosition().y + Main::Inst()->getRenderHeight() / 2, width, height, currentRow, currentFrame, angle, alpha, color);
	}
}

void Hostile::kill()
{
	active = false;
	timer.start();
	Camera::Inst()->getTarget_nonConst()->exp += exp;
	if (uniqueID == BlackBlock)
	{
		SoundLoader::Inst()->playSound(DeathSound);
		if (Dice::Inst()->rand(3) == 0)
			World::Inst()->newItem(IronDartItem, 1, position.x + width / 2, position.y + height / 2);
		if (Dice::Inst()->rand(3) == 0)
			World::Inst()->newItem(CrystalDartItem, 1, position.x + width / 2, position.y + height / 2);
		if (Dice::Inst()->rand(3) == 0)
			World::Inst()->newItem(MokbiDartItem, 1, position.x + width / 2, position.y + height / 2);
		return;
	}
	if (uniqueID == DemonHostile)
		SoundLoader::Inst()->playSound(DemonDeathSound);
	else if (uniqueID == HostileGhostMob)
		SoundLoader::Inst()->playSound(DemonDeathSound);
	else if (uniqueID == HostileSkeleton)
		SoundLoader::Inst()->playSound(DemonDeathSound);
	else if (uniqueID == HostileWoodMob)
		SoundLoader::Inst()->playSound(DemonDeathSound);
	else if (uniqueID == HostileGiantCat)
		SoundLoader::Inst()->playSound(DemonDeathSound);

	color = COLOR_WHITE;
}

void Hostile::onHit(int damage, int critChance)
{
	int actualDamage;
	if (Dice::Inst()->rand(100) < critChance)
	{
		actualDamage = 2 * (damage - defense);
		//minimum damage protect
		if (actualDamage < 2)
			actualDamage = 2;
		life -= actualDamage;

		Vector2D textShift(entityCenter.x + Dice::Inst()->randInverse(20), position.y + Dice::Inst()->randInverse(20));
		World::Inst()->createText(textShift, 0, -0.1f, to_string(actualDamage) + "!", segoeui28, COLOR_RED, 60);
	}
	else
	{
		actualDamage = damage - defense;
		//minimum damage protect
		if (actualDamage < 1)
			actualDamage = 1;
		life -= actualDamage;

		Vector2D textShift(entityCenter.x + Dice::Inst()->randInverse(20), position.y + Dice::Inst()->randInverse(20));
		World::Inst()->createText(textShift, 0, -0.1f, to_string(actualDamage), segoeui22, COLOR_WHITE, 60);
	}
	if (uniqueID == BlackBlock)
		SoundLoader::Inst()->playSound(DamageSound);
	else if (uniqueID == DemonHostile)
	{
		SoundLoader::Inst()->playSound(DemonDamageSound);
	}
	else if (uniqueID == HostileGhostMob)
	{
		SoundLoader::Inst()->playSound(DemonDamageSound);
	}
	else if (uniqueID == HostileSkeleton)
	{
		SoundLoader::Inst()->playSound(DemonDamageSound);
	}
	else if (uniqueID == HostileWoodMob)
	{
		SoundLoader::Inst()->playSound(DemonDamageSound);
	}
	else if (uniqueID == HostileGiantCat)
	{
		SoundLoader::Inst()->playSound(DemonDamageSound);
	}
	color = COLOR_RED;
	damageTick = DAMAGETICK;
}
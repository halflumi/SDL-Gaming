#include "Hostile.h"
#include "Main.h"
#include "World.h"
#include "Camera.h"
#include "TextureLoader.h"
#include "SoundLoader.h"
#include "Inputor.h"
#include "Dice.h"

#define DAMAGETICK 15
#define MIDAIR 1
#define SPEED_SLOW 1.5f
#define SPEED_MEDIUM 3.f
#define SPEED_FAST 6.f
#define MOBMOVINGACCELERATION 0.7f
#define KNOCKBACKSPEED 2.f
#define KNOCKBACKACCELERATION 0.2f

Hostile::Hostile(int id, int _worldID, int x, int y) : frameTimer(true)
{
	position.x = x;
	position.y = y;
	uniqueID = id;
	worldID = _worldID;
	Load();
}

void Hostile::Load()
{
	friendly = false;
	damageTick = 0;
	ai[0] = 0;
	ai[1] = 0;
	ai[2] = 0;
	ai[3] = 0;
	ai[4] = 0;
	midair = false;
	stasis = false;
	if (uniqueID == BlackBlock)
	{
		width = 80;
		height = 80;
		damageSoundID = DamageSound;
		dieSoundID = DeathSound;

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
		height = 170;
		numFrames = 5;
		damageSoundID = DemonDamageSound;
		dieSoundID = DemonDieSound;

		maxSpeed = SPEED_SLOW;
		acceleration.y = GRAVITY;
		level = 5;
		exp = 100;
		life = 500;
		minATT = 45;
		maxATT = 55;
		defense = 10;
		return;
	}
	if (uniqueID == HostileGhostMob)
	{
		width = 70;
		height = 63;
		numFrames = 3;
		damageSoundID = GhostMobDamageSound;
		dieSoundID = GhostMobDieSound;

		maxSpeed = SPEED_MEDIUM;
		acceleration.y = GRAVITY;
		level = 4;
		exp = 75;
		life = 300;
		minATT = 35;
		maxATT = 45;
		defense = 5;
		return;
	}
	if (uniqueID == HostileSkeleton)
	{
		width = 84;
		height = 95;
		numFrames = 4;
		animatedSpeed = 20;
		damageSoundID = SkeletonDamageSound;
		dieSoundID = SkeletonDieSound;

		maxSpeed = SPEED_MEDIUM;
		acceleration.y = GRAVITY;
		level = 2;
		exp = 20;
		life = 150;
		minATT = 20;
		maxATT = 40;
		defense = 2;
		return;
	}
	if (uniqueID == HostileWoodMob)
	{
		width = 74;
		height = 77;
		numFrames = 4;
		animatedSpeed = 20;
		damageSoundID = WoodMobDamageSound;
		dieSoundID = WoodMobDieSound;

		maxSpeed = SPEED_SLOW;
		acceleration.y = GRAVITY;
		level = 1;
		exp = 10;
		life = 50;
		minATT = 5;
		maxATT = 15;
		defense = 1;
		return;
	}
	if (uniqueID == HostileGiantCat)
	{
		width = 165;
		height = 96;
		numFrames = 5;
		animatedSpeed = 6;
		damageSoundID = GiantCatDamageSound;
		dieSoundID = GiantCatDieSound;

		maxSpeed = SPEED_FAST;
		acceleration.y = GRAVITY;
		level = 3;
		exp = 50;
		life = 100;
		minATT = 35;
		maxATT = 45;
		defense = 0;
		return;
	}
	if (uniqueID == HostilePigNPC)
	{
		friendly = true;
		width = 69;
		height = 50;
		numFrames = 3;
		damageSoundID = PigDamageSound;
		dieSoundID = PigDieSound;

		maxSpeed = 3.f;
		acceleration.y = GRAVITY;
		level = 1;
		exp = 20;
		life = 10;
		minATT = 20;
		maxATT = 40;
		defense = 5;

		ai[1] = 1;
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
			if (damageTick == 0)
			{
				///moving behaviors
				MovingAI();
				///moving frame
				if (movingLeft || movingRight)
					currentFrame = int(((frameTimer.getTicks() / animatedSpeed) % numFrames));
				else
					currentFrame = 0;
			}
			else
			{
				currentFrame = 0;
				frameTimer.start();
			}
			///calculate position
			Vector2D newposition = position + velocity;

			if (!CheckCollision_tileX(newposition.x)) {
				position.x = newposition.x;
			}
			if (!CheckCollision_tileY(newposition.y)) {
				position.y = newposition.y;
			}

			if (friendly) // currently only friend npc can be hit by objects other than player
			{
				CheckCollision_hostile(newposition);
				//invulnerable tick
				if (invulnerableTick)
				{
					invulnerableTick++;
					if (invulnerableTick == invulnerableInterval)
						invulnerableTick = 0;
					if (invulnerableTick % 5 == 0)
					{
						if (alpha == 255)
							alpha = 50;
						else
							alpha = 255;
					}
				}
				else
					alpha = 255;
			}
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
	int player_x = Camera::Inst()->getTarget_nonConst()->position.x;
	acceleration.y = GRAVITY;
	if (!friendly)
	{
		if (position.x < player_x)
		{
			movingRight = true;
			movingLeft = false;
		}
		else if(position.x > player_x)
		{
			movingRight = false;
			movingLeft = true;
		}
		else
		{
			movingRight = false;
			movingLeft = false;
		}
	}
	else
	{
		if (!(movingLeft || movingRight)) {
			movingLeft = true;
			movingRight = false;
		}
		static int start = SDL_GetTicks();
		if (SDL_GetTicks() - start > 2000) {
			swap(movingLeft, movingRight);
			velocity.x *= -1;
			start = SDL_GetTicks();
		}

	}
	if (!midair)
	{
		if (movingLeft)
		{
			currentRow = 0;
			acceleration.x = -MOBMOVINGACCELERATION;
			if (velocity.x > 0) //turn around from right
				velocity.x = 0;
		}
		else if (movingRight)
		{
			currentRow = 1;
			acceleration.x = MOBMOVINGACCELERATION;
			if (velocity.x < 0) //turn around from left
				velocity.x = 0;
		}
		else
		{
			velocity.x = 0;
			acceleration.x = 0;
		}
	}
}

void Hostile::KnockBack()
{
	currentRow += 2;
	if (velocity.x > 0)
	{
		velocity.x = -KNOCKBACKSPEED - Dice::Inst()->rand(100) / 100.f;
		acceleration.x = -KNOCKBACKACCELERATION;
	}
	else
	{
		velocity.x = KNOCKBACKSPEED + Dice::Inst()->rand(100) / 100.f;
		acceleration.x = KNOCKBACKACCELERATION;
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

		float& objectLeft = objects[i]->position.x;
		float objectRight = objectLeft + objects[i]->width;
		float& objectTop = objects[i]->position.y;
		float objectBottom = objectTop + objects[i]->height;


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

		float& objectLeft = objects[i]->position.x;
		float objectRight = objectLeft + objects[i]->width;
		float& objectTop = objects[i]->position.y;
		float objectBottom = objectTop + objects[i]->height;

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

void Hostile::CheckCollision_hostile(Vector2D newpos)
{
	if (invulnerableTick > 0)
		return;
	int pRight = newpos.x + width;
	int pBottom = newpos.y + height;

	vector<Entity*>& entities = World::Inst()->getLayer_entity();
	int i;
	int len = entities.size();
	for (i = 0; i < len; i++)
	{
		if (entities[i]->type() != TypeHostile)
			continue;
		if (!entities[i]->active || entities[i]->friendly)
			continue;

		if (pBottom <= entities[i]->position.y)
			continue;
		if (newpos.y >= entities[i]->position.y + entities[i]->height)
			continue;
		if (pRight <= entities[i]->position.x)
			continue;
		if (newpos.x >= entities[i]->position.x + entities[i]->width)
			continue;

		//onhit
		SoundLoader::Inst()->playSound(PlayerDamageSound);
		int damage = Dice::Inst()->rand(entities[i]->minATT, entities[i]->maxATT) - defense;
		life -= damage;
		Vector2D textShift(entityCenter.x + Dice::Inst()->randInverse(20), position.y + Dice::Inst()->randInverse(20));
		World::Inst()->createText(textShift, 0, -0.1f, to_string(damage), segoeui22, COLOR_RED, 60);
		velocity.y = -10.f;
		//acceleration.y = -GRAVITY;
		if (entities[i]->position.x > position.x) {
			velocity.x = -5.f;
			acceleration.x = 0;
		}
		else {
			velocity.x = 5.f;
			acceleration.x = 0;
		}
		invulnerableTick = 1;
		return;
	}
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
		TextureLoader::Inst()->drawFrame(uniqueID, position.x - Camera::Inst()->getPosition().x + Main::Inst()->getRenderWidth() / 2, position.y - Camera::Inst()->getPosition().y + Main::Inst()->getRenderHeight() / 2, width, height, currentRow, currentFrame, angle, alpha);
	}
}

void Hostile::kill()
{
	active = false;
	currentFrame = 0;
	if(Camera::Inst( )->getTarget_nonConst( )->level < MAXLEVEL)
		Camera::Inst()->getTarget_nonConst()->exp += exp;

	///drop
	World::Inst()->newItem(GoldCoinItem, Dice::Inst()->rand(100), entityCenter.x + Dice::Inst()->randInverse(20), entityCenter.y);
	if (Dice::Inst()->rand(10) == 0)
		World::Inst()->newItem(IronDartItem, 1, entityCenter.x + Dice::Inst()->randInverse(20), entityCenter.y);
	else if (Dice::Inst()->rand(15) == 0)
		World::Inst()->newItem(CrystalDartItem, 1, entityCenter.x + Dice::Inst()->randInverse(20), entityCenter.y);
	else if (Dice::Inst()->rand(25) == 0)
		World::Inst()->newItem(MokbiDartItem, 1, entityCenter.x + Dice::Inst()->randInverse(20), entityCenter.y);
	else if (Dice::Inst()->rand(25) == 0)
		World::Inst()->newItem(SteelyThrowingKnivesItem, 1, entityCenter.x + Dice::Inst()->randInverse(20), entityCenter.y);

	SoundLoader::Inst()->playSound(dieSoundID);

	if (uniqueID == HostilePigNPC)
	{
		Main::Inst()->changeMenu(MenuGameOver);
	}
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
		World::Inst()->createText(textShift, 0, -0.15f, to_string(actualDamage) + "!", segoeui28, COLOR_RED, 60);
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
	SoundLoader::Inst()->playSound(damageSoundID);
	//color = COLOR_RED;
	if(damageTick == 0)
		damageTick = DAMAGETICK;

	if (!stasis)
	{
		movingLeft = movingRight = false;
		KnockBack();
	}
}
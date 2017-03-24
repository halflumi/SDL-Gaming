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
	friendly = false;
	color = COLOR_WHITE;
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
		height = 163;
		numFrames = 4;
		damageSoundID = DemonDamageSound;
		dieSoundID = DemonDieSound;

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
		damageSoundID = GhostMobDamageSound;
		dieSoundID = GhostMobDieSound;

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
		damageSoundID = SkeletonDamageSound;
		dieSoundID = SkeletonDieSound;

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
		damageSoundID = WoodMobDamageSound;
		dieSoundID = WoodMobDieSound;

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
		damageSoundID = GiantCatDamageSound;
		dieSoundID = GiantCatDieSound;

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
	if (uniqueID == HostilePigNPC)
	{
		friendly = true;
		width = 69;
		height = 50;
		numFrames = 3;
		animatedSpeed = 250;
		damageSoundID = PigDamageSound;
		dieSoundID = PigDieSound;

		maxSpeed = 3.f;
		acceleration.y = GRAVITY;
		level = 1;
		exp = 20;
		life = 300;
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
	if (!friendly)
	{
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
	}
	else
	{
		if (ai[0] > 0)
		{
			ai[0]--;
			//cout << ai[0] << ' ';
			if (ai[1] == 1)
				currentRow = 2;
			if (ai[1] == 2)
				currentRow = 3;
			movingRight = false;
			movingLeft = false;
			velocity.x = 0;
		}
		else
		{
			cout << "shit" << endl;
			if (ai[1] == 1)
			{
				movingLeft = false;
				movingRight = true;
			}
			else
			{
				movingLeft = true;
				movingRight = false;
			}
			ai[1] = 0;
		}
	}
	cout << ai[1];
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
	cout << newposition.x << endl;
	if (friendly || !ai[1])
	{
		if (newposition.x < 0)
		{
			ai[0] = Dice::Inst()->rand(60, 60);
			ai[1] = 1;
		}
		else if (newposition.x > 400)
		{
			ai[0] = Dice::Inst()->rand(60, 60);
			ai[1] = 2;
		}
	}

	if (!CheckCollision_tileX(newposition.x)) {
		position.x = newposition.x;
	}
	if (!CheckCollision_tileY(newposition.y)) {
		position.y = newposition.y;
	}

	CheckCollision_hostile(newposition);
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

		if (pBottom <= entities[i]->getPosition().y)
			continue;
		if (newpos.y >= entities[i]->getPosition().y + entities[i]->getHeight())
			continue;
		if (pRight <= entities[i]->getPosition().x)
			continue;
		if (newpos.x >= entities[i]->getPosition().x + entities[i]->getWidth())
			continue;

		//onhit
		SoundLoader::Inst()->playSound(PlayerDamageSound);
		int damage = Dice::Inst()->rand(entities[i]->minATT, entities[i]->maxATT) - defense;
		life -= damage;
		Vector2D textShift(entityCenter.x + Dice::Inst()->randInverse(20), position.y + Dice::Inst()->randInverse(20));
		World::Inst()->createText(textShift, 0, -0.1f, to_string(damage), segoeui22, COLOR_RED, 60);
		velocity.y = -10.f;
		//acceleration.y = -GRAVITY;
		if (entities[i]->getPosition().x > position.x) {
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
		TextureLoader::Inst()->drawFrameSp(uniqueID, position.x - Camera::Inst()->getPosition().x + Main::Inst()->getRenderWidth() / 2, position.y - Camera::Inst()->getPosition().y + Main::Inst()->getRenderHeight() / 2, width, height, currentRow, currentFrame, angle, alpha, color);
	}
}

void Hostile::kill()
{
	active = false;
	timer.start();
	Camera::Inst()->getTarget_nonConst()->exp += exp;
	///drop
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

	SoundLoader::Inst()->playSound(dieSoundID);
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
	SoundLoader::Inst()->playSound(damageSoundID);
	color = COLOR_RED;
	damageTick = DAMAGETICK;
}
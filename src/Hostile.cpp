#include "Hostile.h"
#include "Main.h"
#include "World.h"
#include "Camera.h"
#include "TextureLoader.h"
#include "SoundLoader.h"
#include "Inputor.h"
#include "Dice.h"

Hostile::Hostile(int id, int _worldID, int x, int y)
{
	timer = new MyTimer();
	position.x = x;
	position.y = y;
	uniqueID = id;
	worldID = _worldID;
	Load();
}

void Hostile::Load()
{
	if (uniqueID == BlackBlock)
	{
		width = 80;
		height = 80;

		level = 1;
		exp = 5;
		life = 100;
		minATT = 10;
		maxATT = 20;
		defense = 2;
		return;
	}
}

void Hostile::update()
{
	Entity::update();

	VisiableCheck();

	if (active)
	{
		if (life <= 0)
			kill();
		currentFrame = int(((SDL_GetTicks() / animatedSpeed) % numFrames));
	}
	else
	{
		if (!active && currentFrame == numFrames - 1)
		{
			dead = true;
			return;
		}
		currentFrame = int(((timer->getTicks() / animatedSpeed) % numFrames));
	}
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
	timer->start();
	if (uniqueID == BlackBlock)
	{
		SoundLoader::Inst()->playSound(DeathSound);
		currentFrame = 0;
		currentRow = 1;
		numFrames = 11;

		Camera::Inst()->getTarget_nonConst()->exp += exp; //************xp should not be distributed globally
		World::Inst()->newItem(WoodenSword, 1, position.x + width / 2, position.y + height / 2);
		return;
	}
}

void Hostile::onHit(int damage, int critChance)
{
	int actualDamage;
	if (Dice::Inst()->rand(100) < critChance)
	{
		actualDamage = 2 * (damage - defense);
		if (actualDamage < 2)
			actualDamage = 2;
		life -= actualDamage;

		angle += 45;
		Vector2D textShift(entityCenter.x + Dice::Inst()->randInverse(20), position.y + Dice::Inst()->randInverse(20));
		World::Inst()->createText(textShift, 0, -0.1f, to_string(actualDamage) + "!", segoeui28, COLOR_RED, 60);
	}
	else
	{
		actualDamage = damage - defense;
		if (actualDamage < 1)
			actualDamage = 1;
		life -= actualDamage;

		angle += 45;
		Vector2D textShift(entityCenter.x + Dice::Inst()->randInverse(20), position.y + Dice::Inst()->randInverse(20));
		World::Inst()->createText(textShift, 0, -0.1f, to_string(actualDamage), segoeui22, COLOR_GREEN, 60);
	}
	SoundLoader::Inst()->playSound(DamageSound);
}
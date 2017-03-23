#include "Skill.h"
#include "IDSheet.h"
#include "SoundLoader.h"
#include "Inputor.h"
#include "World.h"
#include "Dice.h"
#include "Camera.h"
#include "Player.h"

Skill::Skill(int _skillID, int _level)
{
	skillID = _skillID;
	level = _level;
	Load();
}

void Skill::Load()
{
	preSkillIndex = 0;
	cooldownTick = 0;
	if (skillID == HealingMagicSkill)
	{
		name = "healing";
		skillClass = SkillClassHealingMagic;
		sp = 1;
		maxLevel = 5;
		cooldownInterval = 240;
		minATT = level * 5;
		maxATT = level * 10;
		manaConsume = 5 + level * 5;
		return;
	}
	if (skillID == IchorKnifeSkill)
	{
		preSkillIndex = HealingMagicIndex;
		name = "Double Ichor Knife";
		skillClass = SkillClassAttackingMagic;
		sp = 1;
		maxLevel = 5;
		cooldownInterval = 120;
		minATT = level * 5;
		maxATT = level * 10;
		manaConsume = level * 3;
		return;
	}
}

void Skill::refresh()
{
	Load();
}

void Skill::update()
{
	if (cooldownTick)
	{
		cooldownTick++;
		if (cooldownTick == cooldownInterval)
			cooldownTick = 0;
	}
}

void Skill::castSkill()
{
	Player* player = Camera::Inst()->getTarget_nonConst();

	if (cooldownTick)
		return;
	if (manaConsume > player->mana)
		return;
	player->mana -= manaConsume;
	cooldownTick = 1;

	if (skillID == HealingMagicSkill)
	{
		player->heal(Dice::Inst()->rand(minATT, maxATT));
		SoundLoader::Inst()->playSound(HealingMagicSound);
		return;
	}
	if (skillID == IchorKnifeSkill)
	{
		Vector2D mousepos = Inputor::Inst()->getMouseDefinitePosition();
		Vector2D direction = mousepos - player->entityCenter;
		direction.normalize();
		direction.x *= 10;
		direction.y *= 5;
		for (int i = 0; i < 2; i++)
		{
			Vector2D randpos(player->entityCenter.x + Dice::Inst()->rand(80), player->entityCenter.y + Dice::Inst()->randInverse(80));
			World::Inst()->newProjectile(IchorKnifeProjectile, randpos, direction.x, direction.y, player);
			SoundLoader::Inst()->playSound(AttackSound);
		}

		return;
	}
}

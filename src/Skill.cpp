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
	preSkillIndex = -1;
	preSkillLevel = 1;
	postSkillIndex = -1;
	cooldownTick = 0;
	passive = false;
	sp = 1;
	if (skillID == SkillPhysicalTraining)
	{
		postSkillIndex = SkillIndexDoubleThrow;
		passive = true;
		name = "Physical Training";
		maxLevel = 3;
		percentATT = level * 10;
		return;
	}
	if (skillID == SkillDoubleThrow)
	{
		preSkillIndex = SkillIndexPhysicalTraining;
		postSkillIndex = SkillIndexTripleThrow;
		name = "Double Dart";
		maxLevel = 3;
		cooldownInterval = 240;
		minATT = level * level * 5;
		maxATT = level * level * 10;
		manaConsume = 2 + level * 1;
		return;
	}
	if (skillID == SkillTripleThrow)
	{
		preSkillIndex = SkillIndexDoubleThrow;
		preSkillLevel = 2;
		name = "Triple Star";
		maxLevel = 3;
		cooldownInterval = 300;
		minATT = level * level * 5;
		maxATT = level * level * 10;
		manaConsume = 5 + level * 1;
		return;
	}
	if (skillID == SkillLifeForce)
	{
		postSkillIndex = SkillIndexIronBody;
		passive = true;
		name = "Life Force";
		sp = 1;
		maxLevel = 3;
		minATT = level * 20;
		return;
	}
	if (skillID == SkillIronBody)
	{
		preSkillIndex = SkillIndexLifeForce;
		postSkillIndex = SkillIndexLifeRegeneration;
		passive = true;
		name = "Iron Body";
		maxLevel = 3;
		minATT = level;
		return;
	}
	if (skillID == SkillLifeRegeneration)
	{
		preSkillIndex = SkillIndexIronBody;
		passive = true;
		name = "Second Spring";
		maxLevel = 3;
		minATT = level * 5;
		return;
	}
	if (skillID == SkillMPBoost)
	{
		postSkillIndex = SkillIndexSummonAttack;
		passive = true;
		name = "Mana Regeneration";
		maxLevel = 3;
		minATT = level * 10;
		return;
	}
	if (skillID == SkillCriticalThrow)
	{
		passive = true;
		name = "Critical Shoot";
		maxLevel = 3;
		minATT = level * 3;
		return;
	}
	if (skillID == SkillSummonAttack)
	{
		preSkillIndex = SkillIndexMPBoost;
		preSkillLevel = 1;
		name = "Summon Attack";
		sp = 2;
		maxLevel = 3;
		cooldownInterval = 600;
		minATT = level * 20;
		maxATT = level * 100;
		manaConsume = 5 + level * 5;
		return;
	}
	if (skillID == SkillSpeedup)
	{
		name = "Speed Up";
		maxLevel = 3;
		cooldownInterval = 1200;
		minATT = level * 10;
		maxATT = 600;
		manaConsume = 5 + level * 5;
		return;
	}
}

void Skill::refresh()
{
	Load();
}

void Skill::update()
{
	Player* player = Camera::Inst()->getTarget_nonConst();
	if (!passive)
	{
		///update cd
		if (cooldownTick)
		{
			cooldownTick++;
			if (cooldownTick == cooldownInterval)
				cooldownTick = 0;
		}
	}
	else
	{
		///update passive effects
		if (skillID == SkillPhysicalTraining)
		{
			player->minATT += player->minATT * percentATT / 100.f;
			player->maxATT += player->minATT * percentATT / 100.f;
			return;
		}
		if (skillID == SkillLifeForce)
		{
			player->maxlife += minATT;
			return;
		}
		if (skillID == SkillIronBody)
		{
			player->defense += minATT;
			return;
		}
		if (skillID == SkillLifeRegeneration)
		{
			player->lifeRegenInterval -= player->lifeRegenInterval * minATT / 100.f;
			return;
		}
		if (skillID == SkillCriticalThrow)
		{
			player->critChance += minATT;
			return;
		}
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

	if (skillID == SkillDoubleThrow)
	{
		player->attacking();
		player->attacking();
		return;
	}
	if (skillID == SkillTripleThrow)
	{
		player->attacking();
		player->attacking();
		player->attacking();
		return;
	}
	if (skillID == SkillSummonAttack)
	{
		player->attackingFrameTick = 40;
		if (player->facingLeft)
			World::Inst()->newSkillEffect(SummonMagicEffect, player->entityCenter.x, player->position.y + player->height, 0, minATT, maxATT, player->critChance);
		else
			World::Inst()->newSkillEffect(SummonMagicEffect, player->entityCenter.x, player->position.y + player->height, 1, minATT, maxATT, player->critChance);
		SoundLoader::Inst()->playSound(SummonMagicUseSound);
		return;
	}
	if (skillID == SkillSpeedup)
	{
		player->addBuff(SpeedupBuff, minATT, maxATT);
		SoundLoader::Inst()->playSound(SpeedupSkillSound);
		World::Inst()->newSkillEffect(SpeedupSkillEffect, player->entityCenter.x, player->position.y + player->height, 0);
		return;
	}
}

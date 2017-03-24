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
	postSkillIndex = -1;
	cooldownTick = 0;
	passive = false;
	if (skillID == SkillPhysicalTraining)
	{
		postSkillIndex = SkillIndexDoubleThrow;
		passive = true;
		name = "Physical Training";
		sp = 1;
		maxLevel = 5;
		minATT = level * 5;
		maxATT = level * 10;
		return;
	}
	if (skillID == SkillDoubleThrow)
	{
		preSkillIndex = SkillIndexPhysicalTraining;
		postSkillIndex = SkillIndexTripleThrow;
		name = "Double Throw";
		sp = 1;
		maxLevel = 5;
		cooldownInterval = 240;
		minATT = level * 5;
		maxATT = level * 10;
		manaConsume = 2 + level * 1;
		return;
	}
	if (skillID == SkillTripleThrow)
	{
		preSkillIndex = SkillIndexDoubleThrow;
		name = "Triple Throw";
		sp = 1;
		maxLevel = 5;
		cooldownInterval = 300;
		minATT = level * 5;
		maxATT = level * 10;
		manaConsume = 5 + level * 1;
		return;
	}
	if (skillID == SkillLifeForce)
	{
		postSkillIndex = SkillIndexIronBody;
		passive = true;
		name = "Life Force";
		sp = 1;
		maxLevel = 5;
		minATT = level * 20;
		return;
	}
	if (skillID == SkillIronBody)
	{
		preSkillIndex = SkillIndexLifeForce;
		postSkillIndex = SkillIndexLifeRegeneration;
		passive = true;
		name = "Iron Body";
		sp = 1;
		maxLevel = 5;
		minATT = level;
		return;
	}
	if (skillID == SkillLifeRegeneration)
	{
		preSkillIndex = SkillIndexIronBody;
		passive = true;
		name = "Life Regenaration";
		sp = 1;
		maxLevel = 5;
		minATT = level * 5;
		return;
	}
	if (skillID == SkillMPBoost)
	{
		passive = true;
		name = "MP Boost";
		sp = 1;
		maxLevel = 5;
		minATT = level * 10;
		return;
	}
	if (skillID == SkillCriticalThrow)
	{
		passive = true;
		name = "Critical Throw";
		sp = 1;
		maxLevel = 5;
		minATT = level * 3;
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
	///update cd
	if (cooldownTick)
	{
		cooldownTick++;
		if (cooldownTick == cooldownInterval)
			cooldownTick = 0;
	}
	///update passive effects
	if (skillID == SkillPhysicalTraining)
	{
		player->minATT += minATT;
		player->maxATT += maxATT;
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
}

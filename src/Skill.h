#pragma once
#include <string>

using namespace std;

class Skill
{
private:
	int skillID;

	void Load();
public:
	string name;
	int preSkillIndex;
	int postSkillIndex;
	bool passive;
	int sp;
	int level;
	int maxLevel;
	int cooldownInterval;
	int cooldownTick;
	int percentATT;
	int minATT;
	int maxATT;
	int manaConsume;

	Skill(int skillID, int level);

	void refresh();
	void update();

	void castSkill();
};
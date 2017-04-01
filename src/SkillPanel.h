#pragma once
#include <vector>
#include "Object.h"
#include "Button.h"
#include "TextboxGroup.h"
#include "Skill.h"

using namespace std;

class SkillSlot : public Object
{
private:
	TextboxGroup skillInfoTexts;
	Textbox* levelNumText;
	bool mouseAbove;

	void Load();
	void InitSkillInfo();
public:
	Skill* skill;

	int skillIndex;

	SkillSlot(int skillID, Skill* skill);
	~SkillSlot() { delete levelNumText; }
	void refresh();

	int type() { return TypeSkillSlot; }
	void update();
	void draw();

	bool checkMouseOver();
	void updateSkillInfo(Vector2D pos);
	void renderSkillInfo();
};

class SkillPanel : public Object
{
	enum HotkeyIndex
	{
		hotkey1,
		hotkey2,
		hotkey3,
		hotkey4,
		hotkey5,
		hotkey6,
	};
private:
	MyTimer selectCooldown;
	int selectedSkillIndex;
	Button closeButton;
	Textbox* skillPointsText;

	void Load();

	void UpdateSkillButtons();
	void UpdateSkillSlots();
public:
	vector<Skill*> skills;
	vector<Button*> skillButtons;
	vector<SkillSlot*> skillslots;
	vector<int>	hotkeySkillIndexes;
	int skillPoints;
	SkillPanel();

	int type() { return TypeSkillPanel; }
	void update();
	void draw();

	bool outsideCheckMouseOver();
	bool outsideCheckMouseTitle();

	void outsideUpdateSkills();
	void outsideDrawHotkeys();
};
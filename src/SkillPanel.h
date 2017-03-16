#pragma once
#include "Object.h"
#include "Button.h"
#include "Textbox.h"

//class SkillSlot : public Object
//{
//private:
//	bool mouseAbove;
//	MyTimer* selectCooldown;
//
//	void Load();
//	void InitItemInfo();
//	void UpdateItemInfo();
//	void RenderItemInfo();
//	bool CheckMouseOver_slot();
//public:
//	Textbox stackNumText;
//	vector<Textbox*> itemInfoTexts;
//	int stack;
//	int maxStack;
//
//	int itemClass;
//	int index;
//	bool beingPicked;
//	Vector2D slotpos;
//
//	int minATT;
//	int maxATT;
//	int defense;
//
//	SkillSlot(int index);
//	SkillSlot(int id, int index, int stack);
//	~SkillSlot() { delete selectCooldown; }
//	void init(int id, int _index, int stack);
//
//	int type() { return TypeSkillSlot; }
//	void update();
//	void draw();
//};

class SkillPanel : public Object
{
private:
	Button closeButton;

	void Load();
public:
	SkillPanel();

	int type() { return TypeSkillPanel; }
	void update();
	void draw();

	bool outsideCheckMouseOver();
	bool outsideCheckMouseTitle();
};
#pragma once
#include "Object.h"
#include "Button.h"
#include "Textbox.h"

//class InventoryItem : public Object
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
//	InventoryItem(int index);
//	InventoryItem(int id, int index, int stack);
//	~InventoryItem() { delete selectCooldown; }
//	void init(int id, int _index, int stack);
//
//	int type() { return TypeInventoryItem; }
//	void update();
//	void draw();
//};

class SkillPanel : public Object
{
private:
	Textbox* levelText;
	Textbox* expText;
	Textbox* expNextText;
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
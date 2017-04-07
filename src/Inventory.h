#pragma once
#include <vector>
#include "Object.h"
#include "IDSheet.h"
#include "Button.h"
#include "MyTimer.h"
#include "TextboxGroup.h"
#include "Item.h"

using namespace std;

class InventoryItem : public Object
{
private:
	MyTimer* selectCooldown;
	
	void Load();
	void InitItemInfo();
	bool CheckMouseOver_slot();
	void InventoryMovement();
public:
	Textbox* stackNumText;
	TextboxGroup itemInfoTexts;
	bool mouseAbove;
	bool stackable;
	int stack;
	int maxStack;

	ItemType itemType;
	ItemslotType slotType;
	bool beingPicked;
	Vector2D slotpos;

	int minATT;
	int maxATT;
	int defense;

	InventoryItem(int id, int stack, ItemslotType slotType);
	~InventoryItem() { delete selectCooldown; delete stackNumText; }
	void init(int id, int stack);

	int type() { return TypeInventoryItem; }
	void update();
	void draw();

	InventoryItem* getSplit(int stack);
};

class Inventory : public Object
{
private:
	int inventorySize;

	Textbox* goldNumText;
	Button closeButton;
	Button rearrangeButton;

	void Load();
public:
	vector<InventoryItem*> items;
	int gold;

	Inventory();
	~Inventory() { items.clear(); }

	int type() { return TypeInventory; }
	void update();
	void draw();

	bool outsideCheckMouseOver();
	bool outsideCheckMouseTitle();
	bool addItem(int itemID, int stack);
	bool addItem(Item* item);
	void rearrangeItems();
};
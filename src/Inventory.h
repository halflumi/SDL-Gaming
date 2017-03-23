#pragma once
#include <vector>
#include "Object.h"
#include "IDSheet.h"
#include "Button.h"
#include "MyTimer.h"
#include "Textbox.h"
#include "Item.h"

using namespace std;

class InventoryItem : public Object
{
private:
	bool mouseAbove;
	MyTimer* selectCooldown;
	
	void Load();
	void InitItemInfo();
	void UpdateItemInfo();
	void RenderItemInfo();
	bool CheckMouseOver_slot();
public:
	Textbox* stackNumText;
	vector<Textbox*> itemInfoTexts;
	bool stackable;
	int stack;
	int maxStack;

	int itemClass;
	bool beingPicked;
	Vector2D slotpos;

	int minATT;
	int maxATT;
	int defense;

	InventoryItem(int id, int stack);
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

	Button closeButton;
	Button rearrangeButton;

	void Load();
public:
	vector<InventoryItem*> items;

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
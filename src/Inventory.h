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
	Textbox stackNumText;
	vector<Textbox*> itemInfoTexts;
	int stack;
	int maxStack;

	int itemClass;
	int index;
	bool beingPicked;
	Vector2D slotpos;

	int minATT;
	int maxATT;
	int defense;

	InventoryItem(int index);
	InventoryItem(string id, int index, int stack);
	~InventoryItem() { delete selectCooldown; }
	void init(string id, int stack);

	string type() { return TypeInventoryItem; }
	void update();
	void draw();

	InventoryItem* getSplit(int stack);
};

class Inventory : public Object
{
private:
	vector<InventoryItem*> items;
	int inventorySize;

	Button closeButton;

	void Load();
public:
	Inventory();
	~Inventory() { items.clear(); }
	
	const InventoryItem* getItem(int i) const { return items[i]; };

	string type() { return TypeInventory; }
	void update();
	void draw();

	bool outsideCheckMouseOver();
	bool outsideCheckMouseTitle();
	bool addItem(string itemID, int width, int height, int stack, int maxStack);
	bool addItem(Item* item);
};
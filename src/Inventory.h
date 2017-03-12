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
	InventoryItem(int id, int index, int stack);
	~InventoryItem() { delete selectCooldown; }
	void init(int id, int _index, int stack);

	int type() { return TypeInventoryItem; }
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

	int type() { return TypeInventory; }
	void update();
	void draw();

	bool outsideCheckMouseOver();
	bool outsideCheckMouseTitle();
	bool addItem(int itemID, int stack, int maxStack, int width, int height);
	bool addItem(Item* item);
};
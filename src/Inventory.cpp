#include "Inventory.h"
#include "Main.h"
#include "World.h"
#include "TextureLoader.h"
#include "Inputor.h"
#include "Camera.h"

#define GRIDSIZE 48
#define GRIDGAP 2
#define GRIDNUM 6
#define TITLEHEIGHT 53

InventoryItem::InventoryItem(int _index) : slotpos(0, 0), stack(1)
{
	selectCooldown = NULL;
	active = false;
	index = _index;
	Load();
}

InventoryItem::InventoryItem(string id, int _index, int _stack) : slotpos(0, 0), stack(_stack)
{
	selectCooldown = NULL;
	uniqueID = id;
	index = _index;
	Load();
}

void InventoryItem::init(string id, int _stack)
{
	active = true;
	uniqueID = id;
	stack = _stack;
	itemInfoTexts.clear();
	Load();
}

void InventoryItem::Load()
{
	stackNumText.init(&position, to_string(stack), segoeui22, { 0,0,0 });
	if(selectCooldown == NULL)
		selectCooldown = new MyTimer(true);
	mouseAbove = false;
	beingPicked = false;

	maxStack = 1;
	minATT = 0;
	maxATT = 0;
	defense = 0;
	if (uniqueID == WoodenSword)
	{
		width = 40;
		height = 40;
		itemClass = ItemClass_Weapon;
		minATT = -10;
		maxATT = 10;
	}
	if (uniqueID == OrichalcumShortsword)
	{
		width = 38;
		height = 38;
		itemClass = ItemClass_Weapon;
		minATT = 10;
		maxATT = 20;
	}
	InitItemInfo();
}

void InventoryItem::InitItemInfo()
{
	itemInfoTexts.push_back(new Textbox(position, uniqueID, segoeui22, { 0,0,255 }, -1));
	itemInfoTexts.push_back(new Textbox(position, "attack: " + to_string(minATT) + "~" + to_string(maxATT), segoeui18, { 0,255,0 }, -1));
	//itemInfoTexts.push_back(new Textbox(position, "defense: 10", segoeui18, { 0,255,0 }, -1));
	//itemInfoTexts.push_back(new Textbox(position, "and other things here", segoeui18, { 0,255,0 }, -1));
}

void InventoryItem::UpdateItemInfo()
{
	Vector2D infopos(position.x, position.y + GRIDSIZE);
	int lineIndent = TTF_FontLineSkip(Main::Inst()->getFont(segoeui18));
	int i, len = itemInfoTexts.size();
	itemInfoTexts[0]->setPosition(infopos);
	for (i = 1; i < len; i++)
		itemInfoTexts[i]->setPosition(position.x, infopos.y + i * lineIndent);
}

void InventoryItem::RenderItemInfo()
{
	int i, len = itemInfoTexts.size();
	for (i = 0; i < len; i++)
		itemInfoTexts[i]->draw();
}

void InventoryItem::update()
{
	stackNumText.setPosition(position);
	if (to_string(stack) != stackNumText.text)
		stackNumText.changeText(to_string(stack));
	if (!beingPicked)
		slotpos = position;

	if (CheckMouseOver_slot())
	{
		mouseAbove = true;
		UpdateItemInfo();
		if (Inputor::Inst()->getMouseButtonState(MOUSE_LEFT) && selectCooldown->getTicks() > CLICKCOOLDOWN)
		{
			selectCooldown->start();
			Player* player = Camera::Inst()->getTarget_nonConst();
			
			if (player->selectingItem == NULL)	//pick one item up
			{
				if (active)
				{
					player->selectingItem = this;
					beingPicked = true;
				}
			}
			else
			{
				if (player->selectingItem == this)	//exchange itself
				{
					beingPicked = false;
					player->selectingItem = NULL;
				}
				else if (active && stack != maxStack && player->selectingItem->getUniqueID() == uniqueID) //add up to the same item
				{
					int addup = player->selectingItem->stack + stack;
					if (addup > maxStack)
					{
						player->selectingItem->stack -= maxStack - stack;
						stack = maxStack;
					}
					else // two items add up into one item, use empty item to fill the gap
					{
						stack = addup;
						
						player->selectingItem->active = false;
						player->selectingItem->beingPicked = false;
						player->selectingItem = NULL;
					}
				}
				else if (active)	//exchange one item
				{
					if (index == -1) // exchange with equipment slots of character panel
					{
						string tempID = player->selectingItem->uniqueID;
						int tempIndex = player->selectingItem->index;
						int tempStack = player->selectingItem->stack;
						player->selectingItem->init(uniqueID, stack);
						player->selectingItem->index = tempIndex;
						init(tempID, tempStack);
						player->selectingItem = NULL;
					}
					else
					{
						int currentIndex = index;
						index = player->selectingItem->index;
						player->selectingItem->index = currentIndex;
						player->selectingItem->beingPicked = false;
						player->selectingItem = this;
						beingPicked = true;
					}
				}
				else //put down one item
				{
					if (index == -1) // equipment slots of character panel
					{
						init(player->selectingItem->getUniqueID(), player->selectingItem->stack);
						player->selectingItem->active = false;
						player->selectingItem->beingPicked = false;
						player->selectingItem = NULL;
					}
					else if (player->selectingItem->index != -1) //means it is not splited, exchange the index
					{
						int currentIndex = index;
						index = player->selectingItem->index;
						player->selectingItem->index = currentIndex;
						player->selectingItem->beingPicked = false;
						player->selectingItem = NULL;
					}
					else // means it is splited, mimic the item to the empty slot
					{
						init(player->selectingItem->getUniqueID(), player->selectingItem->stack);
						delete player->selectingItem;
						player->selectingItem = NULL;
					}
				}
			}
		}
		if (stack > 1 && Inputor::Inst()->getMouseButtonState(MOUSE_RIGHT) && selectCooldown->getTicks() > CLICKCOOLDOWN)
		{
			selectCooldown->start();
			Player* player = Camera::Inst()->getTarget_nonConst();

			if (player->selectingItem == NULL)
			{
				int split = stack / 2;
				stack -= split;
				player->selectingItem = getSplit(split);
			}
		}
	}
	else
		mouseAbove = false;
}

void InventoryItem::draw()
{
	if (active)
	{
		TextureLoader::Inst()->drawFrameEx(uniqueID, position.x, position.y, width, height, GRIDSIZE, GRIDSIZE, currentRow, currentFrame, angle, alpha);
		if (maxStack > 1)
			stackNumText.draw();
		if (!beingPicked && mouseAbove)
			RenderItemInfo();
	}
	if (mouseAbove)
		TextureLoader::Inst()->drawFrameEx(InventoryGridMask, slotpos.x, slotpos.y, 10, 10, GRIDSIZE, GRIDSIZE, 0, 0, 0, 255);
}

bool InventoryItem::CheckMouseOver_slot()
{
	Vector2D* mousepos = Inputor::Inst()->getMouseRelativePosition();

	if (mousepos->x <= slotpos.x + GRIDSIZE && mousepos->x >= slotpos.x && mousepos->y >= slotpos.y && mousepos->y <= slotpos.y + GRIDSIZE)
		return true;
	return false;
}

InventoryItem* InventoryItem::getSplit(int stack)
{
	InventoryItem* splitItem = new InventoryItem(uniqueID, -1, stack);
	//cout << splitItem->getUniqueID();
	splitItem->slotpos = slotpos;
	splitItem->beingPicked = true;
	return splitItem;
}

//--------------------------------------------------------
Inventory::Inventory() : closeButton(InventoryCloseButton)
{
	uniqueID = InventoryGrid;
	Load();
}

void Inventory::Load()
{
	width = 304;
	height = 354;
	position.x = Main::Inst()->getRenderWidth() - 100 - width;
	position.y = 100;
	inventorySize = 36;
	for (int i = 0; i < inventorySize; i++)
		items.push_back(new InventoryItem(i));
}

void Inventory::update()
{
	if (closeButton.outsideUpdate())
		active = false;

	closeButton.setPosition(position.x + 260, position.y + 2);

	for (int i = 0; i < inventorySize; i++)
	{
		if (!items[i]->beingPicked)
		{
			items[i]->setPosition(position.x + items[i]->index % GRIDNUM * (GRIDSIZE + GRIDGAP) + 3, position.y + items[i]->index / GRIDNUM * (GRIDSIZE + GRIDGAP) + TITLEHEIGHT);

			items[i]->update();
		}
	}
}

void Inventory::draw()
{
	TextureLoader::Inst()->draw(uniqueID, position.x, position.y, width, height);
	closeButton.draw();

	int i, len = items.size();
	for (i = 0; i < len; i++)
			items[i]->draw();
}

bool Inventory::outsideCheckMouseTitle()
{
	Vector2D* mousepos = Inputor::Inst()->getMouseRelativePosition();
	if (mousepos->y <= position.y + TITLEHEIGHT)
		return true;
	return false;
}

bool Inventory::outsideCheckMouseOver()
{
	Vector2D* mousepos = Inputor::Inst()->getMouseRelativePosition();
	if (mousepos->x <= position.x + width && mousepos->x >= position.x && mousepos->y >= position.y && mousepos->y <= position.y + height)
		return true;
	return false;
}

bool Inventory::addItem(string itemID, int width, int height, int stack, int maxStack)
{
	bool availSlots[36] = { 0 };
	int itemsArrayIndex[36] = { 0 };
	int i;
	for (i = 0; i < inventorySize; i++)
	{
		if (!items[i]->active)
		{
			availSlots[items[i]->index] = true;
			itemsArrayIndex[items[i]->index] = i;
		}
		else if (items[i]->getUniqueID() == itemID && items[i]->stack < maxStack)
		{
			int addup = items[i]->stack + stack;
			if (addup > maxStack)
			{
				stack -= maxStack - items[i]->stack;
				items[i]->stack = maxStack;
			}
			else
			{
				items[i]->stack = addup;
				return true;
			}
		}
	}
	for (i = 0; i < inventorySize; i++)
	{
		if (availSlots[i])
		{
			delete items[itemsArrayIndex[i]];
			items[itemsArrayIndex[i]] = new InventoryItem(itemID, itemsArrayIndex[i], i);
			return true;
		}
	}

	return false;
}

bool Inventory::addItem(Item* item)
{
	bool availSlots[36] = { 0 };
	int itemsArrayIndex[36] = { 0 };
	int i;
	for (i = 0; i < inventorySize; i++)
	{
		if (!items[i]->active) // if the slot is empty
		{
			availSlots[items[i]->index] = true;
			itemsArrayIndex[items[i]->index] = i;
		}
		else if (items[i]->getUniqueID() == item->getUniqueID() && items[i]->stack < item->maxStack)
		{
			cout << "sjit";
			int addup = items[i]->stack + item->stack;
			if (addup > item->maxStack)
			{
				item->stack -= item->maxStack - items[i]->stack;
				items[i]->stack = item->maxStack;
			}
			else
			{
				items[i]->stack = addup;
				return true;
			}
		}
	}
	for (i = 0; i < inventorySize; i++)
	{
		if (availSlots[i])
		{
			delete items[itemsArrayIndex[i]];
			items[itemsArrayIndex[i]] = new InventoryItem(item->getUniqueID(), i, item->stack);
			return true;
		}
	}

	return false;
}
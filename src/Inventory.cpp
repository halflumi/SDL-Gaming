#include "Inventory.h"
#include "Main.h"
#include "World.h"
#include "TextureLoader.h"
#include "Inputor.h"
#include "Camera.h"
#include "XmlParser.h"

#define GRIDSIZE 48
#define ITEMSIZE 32
#define SIZEDIFF 8
#define GRIDGAP 2
#define GRIDNUM 6
#define TITLEHEIGHT 53

#define GoldNumTextPos		position.x + 33, position.y + 357
#define CloseButtonPos		position.x + 260, position.y + 2
#define RearrangeButtonPos	position.x + 261, position.y + 355

InventoryItem::InventoryItem(int id, int _stack, ItemslotType _slotType) : itemInfoTexts(-1, TextEquipmentDescription)
{
	if (id == NULL)
		active = false;
	slotpos.set(0, 0);
	selectCooldown = NULL;
	uniqueID = id;
	stack = _stack;
	slotType = _slotType;
	beingPicked = false;
	Load();
}

void InventoryItem::init(int id, int _stack)
{
	active = true;
	uniqueID = id;
	stack = _stack;
	itemInfoTexts.clear();
	Load();
}

void InventoryItem::Load()
{
	stackNumText = new Textbox(position, to_string(stack), segoeui22, COLOR_BLACK, -1);
	if(selectCooldown == NULL)
		selectCooldown = new MyTimer(true);
	mouseAbove = false;

	stackable = false;
	maxStack = 1;
	minATT = 0;
	maxATT = 0;
	defense = 0;
	if (uniqueID == IronDartItem)
	{
		name = IronDartItemName;
		itemType = ItemTypeWeapon;

		width = 27;
		height = 27;
		minATT = 1;
		maxATT = 5;
	} 
	else if (uniqueID == CrystalDartItem)
	{
		name = CrystalDartName;
		itemType = ItemTypeWeapon;

		width = 27;
		height = 27;
		minATT = 15;
		maxATT = 20;
	} 
	else if (uniqueID == MokbiDartItem)
	{
		name = MokbiDartName;
		itemType = ItemTypeWeapon;

		width = 28;
		height = 28;
		minATT = 5;
		maxATT = 10;
	}
	else if (uniqueID == SteelyThrowingKnivesItem)
	{
		name = SteelyThrowingKnivesItemName;
		itemType = ItemTypeWeapon;

		width = 29;
		height = 29;
		minATT = 5;
		maxATT = 10;
		
	}
	else if (uniqueID == HealthPotionItem)
	{
		width = height = 27;

		name = HealthPotionItemName;
		itemType = ItemTypeMiscellaneous;
		stackable = true;
		maxStack = 99;
	}
	InitItemInfo();
}

void InventoryItem::InitItemInfo()
{
	itemInfoTexts.newLine(name, segoeui22, COLOR_WHITE);

	switch(itemType)
	{
	case ItemTypeWeapon:
		itemInfoTexts.newLine("attack: " + to_string(minATT) + "~" + to_string(maxATT), segoeui18, COLOR_WHITE);
		itemInfoTexts.newLine("attack Interval: 40", segoeui18, COLOR_WHITE);
		if (uniqueID == MokbiDartItem || uniqueID == SteelyThrowingKnivesItem)
		{
			itemInfoTexts.newLine("can penetrate 2 enemies", segoeui18, COLOR_WHITE);
			return;
		}
		break;
	}
}

void InventoryItem::update()
{
	stackNumText->setPosition(position);
	if (to_string(stack) != stackNumText->text)
		stackNumText->changeText(to_string(stack));
	if (!beingPicked)
		slotpos = position;

	if (CheckMouseOver_slot())
	{
		mouseAbove = true;
		itemInfoTexts.setPosition(position.x, position.y + GRIDSIZE);
		itemInfoTexts.update();
		/// pickup, exchange or throw
		InventoryMovement();
	}
	else
		mouseAbove = false;
}

void InventoryItem::draw()
{
	if (active)
	{
		TextureLoader::Inst()->drawFrameEx(uniqueID, position.x + SIZEDIFF, position.y + SIZEDIFF, width, height, ITEMSIZE, ITEMSIZE, currentRow, currentFrame, angle, alpha);
		if (maxStack > 1)
			stackNumText->draw();
	}
	if (mouseAbove)
		TextureLoader::Inst()->drawFrameEx(InventoryGridMask, slotpos.x, slotpos.y, 10, 10, GRIDSIZE, GRIDSIZE, 0, 0, 0, 255);
}

bool InventoryItem::CheckMouseOver_slot()
{
	Vector2D mousepos = Inputor::Inst()->getMouseRelativePosition();

	if (mousepos.x <= slotpos.x + GRIDSIZE && mousepos.x >= slotpos.x && mousepos.y >= slotpos.y && mousepos.y <= slotpos.y + GRIDSIZE)
		return true;
	return false;
}

InventoryItem* InventoryItem::getSplit(int stack)
{
	InventoryItem* splitItem = new InventoryItem(uniqueID, stack, ItemslotTypeSplited);
	splitItem->slotpos = slotpos;
	splitItem->beingPicked = true;
	return splitItem;
}

void InventoryItem::InventoryMovement()
{
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
		else if (player->selectingItem == this)	//exchange itself
		{
			beingPicked = false;
			player->selectingItem = NULL;
		}
		else if (active && stackable && player->selectingItem->getUniqueID() == uniqueID) //add up to the same item
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
			if(slotType == ItemslotTypeInventory || slotType == player->selectingItem->itemType || slotType == player->selectingItem->itemType + 1) // a potion cannot be put in weapon slot
				if (player->selectingItem->slotType == ItemslotTypeSplited) // means it is splited, pick up the item
				{
					int tempID = player->selectingItem->uniqueID;
					int tempStack = player->selectingItem->stack;
					player->selectingItem->init(uniqueID, stack);
					init(tempID, tempStack);
				}
				else
				{
					int tempID = player->selectingItem->uniqueID;
					int tempStack = player->selectingItem->stack;
					player->selectingItem->init(uniqueID, stack);
					init(tempID, tempStack);
					player->selectingItem->beingPicked = false;
					player->selectingItem = NULL;
					beingPicked = false;
				}
		}
		else //put down one item
		{
			if (slotType == ItemslotTypeInventory || slotType == player->selectingItem->itemType || slotType == player->selectingItem->itemType + 1) // a potion cannot be put in weapon slot
				if (player->selectingItem->slotType == ItemslotTypeSplited) // means it is splited, delete the splited
				{
					init(player->selectingItem->getUniqueID(), player->selectingItem->stack);
					delete player->selectingItem;
					player->selectingItem = NULL;
				}
				else
				{
					init(player->selectingItem->getUniqueID(), player->selectingItem->stack);
					player->selectingItem->active = false;
					player->selectingItem->beingPicked = false;
					player->selectingItem = NULL;
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

//--------------------------------------------------------
Inventory::Inventory() : closeButton(InventoryCloseButton), rearrangeButton(InventoryArrangeButton)
{
	uniqueID = InventoryGrid;
	Load();
}

void Inventory::Load()
{
	width = 304;
	height = 394;
	position.x = Main::Inst()->getRenderWidth() - 100 - width;
	position.y = 100;

	gold = XmlParser::Inst()->gold;
	goldNumText = new Textbox(position, to_string(gold), arial28_bold, COLOR_BLACK, -1);
	for (int i = 0; i < INVENTORYSIZE * 2; i += 2)
		items.push_back(new InventoryItem(XmlParser::Inst()->inventory[i], XmlParser::Inst()->inventory[i + 1], ItemslotTypeInventory));
}

void Inventory::update()
{
	///update close button
	if (closeButton.outsideUpdate())
	{
		active = false;
		Camera::Inst()->getTarget_nonConst()->mouseCooldown.start();
	}
	closeButton.setPosition(CloseButtonPos);
	closeButton.update();
	///update rearrange button
	if (rearrangeButton.outsideUpdate())
		rearrangeItems();
	rearrangeButton.setPosition(RearrangeButtonPos);
	rearrangeButton.update();
	///update gold text
	goldNumText->setPosition(GoldNumTextPos); 
	goldNumText->changeText(to_string(gold));
	///update inventory items
	for (int i = 0; i < INVENTORYSIZE; i++)
		if (!items[i]->beingPicked)
		{
			items[i]->setPosition(position.x + i % GRIDNUM * (GRIDSIZE + GRIDGAP) + 3, position.y + i / GRIDNUM * (GRIDSIZE + GRIDGAP) + TITLEHEIGHT);
			items[i]->update();
		}
}

void Inventory::draw()
{
	TextureLoader::Inst()->draw(uniqueID, position.x, position.y, width, height);
	closeButton.draw();
	rearrangeButton.draw();
	goldNumText->draw();

	int i, len = items.size();
	int infoIndex = -1;
	for (i = 0; i < len; i++)
	{
		items[i]->draw();
		if (items[i]->mouseAbove && items[i]->active && !items[i]->beingPicked)
			infoIndex = i;
	}
	if(infoIndex != -1)
		items[infoIndex]->itemInfoTexts.draw();
}

bool Inventory::outsideCheckMouseTitle()
{
	Vector2D mousepos = Inputor::Inst()->getMouseRelativePosition();
	if (mousepos.y <= position.y + TITLEHEIGHT)
		return true;
	return false;
}

bool Inventory::outsideCheckMouseOver()
{
	Vector2D mousepos = Inputor::Inst()->getMouseRelativePosition();
	if (mousepos.x <= position.x + width && mousepos.x >= position.x && mousepos.y >= position.y && mousepos.y <= position.y + height)
		return true;
	return false;
}

bool Inventory::addItem(int itemID, int stack)
{
	if (itemID == GoldCoinItem)
	{
		gold += stack;
		return true;
	}

	int i;
	for (i = 0; i < INVENTORYSIZE; i++)
	{
		if (items[i]->active && items[i]->stackable && items[i]->getUniqueID() == itemID)
		{
			int addup = items[i]->stack + stack;
			if (addup > items[i]->maxStack)
			{
				stack = addup - items[i]->maxStack;
				items[i]->stack = items[i]->maxStack;
			}
			else
			{
				items[i]->stack = addup;
				return true;
			}
		}
	}
	for (i = 0; i < INVENTORYSIZE; i++)
		if (!items[i]->active)
		{
			items[i]->init(itemID, stack);
			return true;
		}

	return false;
}

bool Inventory::addItem(Item* item)
{
	if (item->getUniqueID() == GoldCoinItem)
	{
		gold += item->stack;
		return true;
	}

	int i;
	for (i = 0; i < INVENTORYSIZE; i++)
	{
		if (items[i]->active && items[i]->stackable && items[i]->getUniqueID() == item->getUniqueID())
		{
			int addup = items[i]->stack + item->stack;
			if (addup > items[i]->maxStack)
			{
				item->stack = addup - items[i]->maxStack;
				items[i]->stack = items[i]->maxStack;
			}
			else
			{
				items[i]->stack = addup;
				return true;
			}
		}
	}
	for (i = 0; i < INVENTORYSIZE; i++)
		if (!items[i]->active)
		{
			items[i]->init(item->getUniqueID(), item->stack);
			return true;
		}

	return false;
}

void Inventory::rearrangeItems()
{
	int idArray[INVENTORYSIZE];
	int stackArray[INVENTORYSIZE];
	int i, k;
	int maxIndex;
	int max;
	bool combined;
	for (k = 0; k < INVENTORYSIZE;)
	{
		max = 0;
		combined = false;
		for (i = 0; i < INVENTORYSIZE; i++)
		{
			if (!items[i]->active) // filter empty slots
				continue;
			if (items[i]->getUniqueID() > max) // find biggest id
			{
				maxIndex = i;
				max = items[i]->getUniqueID();
			}
		}
		if (max == 0) // all the items has been checked
			break;

		if(items[maxIndex]->stackable) // check whether the stackable item can be stacked with the sorted item
			for (i = 0; i < k; i++) 
			{
				if (idArray[i] == items[maxIndex]->getUniqueID())
				{
					int addup = stackArray[i] + items[maxIndex]->stack;
					//cout << addup << endl;
					if (addup > items[maxIndex]->maxStack)
					{
						items[maxIndex]->stack = addup - items[maxIndex]->maxStack;
						stackArray[i] = items[maxIndex]->maxStack;
					}
					else
					{
						stackArray[i] = addup;
						combined = true;
						break;
					}
				}
			}
		if (!combined)
		{
			idArray[k] = max;
			stackArray[k] = items[maxIndex]->stack;
			k++;
		}
		items[maxIndex]->active = false;
	}

	for (i = 0; i < k; i++)
		items[i]->init(idArray[i], stackArray[i]);
}
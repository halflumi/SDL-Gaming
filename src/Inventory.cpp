#include "Inventory.h"
#include "Main.h"
#include "World.h"
#include "TextureLoader.h"
#include "Inputor.h"
#include "Camera.h"
#include "XmlParser.h"

#define GRIDSIZE 48
#define GRIDGAP 2
#define GRIDNUM 6
#define TITLEHEIGHT 53

#define CloseButtonPos		position.x + 260, position.y + 2
#define RearrangeButtonPos	position.x + 261, position.y + 355

InventoryItem::InventoryItem(int id, int _stack) : slotpos(0, 0)
{
	if (id == NULL)
		active = false;
	selectCooldown = NULL;
	uniqueID = id;
	stack = _stack;
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
	beingPicked = false;

	stackable = false;
	maxStack = 1;
	minATT = 0;
	maxATT = 0;
	defense = 0;
	if (uniqueID == IronDartItem)
	{
		name = IronDartItemName;
		itemClass = ItemClassWeapon;

		width = 48;
		height = 48;
		minATT = 1;
		maxATT = 5;
	} 
	else if (uniqueID == CrystalDartItem)
	{
		name = CrystalDartName;
		itemClass = ItemClassWeapon;

		width = 48;
		height = 48;
		minATT = 15;
		maxATT = 20;
	} 
	else if (uniqueID == MokbiDartItem)
	{
		name = MokbiDartName;
		itemClass = ItemClassWeapon;

		width = 48;
		height = 48;
		minATT = 5;
		maxATT = 10;
	}
	InitItemInfo();
}

void InventoryItem::InitItemInfo()
{
	itemInfoTexts.push_back(new Textbox(position, name, segoeui22, COLOR_BLUE, -1));
	itemInfoTexts.push_back(new Textbox(position, "attack: " + to_string(minATT) + "~" + to_string(maxATT), segoeui18, COLOR_GREEN, -1));
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
	stackNumText->setPosition(position);
	if (to_string(stack) != stackNumText->text)
		stackNumText->changeText(to_string(stack));
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
					int tempID = player->selectingItem->uniqueID;
					int tempStack = player->selectingItem->stack;
					player->selectingItem->init(uniqueID, stack);
					init(tempID, tempStack);
					player->selectingItem = this;
					beingPicked = true;
				}
				else //put down one item
				{
					if (player->selectingItem->itemClass == -1) // means it is splited, delete the splited
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
			stackNumText->draw();
		if (!beingPicked && mouseAbove)
			RenderItemInfo();
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
	InventoryItem* splitItem = new InventoryItem(uniqueID, stack);
	splitItem->itemClass = -1;
	splitItem->slotpos = slotpos;
	splitItem->beingPicked = true;
	return splitItem;
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

	for (int i = 0; i < INVENTORYSIZE * 2; i += 2)
		items.push_back(new InventoryItem(XmlParser::Inst()->inventory[i], XmlParser::Inst()->inventory[i + 1]));
}

void Inventory::update()
{
	if (closeButton.outsideUpdate())
	{
		active = false;
		Camera::Inst()->getTarget_nonConst()->mouseCooldown.start();
	}
	closeButton.setPosition(CloseButtonPos);
	closeButton.update();
	if (rearrangeButton.outsideUpdate())
		rearrangeItems();
	rearrangeButton.setPosition(RearrangeButtonPos);
	rearrangeButton.update();

	for (int i = 0; i < INVENTORYSIZE; i++)
	{
		if (!items[i]->beingPicked)
		{
			items[i]->setPosition(position.x + i % GRIDNUM * (GRIDSIZE + GRIDGAP) + 3, position.y + i / GRIDNUM * (GRIDSIZE + GRIDGAP) + TITLEHEIGHT);
			items[i]->update();
		}
	}
}

void Inventory::draw()
{
	TextureLoader::Inst()->draw(uniqueID, position.x, position.y, width, height);
	closeButton.draw();
	rearrangeButton.draw();

	int i, len = items.size();
	for (i = 0; i < len; i++)
			items[i]->draw();
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
	int i;
	for (i = 0; i < INVENTORYSIZE; i++)
	{
		if (active && items[i]->stackable && items[i]->getUniqueID() == itemID)
		{
			int addup = items[i]->stack + stack;
			if (addup > items[i]->maxStack)
			{
				stack -= items[i]->maxStack - items[i]->stack;
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
	int i;
	for (i = 0; i < INVENTORYSIZE; i++)
	{
		if (active && items[i]->stackable && items[i]->getUniqueID() == item->getUniqueID())
		{
			int addup = items[i]->stack + item->stack;
			if (addup > items[i]->maxStack)
			{
				item->stack -= items[i]->maxStack - items[i]->stack;
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
	for (k = 0; k < INVENTORYSIZE; k++)
	{
		max = 0;
		for (i = 0; i < INVENTORYSIZE; i++)
		{
			if (!items[i]->active)
				continue;
			if (items[i]->getUniqueID() > max)
			{
				maxIndex = i;
				max = items[i]->getUniqueID();
			}
		}
		if (max == 0)
			break;
		idArray[k] = max;
		stackArray[k] = items[maxIndex]->stack;
		items[maxIndex]->active = false;
	}

	for (i = 0; i < k; i++)
		items[i]->init(idArray[i], stackArray[i]);
}
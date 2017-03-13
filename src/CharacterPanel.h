#pragma once
#include "Object.h"
#include "Button.h"
#include "Textbox.h"
#include "Inventory.h"

class CharacterPanel : public Object
{
private:
	Textbox* levelText;
	Textbox* expText;
	Textbox* expNextText;
	Button closeButton;

	void Load();
public:
	InventoryItem* rightHandSlot;
	InventoryItem* leftHandSlot;
	InventoryItem* helmetSlot;

	CharacterPanel();

	int type() { return TypeCharacterPanel; }
	void update();
	void draw();

	bool outsideCheckMouseOver();
	bool outsideCheckMouseTitle();
};
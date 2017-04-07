#pragma once
#include "Object.h"
#include "Button.h"
#include "Textbox.h"
#include "ProgressBar.h"
#include "Inventory.h"

class CharacterPanel : public Object
{
private:
	Textbox* levelText;
	Textbox* expText;
	Textbox* expNextText;
	Button closeButton;
	ProgressBar xpBar;

	void Load();
public:
	InventoryItem* rightHandSlot;
	InventoryItem* leftHandSlot;
	InventoryItem* helmetSlot;

	CharacterPanel();
	~CharacterPanel() 
	{
		delete levelText; 
		delete expText; 
		delete expNextText;
		delete rightHandSlot;
		delete leftHandSlot;
		delete helmetSlot;
	}

	int type() { return TypeCharacterPanel; }
	void update();
	void draw();

	bool outsideCheckMouseOver();
	bool outsideCheckMouseTitle();
};
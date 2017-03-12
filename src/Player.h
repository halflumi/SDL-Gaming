#pragma once
#include <vector>
#include "IDSheet.h"
#include "Entity.h"
#include "Item.h"
#include "Inventory.h"
#include "CharacterPanel.h"
#include "Dialog.h"
#include "MyTimer.h"
#include "Projectile.h"

class Player : public Entity
{
private:
	bool onLadder;
	bool movingUp;
	bool movingDown;
	Projectile* meleeProjectile;
	int attackInterval;
	int attackTick;
	int invulnerableInterval;
	int invulnerableTick;
	int baseATT;
	int baseDEF;

	bool focused;
	Vector2D display_pos;

	MyTimer* keyCooldown;
	MyTimer* mouseCooldown;

	void Load();
	
	void isLevelingup();
	void updateAttributes();

	void HandleInput();
	void HandleMovement();
	void HandleDisplay();
	void Attacking();

	bool CheckCollision_tileX(float x);
	bool CheckCollision_tileY(float y);
	void CheckCollision_hostile(Vector2D newpos);
	void CheckInteractive();
	void DoInteractive(int id);
	void CheckPickup();
	void HitGround();
public:
	Dialog* dialog;
	CharacterPanel* characterPanel;
	Inventory* inventory;
	InventoryItem* selectingItem;
	InventoryItem* rightHand_equ;
	InventoryItem* leftHand_equ;
	InventoryItem* helmet_equ;
	int expToNextLevel;

	Player(int id, int x, int y);
	~Player() { delete inventory; delete keyCooldown; delete mouseCooldown; }

	void setFocused() { focused = true; }
	void removeFocused() { focused = false; }
	Vector2D& getDisplayPos() { return display_pos; }

	int type() { return TypePlayer; }
	void update();
	void draw();
};
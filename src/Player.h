#pragma once
#include <vector>
#include "IDSheet.h"
#include "Entity.h"
#include "Item.h"
#include "Inventory.h"
#include "CharacterPanel.h"
#include "SkillPanel.h"
#include "Dialog.h"
#include "MyTimer.h"
#include "Projectile.h"

#define PLAYERWIDTH 50
#define PLAYERHEIGHT 100

class Player : public Entity
{
private:
	bool onLadder;
	bool movingUp;
	bool movingDown;
	Projectile* meleeProjectile;
	int attackInterval;
	int attackTick;
	int lifeRegenInterval;
	int lifeRegenTick;
	int manaRegenInterval;
	int manaRegenTick;
	int invulnerableInterval;
	int invulnerableTick;
	int baseATT;
	int baseDEF;
	int baseMaxLife;
	int baseMaxMana;

	bool focused;
	Vector2D display_pos;

	void Load();
	
	void isLevelingup();
	void updateAttributes();

	void HandleInput();
	void HandlePlayerPhysics( );
	void HandleMovement();
	void HandleDisplay();
	void Attacking();


	bool CheckCollision_tileX(float& x);
	bool CheckCollision_tileY(float& y);
	void CheckCollision_hostile(Vector2D newpos);
	void CheckInteractive();

	void DoInteractive(Object*);
	void CheckPickup();
	void HitGround();
public:
	MyTimer keyCooldown;
	MyTimer mouseCooldown;

	Dialog* dialog;
	CharacterPanel* characterPanel;
	SkillPanel* skillPanel;
	Inventory* inventory;
	InventoryItem* selectingItem;
	InventoryItem* rightHand_equ;
	InventoryItem* leftHand_equ;
	InventoryItem* helmet_equ;
	int expToNextLevel;

	Player(int id, int x, int y);
	~Player() { delete inventory; }

	void setFocused() { focused = true; }
	void removeFocused() { focused = false; }
	Vector2D& getDisplayPos() { return display_pos; }

	int type() { return TypePlayer; }
	void update();
	void draw();
};
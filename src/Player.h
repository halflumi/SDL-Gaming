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
#include "Buff.h"

#define TOTALATTRIBUTES 5

class Player : public Entity
{
private:
	MyTimer frameTimer;
	vector<Buff*> buffs;
	int footstepTick;
	bool onLadder;
	bool movingUp;
	bool movingDown;
	float baseMaxSpeed;
	int attackInterval;
	int attackTick;
	int lifeRegenTick;
	int manaRegenTick;
	int baseATT;
	int baseDEF;
	int baseMaxLife;
	int baseMaxMana;
	int baseLifeRegenInterval;
	int baseLifeRegenAmount;
	int baseManaRegenInterval;
	int baseManaRegenAmount;
	int baseInvulnerableInterval;	
	static enum AttributesList { ATK, DEF, HP, MP, SP };
	static const int LvUpBonus[TOTALATTRIBUTES][MAXLEVEL];

	void Load();
	
	void IsDead();
	void IsLevelingup();
	void LevelUpBonus( );
	void UpdateAttributes();
	void HandleInput();
	void HandlePlayerPhysics( );
	void HandleMovement();
	void HandleDisplay();

	bool CheckCollision_tileX(float& x);
	bool CheckCollision_tileY(float& y);
	void CheckCollision_hostile(Vector2D newpos);
	void CheckInteractive(short flag = 0);

	void DoInteractive(Object*);
	void CheckPickup();
	void HitGround();
	void ChangeFacingDirection();
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

	int attackingFrameTick;
	int expToNextLevel;
	int lifeRegenInterval;
	int lifeRegenAmount;
	int manaRegenInterval;
	int manaRegenAmount;

	Player(int id, int x, int y);
	~Player();

	int type() { return TypePlayer; }
	void update();
	void draw();

	void attacking();
	void addBuff(int buffID, int ATT, int duration);
};
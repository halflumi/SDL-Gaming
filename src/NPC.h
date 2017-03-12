#pragma once
#include "Entity.h"
#include "IDSheet.h"
#include "MyTimer.h"

class NPC : public Entity
{
private:
	MyTimer* clickCooldown;

	void Load();
	bool CheckPlayerNearby();
public:
	NPC(int id, int x, int y);

	int type() { return TypeNPC; }
	void update();
	void draw();

	bool checkMouseOver();
};
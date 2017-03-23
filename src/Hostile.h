#pragma once
#include "Entity.h"
#include "IDSheet.h"
#include "MyTimer.h"

class Hostile : public Entity
{
private:
	MyTimer timer;
	bool beingHit;
	int damageTick;

	void Load();
public:
	Hostile(int id, int worldID, int x, int y);

	int type() { return TypeHostile; }
	void update();
	void draw();
	void kill();

	void onHit(int damage, int critChance);
};
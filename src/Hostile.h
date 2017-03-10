#pragma once
#include "Entity.h"
#include "IDSheet.h"
#include "MyTimer.h"

class Hostile : public Entity
{
private:
	MyTimer* timer;

	void Load();
public:
	Hostile(int x, int y, string id, int worldID);
	~Hostile() { delete timer; }

	string type() { return TypeHostile; }

	void update();
	void draw();
	void kill();

	void onHit(int damage, int critChance);
};
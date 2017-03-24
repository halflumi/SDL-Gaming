#pragma once
#include "Entity.h"
#include "IDSheet.h"
#include "MyTimer.h"

class Hostile : public Entity
{
private:
	MyTimer timer;
	SDL_Color color;
	bool beingHit;
	int damageTick;
	bool stasis;

	void Load();

	void MovingAI();
	bool CheckCollision_tileX(float& x);
	bool CheckCollision_tileY(float& y);
	void HitGround();
public:
	Hostile(int id, int worldID, int x, int y);

	int type() { return TypeHostile; }
	void update();
	void draw();
	void kill();

	void onHit(int damage, int critChance);
};
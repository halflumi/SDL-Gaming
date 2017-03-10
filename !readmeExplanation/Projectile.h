#pragma once
#include "Entity.h"
#include "IDSheet.h"

class Projectile : public Entity
{
private:
	void load();
public:
	//Projectile(int x, int y, string id);
	Projectile(Vector2D* pos, string id, int worldID, float velocity_x, float velocity_y, bool gravitational = true);
	
	string type() { return TypeProjectile; }

	void update();
	void draw();

	void kill();
};
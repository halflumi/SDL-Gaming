#pragma once
#include <vector>
#include "Entity.h"
#include "IDSheet.h"

class Projectile : public Entity
{
private:
	Entity* owner;
	vector<int> attackedTargets;
	int penetrate;

	void Load();
	void Kill();
	bool CollisionCheck_tile(Vector2D newpos);
	bool CollisionCheck_entity(Vector2D newpos);
public:
	Projectile(int id, int worldID, Vector2D pos, float velocity_x, float velocity_y, Entity* owner, bool gravitational = true);
	
	int type() { return TypeProjectile; }
	void update();
	void draw();
};
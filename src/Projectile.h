#pragma once
#include <vector>
#include "Entity.h"
#include "IDSheet.h"
#include "MyTimer.h"

class Projectile : public Entity
{
private:
	MyTimer frameTimer;
	vector<int> attackedTargets;
	int penetrate;

	void Load();
	void Kill();
	bool CollisionCheck_tile(Vector2D newpos);
	bool CollisionCheck_entity(Vector2D newpos);
public:
	Projectile(int id, int worldID, Vector2D pos, float velocity_x, float velocity_y, int minATT, int maxATT, int critChance, bool friendly, bool gravitational = true);
	
	int type() { return TypeProjectile; }
	void update();
	void draw();
	void onHit(int damage, bool critical) {}
};
#pragma once
#include "Entity.h"
#include "IDSheet.h"
#include "MyTimer.h"

class Item : public Entity
{
private:
	MyTimer frameTimer;
	bool bumping;

	void Load();

	bool CollisionCheck(Vector2D newpos);
public:
	int stack;

	Item(int id, int stack, int x, int y);
	Item(int id, int stack, int x, int y, float velocity_x, float velocity_y);

	int type() { return TypeItem; }
	void update();
	void draw();
};
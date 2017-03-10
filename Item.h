#pragma once
#include "Entity.h"
#include "IDSheet.h"

class Item : public Entity
{
private:
	void Load();

	bool CollisionCheck(Vector2D newpos);
public:
	int stack;
	int maxStack;

	//Item(int x, int y, string id);
	Item(int x, int y, string id, int stack);
	Item(int x, int y, float velocity_x, float velocity_y, string id, int stack);

	string type() { return TypeItem; }

	void update();
	void draw();
};
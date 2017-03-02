#pragma once
#include "Object.h"
#include "IDSheet.h"

class Tile : public Object
{
private:
	void load();
public:
	Tile(int x, int y, string id);

	string type() { return TypeTile; }
	void update();
	void draw();
};
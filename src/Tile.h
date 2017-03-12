#pragma once
#include "Object.h"
#include "IDSheet.h"

class Tile : public Object
{
private:
	void Load();
public:
	Tile(int id, int x, int y);

	int type() { return TypeTile; }
	void update();
	void draw();
};
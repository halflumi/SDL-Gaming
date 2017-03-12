#pragma once
#include "Object.h"
#include "IDSheet.h"


class Sprite : public Object
{
private:
	void Load();
public:
	Sprite(int id, int x, int y);

	int type() { return TypeSprite; }
	void update();
	void draw();
	bool outsideCheckPlayerWithin();
};
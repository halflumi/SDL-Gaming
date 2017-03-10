#pragma once
#include "Object.h"
#include "IDSheet.h"


class Sprite : public Object
{
private:
	void Load();
public:
	Sprite(int x, int y, string id);

	string type() { return TypeSprite; }
	void update();
	void draw();
	bool outsideCheckPlayerWithin();
};
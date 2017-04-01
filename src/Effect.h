#pragma once
#include "Object.h"
#include "IDSheet.h"
#include "MyTimer.h"

class Effect : public Object
{
private:
	MyTimer frameTimer;
	bool attacked;
	int minATT;
	int maxATT;
	int critChance;

	void Load();
public:
	Effect(int effectID, int x, int y, int row);
	Effect(int effectID, int x, int y, int row, int minATT, int maxATT, int critChance);

	int type() { return TypeEffect; }
	void update();
	void draw();
};
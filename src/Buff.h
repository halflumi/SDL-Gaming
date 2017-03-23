#pragma once
#include "Object.h"
#include "IDSheet.h"
#include "Textbox.h"

class Buff : Object
{
private:
	Textbox timeleftText;
	int lastingTicks;

	void Load();
public:
	Buff(int buffID, int lastingTime);
	
	int type() { return TypeBuff; }
	void update();
	void draw();
};
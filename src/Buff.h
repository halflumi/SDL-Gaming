#pragma once
#include "Object.h"
#include "IDSheet.h"
#include "Textbox.h"

class Buff : public Object
{
private:
	MyTimer timer; 
	Textbox timeleftText;
	int duration;

	int ATT;

	void Load();
public:
	Buff(int buffID, int ATT, int lastingTime);
	
	int type() { return TypeBuff; }
	void update();
	void draw();

	void extend();
};
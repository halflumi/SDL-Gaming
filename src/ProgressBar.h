#pragma once
#include "Object.h"
#include "IDSheet.h"

class ProgressBar : public Object
{
private:
	int barLength;
	int barHeight;
	int targetValMin;
	int targetValMax;
	int renderWidth;

	void Load();
	void update();
public:
	ProgressBar(int barID, int barLength, int barHeight);

	int type() { return TypeProgressBar; }
	void draw();

	void updateTarget(int min, int max);
};
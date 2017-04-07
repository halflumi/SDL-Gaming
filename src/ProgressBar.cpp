#include "ProgressBar.h"
#include "TextureLoader.h"

ProgressBar::ProgressBar(int barID, int _barLength, int _barHeight)
{
	uniqueID = barID;
	barLength = _barLength;
	barHeight = _barHeight;
	Load();
}

void ProgressBar::Load()
{
	width = height = 10;
	targetValMin = targetValMax = 0;
}

void ProgressBar::update()
{
	renderWidth = targetValMin * barLength / targetValMax;
}

void ProgressBar::draw()
{
	TextureLoader::Inst()->drawEx2(uniqueID, position.x, position.y , width, height, renderWidth, barHeight);
}

void ProgressBar::updateTarget(int min, int max)
{
	if (targetValMin == min && targetValMax == max)
		return;
	targetValMin = min;
	targetValMax = max;
	update();
}
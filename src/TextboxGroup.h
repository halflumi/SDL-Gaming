#pragma once
#include <vector>
#include "Object.h"
#include "Textbox.h"

using namespace std;

class TextboxGroup : public Object
{
private:
	TextboxGroupType textType;
	vector<Textbox*> texts;
	int duration;
	bool background;

	void Load();
public:
	TextboxGroup(int duration, TextboxGroupType textType);

	int type() { return TypeTextboxGroup; }
	void update();
	void draw();

	void newLine(string text, int fontID, SDL_Color color);
	void clear();
};
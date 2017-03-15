#pragma once
#include <string>
#include "Object.h"
#include "IDSheet.h"
#include "Textbox.h"
#include "MyTimer.h"

using namespace std;

class Button : public Object
{
private:
	MyTimer clickCooldown;

	void Load();
	bool CheckMouseOver();
public:
	Textbox* buttonText;
	int buttonClass;
	int flag;

	Button(int id);
	Button(int id, int flag);
	~Button() { if (buttonText) delete buttonText; }

	int type() { return TypeButton; }
	void update();
	void draw();

	bool outsideUpdate();
};
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
	Textbox* buttonText;
	MyTimer clickCooldown;

	void Load();
	bool CheckMouseOver();
public:
	//Button() { };
	Button(string id);
	~Button() { if (buttonText) delete buttonText; }

	string type() { return TypeButton; }
	void update();
	void draw();

	bool outsideUpdate();
};
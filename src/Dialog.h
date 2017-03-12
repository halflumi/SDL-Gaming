#pragma once
#include "Object.h"
#include "IDSheet.h"
#include "Textbox.h"

class Dialog : public Object
{
private:
	Textbox* dialogText;

	void Load();
public:
	Dialog* next;

	Dialog();
	~Dialog() { delete dialogText; };

	int type() { return TypeDialog; }
	void update();
	void draw();
};
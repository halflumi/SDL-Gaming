#pragma once
#include <string>
#include "Object.h"
#include "IDSheet.h"

using namespace std;

class Button : public Object
{
private:
	void Load();
	bool CheckMouseOver();
public:
	Button(string id);

	string type() { return TypeButton; }
	void update();
	void draw();

	bool outsideUpdate();
};
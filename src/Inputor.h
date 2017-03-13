#pragma once
#include <SDL.h>
#include <vector>
#include "Vector2D.h"

using namespace std;

enum mouse_buttons
{
	MOUSE_LEFT = 0,
	MOUSE_MIDDLE = 1,
	MOUSE_RIGHT = 2
};

class Inputor
{
private:
	Inputor() : keystates(0), mousestates(3), mousePosition_old(new Vector2D(0, 0)),mousePosition(new Vector2D(0,0)) {}
	~Inputor() { delete mousePosition_old; delete mousePosition; }
	Inputor(const Inputor&);
	static Inputor* INSTANCE;

	const Uint8* keystates;
    vector<bool> mousestates;
	Vector2D* mousePosition_old;
	Vector2D* mousePosition;

	void onKeyDown();
	void onKeyUp();
	void onMouseMove(SDL_Event & event);
	void onMouseButtonDown(SDL_Event & event);
	void onMouseButtonUp(SDL_Event & event);
public:
	static Inputor* Inst()
	{
		if (INSTANCE == 0)
		{
			INSTANCE = new Inputor();
			return INSTANCE;
		}

		return INSTANCE;
	}

	void updating();

	bool isKeyDown(SDL_Scancode key) const;
	bool getMouseButtonState(int buttonNumber) const { return mousestates[buttonNumber]; }
	Vector2D* getMouseRelativePosition() const { return mousePosition; }
	Vector2D* getMouseDefinitePosition() const;
	Vector2D* getMouseMotionVector();
};
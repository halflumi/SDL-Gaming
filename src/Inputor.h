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
	Inputor() : keystates(0), mousestates(3), mousePosition_old(0, 0),mousePosition(0,0) {}
	~Inputor() { }
	Inputor(const Inputor&);
	static Inputor* INSTANCE;
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
private:
	const Uint8* keystates;
    vector<bool> mousestates;
	Vector2D mousePosition_old;
	Vector2D mousePosition;

	void OnKeyDown();
	void OnKeyUp();
	void OnMouseMove(SDL_Event & event);
	void OnMouseButtonDown(SDL_Event & event);
	void OnMouseButtonUp(SDL_Event & event);
public:
	void updating();

	bool isKeyDown(SDL_Scancode key) const;
	void resetMouseState();
	bool getMouseButtonState(int buttonNumber) const { return mousestates[buttonNumber]; }
	Vector2D getMouseRelativePosition() const { return mousePosition; }
	Vector2D getMouseDefinitePosition() const;
	Vector2D getMouseMotionVector();
};
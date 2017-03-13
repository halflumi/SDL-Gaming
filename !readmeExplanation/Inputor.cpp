#include "Inputor.h"
#include "Main.h"

Inputor* Inputor::INSTANCE = 0;

void Inputor::updating()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			Main::Inst()->quit();
			break;
		case SDL_KEYDOWN:
			onKeyDown();
			break;
		case SDL_KEYUP:
			onKeyUp();
			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(e);
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(e);
			break;
		case SDL_MOUSEMOTION:
			onMouseMove(e);
			break;
		}
	}
}

bool Inputor::isKeyDown(SDL_Scancode key) const
{
	if (keystates != 0)
	{
		if (keystates[key] == 1)
			return true;
		else
			return false;
	}

	return false;
}

void Inputor::onKeyDown()
{
	keystates = SDL_GetKeyboardState(0);
}

void Inputor::onKeyUp()
{
	keystates = SDL_GetKeyboardState(0);
}

void Inputor::onMouseMove(SDL_Event &event)
{
	mousePosition->x = event.motion.x;
	mousePosition->y = event.motion.y;
}

void Inputor::onMouseButtonDown(SDL_Event &event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		mousestates[MOUSE_LEFT] = true;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		mousestates[MOUSE_MIDDLE] = true;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		mousestates[MOUSE_RIGHT] = true;
	}
}

void Inputor::onMouseButtonUp(SDL_Event &event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		mousestates[MOUSE_LEFT] = false;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		mousestates[MOUSE_MIDDLE] = false;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		mousestates[MOUSE_RIGHT] = false;
	}
}
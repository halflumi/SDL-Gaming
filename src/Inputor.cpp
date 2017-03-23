#include "Inputor.h"
#include "Main.h"
#include "Camera.h"

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
			OnKeyDown();
			break;
		case SDL_KEYUP:
			OnKeyUp();
			break;
		case SDL_MOUSEBUTTONDOWN:
			OnMouseButtonDown(e);
			break;
		case SDL_MOUSEBUTTONUP:
			OnMouseButtonUp(e);
			break;
		case SDL_MOUSEMOTION:
			OnMouseMove(e);
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

void Inputor::OnKeyDown()
{
	keystates = SDL_GetKeyboardState(0);
}

void Inputor::OnKeyUp()
{
	keystates = SDL_GetKeyboardState(0);
}

void Inputor::OnMouseMove(SDL_Event &event)
{
	mousePosition_old.x = mousePosition.x;
	mousePosition_old.y = mousePosition.y;
	mousePosition.x = event.motion.x;
	mousePosition.y = event.motion.y;
}

void Inputor::OnMouseButtonDown(SDL_Event &event)
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

void Inputor::OnMouseButtonUp(SDL_Event &event)
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

void Inputor::resetMouseState()
{
	mousestates[MOUSE_LEFT] = false;
	mousestates[MOUSE_MIDDLE] = false;
	mousestates[MOUSE_RIGHT] = false;
}

Vector2D Inputor::getMouseDefinitePosition() const
{
	return Vector2D(mousePosition.x + Camera::Inst()->getPosition().x - Main::Inst()->getRenderWidth() / 2, mousePosition.y + Camera::Inst()->getPosition().y - Main::Inst()->getRenderHeight() / 2);
}

Vector2D Inputor::getMouseMotionVector()
{
	return Vector2D(mousePosition.x - mousePosition_old.x, mousePosition.y - mousePosition_old.y);
}
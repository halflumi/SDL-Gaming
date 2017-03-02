#pragma once

#include <SDL.h>
#include <iostream>
#include <vector>

#include "Object.h"

using namespace std;

class Main
{
private:
	Main() {}
	~Main() {}
	Main(const Main&);
	static Main* INSTANCE;

	SDL_Window* window;
	SDL_Renderer* renderer;

	bool _running;
	int windowWidth;
	int windowHeight;
public:
	static Main* Inst()
	{
		if (INSTANCE == 0)
		{
			INSTANCE = new Main();
			return INSTANCE;
		}

		return INSTANCE;
	}

	SDL_Window* getWindow() const { return window; }
	SDL_Renderer* getRenderer() const { return renderer; }
	int getWindowWidth() const { return windowWidth; }
	int getWindowHeight() const { return windowHeight; }

	bool running() { return _running; }
	void quit() { _running = false; }

	bool Initialize(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void updating();
	void rendering();
	void close();
};


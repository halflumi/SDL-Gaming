#include "MyTimer.h"

MyTimer::MyTimer()
{
	startTicks = 0;
	pausedTicks = 0;

	paused = false;
	started = false;
}

MyTimer::MyTimer(bool defaultStarted)
{
	startTicks = 0;
	pausedTicks = 0;

	paused = false;
	started = false;

	if (defaultStarted)
		start();
}

int MyTimer::getTicks()
{
	Uint32 time = 0;

	if (started)
	{
		if (paused)
			time = pausedTicks;
		else
			time = SDL_GetTicks() - startTicks;
	}

	return time;
}

void MyTimer::start()
{
	started = true;

	paused = false;

	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

void MyTimer::start(int shift)
{
	started = true;

	paused = false;

	startTicks = SDL_GetTicks() + shift;
	pausedTicks = 0;
}

void MyTimer::stop()
{
	started = false;

	paused = false;

	startTicks = 0;
	pausedTicks = 0;
}

void MyTimer::pause()
{
	if (started && !paused)
	{
		paused = true;

		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}

void MyTimer::unpause()
{
	if (started && paused)
	{
		paused = false;

		startTicks = SDL_GetTicks() - pausedTicks;

		pausedTicks = 0;
	}
}
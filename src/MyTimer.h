#pragma once
#include <SDL.h>

class MyTimer
{
private:
	Uint32 startTicks;
	Uint32 pausedTicks;

	bool paused;
	bool started;
public:
	MyTimer();
	MyTimer(bool defaultStarted);

	bool isStarted() { return started; }
	bool isPaused() { return paused; }
	Uint32 getTicks();

	void start();
	void start(int shift);
	void stop();
	void pause();
	void unpause();
};
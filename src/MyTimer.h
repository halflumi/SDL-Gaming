#pragma once

class MyTimer
{
private:
	int startTick;

public:
	MyTimer();
	MyTimer(bool defaultStarted);

	int getTicks();

	void start();
	void start(int shift);
};
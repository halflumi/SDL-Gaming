#include "MyTimer.h"
#include "Main.h"

MyTimer::MyTimer()
{
	startTick = 0;
}

MyTimer::MyTimer(bool defaultStarted)
{
	startTick = 0;

	if (defaultStarted)
		start();
}

int MyTimer::getTicks()
{
	return Main::Inst()->getFrameTick() - startTick;
}

void MyTimer::start()
{
	startTick = Main::Inst()->getFrameTick();
}

void MyTimer::start(int shift)
{
	startTick = Main::Inst()->getFrameTick() + shift;
}
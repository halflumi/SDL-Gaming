#include "Buff.h"
#include "TextureLoader.h"
#include "Camera.h"
#include "Main.h"

#define BUFFSIZE 32

Buff::Buff(int buffID, int _ATT, int lastingTime) : timer(true)
{
	uniqueID = buffID;
	ATT = _ATT;
	duration = lastingTime;
	Load();
}

void Buff::Load()
{
	width = height = BUFFSIZE;
}

void Buff::update()
{
	Player* player = Camera::Inst()->getTarget_nonConst();

	if (timer.getTicks() > duration)
		active = false;

	if (uniqueID == SpeedupBuff)
	{
		player->maxSpeed += player->maxSpeed * ATT / 100.f;
		return;
	}
}

void Buff::draw()
{
	TextureLoader::Inst()->draw(uniqueID, position.x, Main::Inst()->getRenderHeight() - height, width, height);
}

void Buff::extend()
{
	active = true;
	timer.start();
}
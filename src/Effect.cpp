#include "Effect.h"
#include "Main.h"
#include "TextureLoader.h"
#include "SoundLoader.h"
#include "Camera.h"
#include "World.h"

Effect::Effect(int effectID, int x, int y, int row) : frameTimer(true)
{
	uniqueID = effectID;
	position.set(x, y);
	currentRow = row;
	Load();
}

Effect::Effect(int effectID, int x, int y, int row, int _minATT, int _maxATT, int _critChance) : frameTimer(true)
{
	uniqueID = effectID;
	position.set(x, y);
	currentRow = row;
	minATT = _minATT;
	maxATT = _maxATT;
	critChance = _critChance;
	Load();
}

void Effect::Load()
{
	attacked = false;
	if (uniqueID == SummonMagicEffect)
	{
		width = 300;
		height = 230;
		animatedSpeed = 8;
		numFrames = 8;
		position.y -= height;
		position.x -= width / 2;
		if (currentRow == 0)
			position.x -= 100;
		else
			position.x += 100;
		return;
	}
	if (uniqueID == SpeedupSkillEffect)
	{
		width = 65;
		height = 80;
		animatedSpeed = 10;
		numFrames = 5;
		return;
	}
}

void Effect::update()
{
	VisiableCheck();
	if (frameTimer.getTicks() > animatedSpeed*numFrames)
		active = false;
	currentFrame = int(((frameTimer.getTicks() / animatedSpeed) % numFrames));

	if (uniqueID == SummonMagicEffect && currentFrame == 3 && !attacked )
	{
		attacked = true;
		Vector2D pos(position.x + 90, position.y + 210);
		World::Inst()->newProjectile(SummonMagicProjectile, pos, 0, 0, minATT, maxATT, critChance, true);
		SoundLoader::Inst()->playSound(SummonMagicHitSound);
		return;
	}
	if (uniqueID == SpeedupSkillEffect)
	{
		const Player* player = Camera::Inst()->getTarget();
		position.y = player->position.y + player->height - height;
		position.x = player->entityCenter.x - width / 2;
	}
}

void Effect::draw()
{
	if (visiable)
		TextureLoader::Inst()->drawFrame(uniqueID, position.x - Camera::Inst()->getPosition().x + Main::Inst()->getRenderWidth() / 2, position.y - Camera::Inst()->getPosition().y + Main::Inst()->getRenderHeight() / 2, width, height, currentRow, currentFrame, angle, alpha);
}

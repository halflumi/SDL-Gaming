#include "Projectile.h"
#include "IDSheet.h"
#include "Main.h"
#include "World.h"
#include "TextureLoader.h"
#include "Camera.h"

Projectile::Projectile(Vector2D* pos, string id, int _worldID, float velocity_x, float velocity_y, bool gravitational)
{
	position = *pos;
	uniqueID = id;
	worldID = _worldID;
	velocity.x = velocity_x;
	velocity.y = velocity_y;
	load();
}

void Projectile::load()
{
	if (uniqueID == IchorKnifeProjectile)
	{
		width = 14;
		height = 28;
	}
}

void Projectile::update()
{
	Entity::update();
	if (position.x - Camera::Inst()->getPosition().x < Main::Inst()->getWindowWidth() / 2)
		visiable = true;
	else if (Camera::Inst()->getPosition().x - (position.x + width) < Main::Inst()->getWindowWidth() / 2)
		visiable = true;
	else
		visiable = false;
	//angle = atan2((double)velocity.y, (double)velocity.x);
	//velocity.x -= 1.0f;
	if (life > 60)
		kill();
	life++;
}

void Projectile::draw()
{
	if(visiable)
		TextureLoader::Inst()->drawFrame(uniqueID, position.x - Camera::Inst()->getPosition().x + Main::Inst()->getWindowWidth() / 2, position.y, width, height, currentRow, currentFrame, angle, alpha);
}

void Projectile::kill()
{
	active = false;
}
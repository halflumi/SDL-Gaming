#include "Entity.h"
#include "World.h"
#include "Dice.h"

void Entity::update()
{
	entityCenter.set(position.x + width / 2, position.y + height / 2);

	if (velocity.x == 0)
		velocity.x += acceleration.x;
	else if (velocity.x > 0)
	{
		if (velocity.x + acceleration.x > maxSpeed)
			velocity.x = maxSpeed;
		else
			velocity.x += acceleration.x;
	}
	else
	{
		if (velocity.x + acceleration.x < -maxSpeed)
			velocity.x = -maxSpeed;
		else
			velocity.x += acceleration.x;
	}
	if (velocity.y < MAXFALLINGSPEED)
		velocity.y += acceleration.y;

	//position += velocity;
}

void Entity::heal(int point)
{
	life = life + point > maxlife ? maxlife : life + point;
	Vector2D textShift(position.x + width / 2 + Dice::Inst()->randInverse(40), position.y + Dice::Inst()->randInverse(40));
	World::Inst()->createText(textShift, 0.f, -0.5f, to_string(point), segoeui22, COLOR_GREEN, 120);
}
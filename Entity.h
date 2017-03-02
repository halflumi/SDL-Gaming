#pragma once
#include "Object.h"
#include "Vector2D.h"

#define GRAVITY 0.10f
#define MAXFALLINGSPEED 10.0f

class Entity : public Object
{
protected:
	int worldID;
	int life;

	bool movingLeft, movingRight;
	bool jumped;
	bool midair;
	float maxSpeed;
	Vector2D velocity;
	Vector2D acceleration;

	Entity() : maxSpeed(5.0f), velocity(0.0f, 0.0f), acceleration(0.0f, GRAVITY), life(0)
	{
		movingLeft = false; 
		movingRight = false;
		jumped = false;
		midair = false;
	}
public:

	virtual void update()
	{
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

		position += velocity;
	}

	Vector2D& getPosition() { return position; }
	Vector2D& getVelocity() { return velocity; }
};
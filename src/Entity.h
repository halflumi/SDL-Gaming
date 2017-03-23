#pragma once
#include "Object.h"

#define GRAVITY 0.50f
#define MAXFALLINGSPEED 10.0f

class Entity : public Object
{
protected:
	bool movingLeft, movingRight;
	bool jumped;
	int midair;
	float maxSpeed;
	Vector2D velocity;
	Vector2D acceleration;

	Entity() : maxSpeed(5.0f), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f), entityCenter(0.f,0.f), life(0), maxlife(0), minATT(0), maxATT(0), defense(0)
	{
		dead = false;

		movingLeft = false; 
		movingRight = false;
		jumped = false;
		midair = false;
	}
public:
	int worldID;
	bool dead;
	Vector2D entityCenter;

	string name;
	int level;
	int exp;
	int life;
	int maxlife;
	int mana;
	int maxmana;
	int minATT;
	int maxATT;
	int defense;
	int critChance;

	Vector2D& getVelocity() { return velocity; }

	virtual void update();
	virtual void heal(int point);
	virtual void onHit(int damage, int critChance) {};
};
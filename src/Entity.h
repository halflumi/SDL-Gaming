#pragma once
#include "Object.h"

#define GRAVITY 0.50f
#define MAXFALLINGSPEED 10.0f

class Entity : public Object
{
protected:
	bool movingLeft, movingRight;
	bool jumped;
	short midair;
	Vector2D acceleration;
	int invulnerableInterval;
	int invulnerableTick;

	Entity() : maxSpeed(5.0f), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f), entityCenter(0.f,0.f), invulnerableTick(0), invulnerableInterval(60)
	{
		dead = false;
		facingLeft = false;
		facingRight = true;
		movingLeft = false; 
		movingRight = false;
		jumped = false;
		midair = false;
		gold = 0;
		life = 0;
		maxlife = 0;
		minATT = 0;
		maxATT = 0;
		defense = 0;
	}
public:
	Vector2D entityCenter;
	Vector2D velocity;
	string name;
	bool facingLeft, facingRight;
	bool dead;
	bool friendly;
	float maxSpeed;
	int worldID;
	int level;
	int gold;
	int exp;
	int life;
	int maxlife;
	int mana;
	int maxmana;
	int minATT;
	int maxATT;
	int defense;
	int critChance;

	virtual void update();
	virtual void heal(int point);
	virtual void onHit(int damage, int critChance) {};
};
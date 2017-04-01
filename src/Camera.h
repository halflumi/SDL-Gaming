#pragma once
#include "Player.h"

class Camera
{
private:
	Camera() : target(NULL), position(0, 0), velocity(0,0) { };
	~Camera() { };
	static Camera* INSTANCE;
public:
	static Camera* Inst()
	{
		if (INSTANCE == 0)
			INSTANCE = new Camera();
		return INSTANCE;
	}
private:
	Player* target;
	Vector2D position;
	Vector2D velocity;
public:
	const Player* getTarget() const { return target; }
	Player* getTarget_nonConst() const { return target; }
	const Vector2D getPosition() const { return position; }

	void focus(Player* _target) { target = _target; position = _target->position; }
	void upadte();
};
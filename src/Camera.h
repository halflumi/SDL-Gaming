#pragma once
#include "Player.h"

class Camera
{
private:
	Camera() : target(NULL), position(0, 0) { };
	~Camera() { };
	static Camera* INSTANCE;

	Player* target;
	Vector2D position;
public:
	static Camera* Inst()
	{
		if (INSTANCE == 0)
			INSTANCE = new Camera();
		return INSTANCE;
	}

	void setPosition(float x, float y) { position.x = x; position.y = y; }
	const Player* getTarget() const { return target; }
	const Vector2D getPosition() const { return position; }

	void Focus(Player* _target);
};
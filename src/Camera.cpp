#include "Camera.h"
#include "Main.h"
#include "World.h"

Camera* Camera::INSTANCE = new Camera();

void Camera::upadte()
{
	int leftScreenBound = Main::Inst()->getRenderWidth() / 2;
	int rightScreenBound = World::Inst()->getWorldWidth() - leftScreenBound;
	int upperScreenBound = Main::Inst()->getRenderHeight() / 2;
	int bottomScreenBound = World::Inst()->getWorldHeight() - Main::Inst()->getRenderHeight() / 2;

	float x, y;
	//x centeralized view
	if (target->position.x < leftScreenBound) // left bound
		x = leftScreenBound;
	else if (target->position.x > rightScreenBound) // right bound
		x = rightScreenBound;
	else
		x = target->position.x;
	//y centeralized view
	if (target->position.y < upperScreenBound) // upper bound
		y = upperScreenBound;
	else if (target->position.y > bottomScreenBound) // bottom bound
		y = World::Inst()->getWorldHeight() - upperScreenBound;
	else
		y = target->position.y;

	//x speedlized view
	if (x == leftScreenBound) // left bound
		velocity.x = -5.f;
	else if (x == rightScreenBound) // right bound
		velocity.x = 5.f;
	else if (x - position.x > 100)
		velocity.x = target->velocity.x == 0 ? 20.f : target->velocity.x;
	else if (x - position.x < -100)
		velocity.x = target->velocity.x == 0 ? -20.f : target->velocity.x;
	else
		velocity.x = 0;
	//y default view
	position.y = y;

	//if reached bounds
	Vector2D newPosition = position + velocity;
	if (newPosition.x < leftScreenBound) // left bound 
		position.x = leftScreenBound;
	else if (newPosition.x > rightScreenBound) // right bound
		position.x = rightScreenBound;
	else
		position.x = newPosition.x;
}
#pragma once
#include "IDSheet.h"
#include "Entity.h"

class Player : public Entity
{
private:
	bool focused;
	Vector2D display_pos;

	void load();
	
	void HandleInput();
	void HandleMovement();
	void HandleDisplay();

	bool CollisionCheck_X(float x);
	bool CollisionCheck_Y(float y);
	void HitGround();
public:
	Player(int x, int y, string id);

	void setFocused() { focused = true; }
	void removeFocused() { focused = false; }
	Vector2D& getDisplayPos() { return display_pos; }

	string type() { return TypePlayer; }

	void update();
	void draw();
};
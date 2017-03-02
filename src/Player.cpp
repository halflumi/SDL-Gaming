#include <SDL_rect.h>
#include "Main.h"
#include "IDSheet.h"
#include "Inputor.h"
#include "TextureLoader.h"
#include "SoundLoader.h"
#include "World.h"
#include "Player.h"
#include "Dice.h"
#include "Camera.h"
#include "Projectile.h"

#define PLAYERACCERLATION 0.8f

Player::Player(int x, int y, string id)
{
	position.x = x;
	position.y = y;
	uniqueID = id;
	display_pos = position;
	maxSpeed = 4.0f;
	acceleration.y = GRAVITY;
	load();
}

void Player::load()
{
	width = 50;
	height = 100;
}

void Player::update()
{
	HandleInput();
	HandleMovement();
	HandleDisplay();
}

void Player::draw()
{
	TextureLoader::Inst()->drawFrame(uniqueID, display_pos.x, display_pos.y, width, height, currentRow, currentFrame, angle, alpha);
}

void Player::HandleInput()
{
	if (Inputor::Inst()->isKeyDown(SDL_SCANCODE_A))
	{
		movingLeft = true;
		movingRight = false;
		currentRow = 1;
		acceleration.x = -PLAYERACCERLATION;
	}
	else if (Inputor::Inst()->isKeyDown(SDL_SCANCODE_D))
	{
		movingRight = true;
		movingLeft = false;
		currentRow = 2;
		acceleration.x = PLAYERACCERLATION;
	}
	else
	{
		movingLeft = false;
		movingRight = false;
	}

	if (Inputor::Inst()->isKeyDown(SDL_SCANCODE_SPACE))
		jumped = true;

	//for projectile test purpose
	if (Inputor::Inst()->getMouseButtonState(MOUSE_LEFT))
	{
		World::Inst()->newProjectile(&position, IchorKnifeProjectile, 5, 0);
	}
}

void Player::HandleMovement()
{
	////calculate acc and direction
	if (movingLeft)
	{
		acceleration.x = -PLAYERACCERLATION;
		if (velocity.x > 0) //turn around from right
			velocity.x = 0;
	}
	else if (movingRight)
	{
		acceleration.x = PLAYERACCERLATION;
		if (velocity.x < 0) //turn around from left
			velocity.x = 0;
	}
	else
	{
		velocity.x = 0;
		acceleration.x = 0;
	}

	if (jumped && !midair)
	{
		midair = true;
		velocity.y = -7.0f;
	}
	if (midair)
	{
		acceleration.y = GRAVITY;
		maxSpeed = 3.0f;
	}
		
		

	//calculate speed
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
	if(velocity.y < MAXFALLINGSPEED)
		velocity.y += acceleration.y;

	//calculate position
	Vector2D newposition = position + velocity;

	if (!CollisionCheck_X(newposition.x))
		position.x = newposition.x;
	if (!CollisionCheck_Y(newposition.y))
		position.y = newposition.y;
}

void Player::HandleDisplay()
{
	//x centeralized view
	if (position.x - Main::Inst()->getWindowWidth() / 2 < 0)
	{
		display_pos.x = position.x;
		if (focused)
			Camera::Inst()->setPosition(Main::Inst()->getWindowWidth() / 2, 0);
	}
	else if (position.x + Main::Inst()->getWindowWidth() / 2 - World::Inst()->getWorldWidth() > 0)
	{
		display_pos.x = Main::Inst()->getWindowWidth() - (World::Inst()->getWorldWidth() - position.x);
		if (focused)
			Camera::Inst()->setPosition(World::Inst()->getWorldWidth() - Main::Inst()->getWindowWidth() /2 , 0);
	}
	else
	{
		display_pos.x = Main::Inst()->getWindowWidth() / 2;
		if (focused)
			Camera::Inst()->setPosition(position.x, 0);
	}
		
	//y default view
	display_pos.y = position.y;

	if (movingLeft || movingRight)
	{
		if (!Dice::Inst()->rand(20))
		{
			switch (Dice::Inst()->rand(4))
			{
			case 0:
				SoundLoader::Inst()->playSound(WalkOnSnow1);
				break;
			case 1:
				SoundLoader::Inst()->playSound(WalkOnSnow2);
				break;
			case 2:
				SoundLoader::Inst()->playSound(WalkOnSnow3);
				break;
			case 3:
				SoundLoader::Inst()->playSound(WalkOnSnow4);
				break;
			}
		}
		currentFrame = int(((SDL_GetTicks() / 250) % 4));
	}
	else
		currentFrame = 0;
}

bool Player::CollisionCheck_X(float x)
{
	//touch world border
	if (x < 0)
		return true;
	if (x + width > World::Inst()->getWorldWidth())
		return true;
		
	//touch tile or enemy
	vector<Object*>& objects = World::Inst()->getLayer_tile();
	int i;
	int len = objects.size();
	for (i = 0; i < len; i++)
	{
		if (objects[i]->type() != TypeTile)
			continue;

		float& objectLeft = objects[i]->getPosition().x;
		float objectRight = objectLeft + objects[i]->getWidth();
		float& objectTop = objects[i]->getPosition().y;
		float objectBottom = objectTop + objects[i]->getHeight();


		if (!(position.y >= objectBottom || position.y + height <= objectTop))
		{
			if (x + width <= objectLeft || x >= objectRight)
				continue;
			else
			{
				if (movingRight)
					velocity.x = 0.4f;
				return true;
			}
		}
	}
	//cout << position.x << endl;
	return false;
}

bool Player::CollisionCheck_Y(float y)
{
	if (y < 0)
		return true;
	if (y + height > World::Inst()->getWorldHeight())
	{
		HitGround();
		return true;
	}

	//touch tile or enemy
	vector<Object*>& objects = World::Inst()->getLayer_tile();
	int i;
	int len = objects.size();
	for (i = 0; i < len; i++)
	{
		if (objects[i]->type() != TypeTile)
			continue;

		float& objectLeft = objects[i]->getPosition().x;
		float objectRight = objectLeft + objects[i]->getWidth();
		float& objectTop = objects[i]->getPosition().y;
		float objectBottom = objectTop + objects[i]->getHeight();
		
		//if (!(position.x + width <= objectLeft || position.x >= objectRight))
		//{
		//	if (position.y > objectBottom || position.y + height < objectTop)
		//		continue;
		//	else
		//		return true;
		//}
	}
	return false;
}

void Player::HitGround()
{
	midair = false;
	jumped = false;
	velocity.y = 0;
	acceleration.y = 0;
	maxSpeed = 4.0f;
}
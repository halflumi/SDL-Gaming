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

#define PLAYERACCERLATION 0.7f
#define AIRACCELERATION 0.3f
#define MIDAIRACCERLATION 0.05f
#define DEFAULTMAXSPEED 5.0f
#define JUMPSPEED -10.f
#define LADDERSPEED 1.0f
#define LADDERJUMPSPEED -7.f

Player::Player(int x, int y, string id)
{
	name = "Who am I?";
	position.set(x, y);
	uniqueID = id;
	display_pos = position;
	onLadder = false;
	movingUp = false;
	movingDown = false;
	characterPanel = new CharacterPanel();
	inventory = new Inventory();
	characterPanel->active = false;
	inventory->active = false;
	dialog = NULL;
	selectingItem = NULL;
	rightHand_equ = characterPanel->rightHandSlot;
	leftHand_equ = characterPanel->leftHandSlot;
	helmet_equ = characterPanel->helmetSlot;
	keyCooldown = new MyTimer(true);
	mouseCooldown = new MyTimer(true);
	Load();
}

void Player::Load()
{
	width = 50;
	height = 100;
	//rpg properties
	maxSpeed = DEFAULTMAXSPEED;
	acceleration.y = GRAVITY;
	level = 1;
	exp = 0;
	expToNextLevel = 10;
	life = 100;
	maxlife = 100;
	mana = 30;
	maxmana = 100;
	baseATT = 10;
	baseDEF = 2;
	critChance = 10;

	meleeProjectile = NULL;
	attackInterval = 30;
	attackTick = 0;
	invulnerableInterval = 60;
	invulnerableTick = 0;
}

void Player::update()
{
	isLevelingup();
	updateAttributes();
	HandleInput();
	HandleMovement();
	HandleDisplay();

	if (meleeProjectile != NULL && meleeProjectile->active)
		meleeProjectile->update();

	if (characterPanel->active)
		characterPanel->update();
	if (inventory->active)
		inventory->update();

	if (selectingItem != NULL)
	{
		if (!inventory->active)
		{
			selectingItem->beingPicked = false;
			if (selectingItem->index == -1)
				inventory->addItem(selectingItem->getUniqueID(), selectingItem->getWidth(), selectingItem->getHeight(), selectingItem->stack, selectingItem->maxStack);
			selectingItem = NULL;
		}
		else
		{
			selectingItem->setPosition(Inputor::Inst()->getMouseRelativePosition());
			selectingItem->update();
		}
	}
}

void Player::draw()
{
	TextureLoader::Inst()->drawFrame(uniqueID, display_pos.x, display_pos.y, width, height, currentRow, currentFrame, angle, alpha);

	if (meleeProjectile != NULL && meleeProjectile->active)
		meleeProjectile->draw();

	if (dialog != NULL)
		dialog->draw();
	if (characterPanel->active)
		characterPanel->draw();
	if (inventory->active)
		inventory->draw();
	if (selectingItem != NULL)
		selectingItem->draw();
}

void Player::isLevelingup()
{
	if (exp >= expToNextLevel)
	{
		level++;
		exp -= expToNextLevel;
		SoundLoader::Inst()->playSound(LevelupSound);
		switch (level)
		{
		case 2:		expToNextLevel = 25;
			break;
		case 3:		expToNextLevel = 50;
			break;
		case 4:		expToNextLevel = 100;
			break;
		}
	}
}

void Player::updateAttributes()
{
	minATT = baseATT + rightHand_equ->minATT;
	maxATT = baseATT + 5 + rightHand_equ->maxATT;
	defense = baseDEF;

	if (attackTick)
	{
		attackTick++;
		if (attackTick == attackInterval)
			attackTick = 0;
	}
	if (invulnerableTick)
	{
		invulnerableTick++;
		if (invulnerableTick == invulnerableInterval)
			invulnerableTick = 0;
		if (invulnerableTick % 5 == 0)
		{
			if (alpha == 255)
				alpha = 50;
			else
				alpha = 255;
		}
	}
	else
		alpha = 255;
}

void Player::HandleInput()
{
	if (dialog != NULL)
	{
		movingRight = false;
		movingLeft = false;
		if (Inputor::Inst()->getMouseButtonState(MOUSE_LEFT) && mouseCooldown->getTicks() > CLICKCOOLDOWN)
		{
			Dialog* temp = dialog->next;
			delete dialog;
			dialog = temp;

			mouseCooldown->start();
		}
		else
			return;
	}

	if (Inputor::Inst()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		characterPanel->active = false;
		inventory->active = false;
	}
	if (Inputor::Inst()->isKeyDown(SDL_SCANCODE_W))
	{
		if(!onLadder)
			CheckInteractive();
		else
		{
			movingUp = true;
			movingDown = false;
			currentRow = 3;
		}
	}
	else if (Inputor::Inst()->isKeyDown(SDL_SCANCODE_S))
	{
		if (onLadder)
		{
			movingDown = true;
			movingUp = false;
			currentRow = 3;
		}
	}
	else
	{
		movingUp = false;
		movingDown = false;
	}
	if (Inputor::Inst()->isKeyDown(SDL_SCANCODE_LCTRL))
	{
		CheckPickup();
	}
	if (Inputor::Inst()->isKeyDown(SDL_SCANCODE_C) && keyCooldown->getTicks() > PRESSCOOLDOWN)
	{
		characterPanel->active = !characterPanel->active;
		keyCooldown->start();
	}
	if (Inputor::Inst()->isKeyDown(SDL_SCANCODE_I) && keyCooldown->getTicks() > PRESSCOOLDOWN)
	{
		inventory->active = !inventory->active;
		keyCooldown->start();
	}

	if (Inputor::Inst()->isKeyDown(SDL_SCANCODE_A) && !Inputor::Inst()->isKeyDown(SDL_SCANCODE_D))
	{
		movingLeft = true;
		movingRight = false;
		if (!midair)
			currentRow = 1;
		else
			currentRow = 0;

		acceleration.x = -PLAYERACCERLATION;
	}
	else if (Inputor::Inst()->isKeyDown(SDL_SCANCODE_D) && !Inputor::Inst()->isKeyDown(SDL_SCANCODE_A))
	{
		movingRight = true;
		movingLeft = false;
		if (!midair)
			currentRow = 2;
		else
			currentRow = 0;

		acceleration.x = -MIDAIRACCERLATION;
	}
	else
	{
		movingLeft = false;
		movingRight = false;
	}

	if (Inputor::Inst()->isKeyDown(SDL_SCANCODE_SPACE))
	{
		jumped = true;
		onLadder = false;
	}

	if (characterPanel->active && characterPanel->outsideCheckMouseOver())
	{
		if (Inputor::Inst()->getMouseButtonState(MOUSE_LEFT) && characterPanel->outsideCheckMouseTitle())
		{
			characterPanel->addPosition(Inputor::Inst()->getMouseMotionVector()); // **********motion is too sensitive
		}
	}
	else if (inventory->active && inventory->outsideCheckMouseOver())
	{
		if (Inputor::Inst()->getMouseButtonState(MOUSE_LEFT) && inventory->outsideCheckMouseTitle())
		{
			inventory->addPosition(Inputor::Inst()->getMouseMotionVector()); // **********motion is too sensitive
		}
	}
	else if (selectingItem != NULL && Inputor::Inst()->getMouseButtonState(MOUSE_LEFT))
	{
		Vector2D* mousepos = Inputor::Inst()->getMouseDefinitePosition();
		Vector2D direction = *mousepos - entityCenter;
		direction.normalize();
		direction.x *= 4;
		direction.y *= 10;
		World::Inst()->newItem(entityCenter.x, entityCenter.y,direction.x, direction.y, selectingItem->getUniqueID(), selectingItem->stack);
		selectingItem->setUniqueID("");
		selectingItem->active = false;
		selectingItem->beingPicked = false;
		selectingItem = NULL;

		mouseCooldown->start(100); // **********cooldown broken
	}
	else
	{
		if (!attackTick && Inputor::Inst()->getMouseButtonState(MOUSE_LEFT))
		{
			Attacking();
		}
		if (!attackTick && mana > 0 && Inputor::Inst()->getMouseButtonState(MOUSE_RIGHT))
		{
			attackTick = 1;
			mana -= 3;
			Vector2D* mousepos = Inputor::Inst()->getMouseDefinitePosition();
			Vector2D direction = *mousepos - entityCenter;
			direction.normalize();
			direction.x *= 10;
			direction.y *= 5;
			for (int i = 0; i < 10; i++)
			{
				Vector2D randpos(entityCenter.x + Dice::Inst()->rand(80), entityCenter.y + Dice::Inst()->randInverse(80));
				World::Inst()->newProjectile(randpos, IchorKnifeProjectile, direction.x, direction.y, this);
				SoundLoader::Inst()->playSound(AttackSound);

				life--;
			}
		}
		mouseCooldown->start();
	}
}

void Player::Attacking()
{
	if (rightHand_equ->getUniqueID() == OrichalcumShortsword)
	{
		attackTick = 1;
		Vector2D* mousepos = Inputor::Inst()->getMouseDefinitePosition();
		Vector2D direction = *mousepos - entityCenter;
		
		if (meleeProjectile != NULL)
			delete meleeProjectile;
		if (direction.x > 0)
		{
			Vector2D swordpos(position.x + width, entityCenter.y - 20.f);
			meleeProjectile = new Projectile(swordpos, OrichalcumShortswordProjectile, -1, 0.1f, 0.f, this);
		}
		else
		{
			Vector2D swordpos(position.x, entityCenter.y - 20.f);
			meleeProjectile = new Projectile(swordpos, OrichalcumShortswordProjectile, -1, -0.1f, 0.f, this);
		}
			
		SoundLoader::Inst()->playSound(AttackSound);
	}
	else
	{
		attackTick = 1;
		Vector2D* mousepos = Inputor::Inst()->getMouseDefinitePosition();
		Vector2D direction = *mousepos - entityCenter;
		direction.normalize();
		direction.x *= 10;
		direction.y *= 5;
		World::Inst()->newProjectile(entityCenter, IchorKnifeProjectile, direction.x, direction.y, this);
		SoundLoader::Inst()->playSound(AttackSound);

		life--;
		Vector2D textShift(position.x + width / 2 + Dice::Inst()->randInverse(20), position.y + Dice::Inst()->randInverse(20));
		World::Inst()->createText(120, textShift, 0.f, -0.5f, "-1s", segoeui22, { 255, 0, 0 });
	}
}

void Player::HandleMovement()
{
	if (onLadder)
	{
		if (movingUp)
		{
			velocity.y = -LADDERSPEED;
		}
		else if (movingDown)
		{
			velocity.y = LADDERSPEED;
		}
		else
		{
			velocity.y = 0;
		}
		position.y += velocity.y;
		return;
	}
	////calculate acc and direction
	if (!midair)
	{
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
	}
	else
	{
		if (movingLeft)
		{
			acceleration.x = -AIRACCELERATION;
		}
		else if (movingRight)
		{
			acceleration.x = AIRACCELERATION;
		}
	}

	if (jumped && !midair)
	{
		midair = true;
		if (!onLadder)
			velocity.y = JUMPSPEED;
		else
			velocity.y = LADDERJUMPSPEED;
	}
	if (midair)
	{
		acceleration.y = GRAVITY;
		//acceleration.x = -0.1f;
	}

	//calculate speed
	Entity::update();

	//calculate position
	Vector2D newposition = position + velocity;

	if (!CheckCollision_tileX(newposition.x))
		position.x = newposition.x;
	if (!CheckCollision_tileY(newposition.y))
		position.y = newposition.y;
	CheckCollision_hostile(newposition);
}

void Player::HandleDisplay()
{
	int x, y;
	//x centeralized view
	if (position.x - Main::Inst()->getRenderWidth() / 2 < 0)
	{
		display_pos.x = position.x;
		if (focused)
			x = Main::Inst()->getRenderWidth() / 2;
	}
	else if (position.x + Main::Inst()->getRenderWidth() / 2 - World::Inst()->getWorldWidth() > 0)
	{
		display_pos.x = Main::Inst()->getRenderWidth() - (World::Inst()->getWorldWidth() - position.x);
		if (focused)
			x = World::Inst()->getWorldWidth() - Main::Inst()->getRenderWidth() / 2;
	}
	else
	{
		display_pos.x = Main::Inst()->getRenderWidth() / 2;
		if (focused)
			x = position.x;
	}
	//y centeralized view
	if (position.y - Main::Inst()->getRenderHeight() / 2 < 0)
	{
		display_pos.y = position.y;
		if (focused)
			y = Main::Inst()->getRenderHeight() / 2;
	}
	else if (position.y + Main::Inst()->getRenderHeight() / 2 - World::Inst()->getWorldHeight() > 0)
	{
		display_pos.y = Main::Inst()->getRenderHeight() - (World::Inst()->getWorldHeight() - position.y);
		if (focused)
			y = World::Inst()->getWorldHeight() - Main::Inst()->getRenderHeight() / 2;
	}
	else
	{
		display_pos.y = Main::Inst()->getRenderHeight() / 2;
		if (focused)
			y = position.y;
	}
	if (focused)
		Camera::Inst()->setPosition(x, y);
	//cout << Camera::Inst()->getPosition().x << ' ' << Camera::Inst()->getPosition().y << endl;


	if (movingLeft || movingRight || movingUp || movingDown)
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

bool Player::CheckCollision_tileX(float x)
{
	//touch world border
	if (x < 0)
		return true;
	if (x + width > World::Inst()->getWorldWidth())
		return true;

	//touch tile or enemy
	vector<Tile*>& objects = World::Inst()->getLayer_tile();
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

bool Player::CheckCollision_tileY(float y)
{
	if (y < 0)
		return true;
	if (y + height > World::Inst()->getWorldHeight())
	{
		HitGround();
		return true;
	}

	//touch tile or enemy
	vector<Tile*>& objects = World::Inst()->getLayer_tile();
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


	}
	return false;
}

void Player::CheckCollision_hostile(Vector2D newpos)
{
	if (invulnerableTick > 0)
		return;
	int pRight = newpos.x + width;
	int pBottom = newpos.y + height;

	vector<Entity*>& entities = World::Inst()->getLayer_entity();
	int i;
	int len = entities.size();
	for (i = 0; i < len; i++)
	{
		if (entities[i]->type() != TypeHostile)
			continue;
		if (!entities[i]->active)
			continue;

		if (pBottom <= entities[i]->getPosition().y)
			continue;
		if (newpos.y >= entities[i]->getPosition().y + entities[i]->getHeight())
			continue;
		if (pRight <= entities[i]->getPosition().x)
			continue;
		if (newpos.x >= entities[i]->getPosition().x + entities[i]->getWidth())
			continue;

		//onhit
		int damage = Dice::Inst()->rand(entities[i]->minATT, entities[i]->maxATT) - defense;
		life -= damage;
		Vector2D textShift(entityCenter.x + Dice::Inst()->randInverse(20), position.y + Dice::Inst()->randInverse(20));
		World::Inst()->createText(60, textShift, 0, -0.1f, to_string(damage), segoeui22, { 0,255,0 });
		velocity.y = -1.f;
		if (entities[i]->getPosition().x > position.x)
			velocity.x = -5.f;
		else
			velocity.x = 5.f;
		invulnerableTick = 1;
		return;
	}
}

void Player::HitGround()
{
	midair = false;
	jumped = false;
	velocity.y = 0;
	acceleration.y = 0;
	maxSpeed = DEFAULTMAXSPEED;
}

void Player::CheckInteractive()
{
	vector<Entity*>& entities = World::Inst()->getLayer_entity();
	int i;
	int len = entities.size();
	for (i = 0; i < len; i++)
	{
		float pRight = position.x + width;
		float& oLeft = entities[i]->getPosition().x;
		if (pRight < oLeft)
			continue;
		float& pLeft = position.x;
		float oRight = entities[i]->getPosition().x + entities[i]->getWidth();
		if (pLeft > oRight)
			continue;
		float pBottom = position.y + height;
		float& oTop = entities[i]->getPosition().y;
		if (pBottom < oTop)
			continue;
		float& pTop = position.y;
		float oBottom = entities[i]->getPosition().y + entities[i]->getHeight();
		if (pTop > oBottom)
			continue;

		if (entities[i]->getUniqueID() == TestPortal)
		{
			if (entityCenter.x <= oRight && entityCenter.x >= oLeft && entityCenter.y >= oTop && entityCenter.y <= oBottom)
			{
				DoInteractive(entities[i]->getUniqueID());
				return;
			}
		}
	}

	vector<Sprite*>& objects = World::Inst()->getLayer_foreground();
	len = objects.size();
	for (i = 0; i < len; i++)
	{
		if (objects[i]->outsideCheckPlayerWithin()) // player in range
		{
			if (objects[i]->getUniqueID() == LadderSprite)
			{
				onLadder = true;
				jumped = false;
				midair = false;
				currentRow = 3;
				return;
			}
			if (objects[i]->getUniqueID() == MapGate)
			{
				World::Inst()->changeMap(MapTest02);
				return;
			}
			if (objects[i]->getUniqueID() == MapGate2)
			{
				World::Inst()->changeMap(MapTest01);
				return;
			}
		}
	}
}

void Player::DoInteractive(string id)
{
	if (id == TestPortal)
	{
		SoundLoader::Inst()->playSound(PortalNoise);
		position.x = 2500;
		position.y = World::Inst()->getWorldHeight() - height;
	}
}

void Player::CheckPickup()
{
	vector<Entity*>& objects = World::Inst()->getLayer_entity();
	int i;
	int len = objects.size();
	for (i = 0; i < len; i++)
	{
		if (objects[i]->type() != TypeItem || objects[i]->dead)
			continue;
		
		float pBottom = position.y + height;
		if (pBottom <= objects[i]->getPosition().y)
			continue;
		if (position.y >= objects[i]->getPosition().y + objects[i]->getHeight())
			continue;

		float pRight = position.x + width;
		if (pRight <= objects[i]->getPosition().x)
			continue;
		if (position.x >= objects[i]->getPosition().x + objects[i]->getWidth())
			continue;

		if (inventory->addItem((Item*)objects[i]))
		{
			SoundLoader::Inst()->playSound(PickupSound);
			objects[i]->active = false;
			objects[i]->dead = true;
		}
		
	}
}
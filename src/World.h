#pragma once
#include <vector>
#include "Object.h"
#include "Player.h"
#include "Textbox.h"
#include "Projectile.h"
#include "Tile.h"
#include "Sprite.h"

using namespace std;

class World
{
	enum LayerType
	{
		LAYER_BACKGROUND,
		LAYER_TILE,
		LAYER_FOREGROUND,
		LAYER_ENTITY,
		LAYER_PROJECTILE,
		LAYER_PLAYER,
		LAYER_TEXT
	};
private:
	static World* INSTANCE;
	World() : newGame(false) {};
	World(const World&);

	MyTimer timer;
	bool newGame;
	int backgroundID;
	int width;
	int height;
	Textbox healthNumText;
	Textbox manaNumText;
	Textbox xpNumText;

	vector<Sprite*> layer_background;
	vector<Tile*> layer_tile;
	vector<Sprite*> layer_foreground;
	vector<Entity*> layer_entity;
	vector<Projectile*> layer_projectile;
	vector<Player*> layer_player;
	vector<Textbox*> layer_text;

	void RenderBackground();
	void RenderUI();
	void AttackWave();
public:
	int currentMapID;

	static World* Inst()
	{
		if (INSTANCE == 0)
		{
			INSTANCE = new World();
			return INSTANCE;
		}
		return INSTANCE;
	}

	vector<Sprite*>& getLayer_background() { return layer_background; }
	vector<Tile*>& getLayer_tile() { return layer_tile; }
	vector<Sprite*>& getLayer_foreground() { return layer_foreground; }
	vector<Entity*>& getLayer_entity() { return layer_entity; }
	vector<Projectile*>& getLayer_projectile() { return layer_projectile; }
	vector<Player*>& getLayer_player() { return layer_player; }
	vector<Textbox*>& getLayer_text() { return layer_text; }
	int getWorldWidth() { return width; }
	int getWorldHeight() { return height; }

	void clearWorld();
	void startNewGame(bool demonic);
	void startOldGame() { newGame = false; }
	void initialize();
	void changeMap(int mapID, MapChangeType form);
	void updating();
	void rendering();

	void newProjectile(int id, Vector2D pos, float velocity_x, float velocity_y, Entity* owner, bool gravitational = true);
	void createText(Vector2D pos, float velocity_x, float velocity_y, string text, int fontID, SDL_Color color, int lastingTime);
	void newHostile(int id, int x, int y);
	void newItem(int id, int stack, int x, int y);
	void newItem(int id, int stack, int x, int y, float velocity_x, float velocity_y);
};
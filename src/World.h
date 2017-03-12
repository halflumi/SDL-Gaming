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
	World() {};
	World(const World&);
	World& operator=(const World&) {};

	int currentMapID;
	string backgroundID;
	int width;
	int height;
	Textbox nameText;
	Textbox healthNumText;
	Textbox manaNumText;

	vector<Sprite*> layer_background;
	vector<Tile*> layer_tile;
	vector<Sprite*> layer_foreground;
	vector<Entity*> layer_entity;
	vector<Projectile*> layer_projectile;
	vector<Player*> layer_player;
	vector<Textbox*> layer_text;

	void ClearWorld();
	void RenderBackground();
	void RenderUI();
public:
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

	void initialize();
	void changeMap(int mapID);
	void updating();
	void rendering();

	void newProjectile(Vector2D pos, string id, float velocity_x, float velocity_y, Entity* owner, bool gravitational = true);
	void createText(int lastingTime, Vector2D pos, float velocity_x, float velocity_y, string text, string fontID, SDL_Color color = { 0,0,0 });
	void newHostile(int x, int y, string id);
	void newItem(int x, int y, string id, int stack);
	void newItem(int x, int y, float velocity_x, float velocity_y, string id, int stack);
};
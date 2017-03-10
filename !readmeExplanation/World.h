#pragma once
#include <vector>
#include "Object.h"
#include "Player.h"

using namespace std;

class World
{
	enum LayerType
	{
		LAYER_SPRITE = 0,
		LAYER_TILE,
		LAYER_ENTITY,
		LAYER_PROJECTILE,
		LAYER_PLAYER
	};
private:
	static World* INSTANCE;
	World();
	World(const World&);
	World& operator=(const World&) {};

	int mapNum;
	int width;
	int height;

	vector<vector<Object*>> layers;
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

	vector<Object*>& getLayer_sprite() { return layers[LAYER_SPRITE]; }
	vector<Object*>& getLayer_tile() { return layers[LAYER_TILE]; }
	vector<Object*>& getLayer_entity() { return layers[LAYER_ENTITY]; }
	vector<Object*>& getLayer_projectile() { return layers[LAYER_PROJECTILE]; }
	vector<Object*>& getLayer_player() { return layers[LAYER_PLAYER]; }
	int getWorldWidth() { return width; }
	int getWorldHeight() { return height; }

	void load();
	void updating();
	void rendering();
	void renderBackground();

	void newProjectile(Vector2D* pos, string id, float velocity_x, float velocity_y, bool gravitational = true);
	//void destroyProjectile(int worldID);
};
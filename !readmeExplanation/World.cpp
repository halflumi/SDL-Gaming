#include "World.h"
#include "Main.h"
#include "IDSheet.h"
#include "SoundLoader.h"
#include "TextureLoader.h"
#include "Camera.h"
#include "Tile.h"
#include "Sprite.h"
#include "Projectile.h"

#define LAYERCOUNT 5

World* World::INSTANCE = 0;

World::World() :layers(LAYERCOUNT)
{

}

void World::load()
{
	mapNum = 0;
	width = 3072;
	height = 600;
	//For Background Test purpose
	TextureLoader::Inst()->load(BackgroundFile, Background);
	//For Tile Test purpose
	TextureLoader::Inst()->load(Tile01File, Tile01);
	TextureLoader::Inst()->load(BrickFile, Brick);
	getLayer_tile().push_back(new Tile(1500, 300, Tile01));

	for (int i = 0; i < 10; i++)
		getLayer_tile().push_back(new Tile(47 * i, height - 37, Brick));
	for (int i = 10; i < 20; i++)
		getLayer_tile().push_back(new Tile(47 * i, height - 100, Brick));
	//For Sprite Test Purpose
	TextureLoader::Inst()->load(WaterMushroomFrameFile, WaterMushroomFrame);
	getLayer_sprite().push_back(new Sprite(1000, height - 136, WaterMushroomFrame));
	//For Entity Test Purpose
	TextureLoader::Inst()->load(PlayerFrameFile, PlayerFrame);
	Player* player = new Player(0, 0, PlayerFrame);
	getLayer_player().push_back(player);
	//For Projectile Test Purpose
	TextureLoader::Inst()->load(IchorKnifeProjectileFile, IchorKnifeProjectile);
	//Set camera on the player
	Camera::Inst()->Focus(player); 

	//For Sound Test Purpose
	//SoundLoader::Inst()->load(Music01File, Music01, SOUND_MUSIC);
	//SoundLoader::Inst()->playMusic(Music01, 2);
	SoundLoader::Inst()->load(WalkOnSnow1File, WalkOnSnow1, SOUND_SFX);
	SoundLoader::Inst()->load(WalkOnSnow2File, WalkOnSnow2, SOUND_SFX);
	SoundLoader::Inst()->load(WalkOnSnow3File, WalkOnSnow3, SOUND_SFX);
	SoundLoader::Inst()->load(WalkOnSnow4File, WalkOnSnow4, SOUND_SFX);
}

void World::updating()
{
	int i;
	int len;

	//update sprite
	vector<Object*>& objects = layers[LAYER_SPRITE];
	len = objects.size();
	for (i = 0; i < len; i++)
		objects[i]->update();
	//update tile
	objects = layers[LAYER_TILE];
	len = objects.size();
	for (i = 0; i < len; i++)
		objects[i]->update();
	//update entity
	objects = layers[LAYER_ENTITY];
	len = objects.size();
	for (i = 0; i < len; i++)
		objects[i]->update();
	//update projectile
	objects = layers[LAYER_PROJECTILE];
	len = objects.size();
	for (i = 0; i < len; i++)
		if(objects[i]->active)
			objects[i]->update();
	if (!objects.empty() && !objects[i - 1]->active)
		objects.pop_back();
	//update player
	objects = layers[LAYER_PLAYER];
	len = objects.size();
	for (i = 0; i < len; i++)
		objects[i]->update();
}

void World::rendering()
{
	int len;
	int i;
	
	SDL_RenderClear(Main::Inst()->getRenderer());

	//render background
	renderBackground();
	//render sprite
	vector<Object*>& objects = layers[LAYER_SPRITE];
	len = objects.size();
	for (i = 0; i < len; i++)
		objects[i]->draw();
	//render tile
	objects = layers[LAYER_TILE];
	len = objects.size();
	for (i = 0; i < len; i++)
		objects[i]->draw();
	//render entity
	objects = layers[LAYER_ENTITY];
	len = objects.size();
	for (i = 0; i < len; i++)
		objects[i]->draw();
	//render projectile
	objects = layers[LAYER_PROJECTILE];
	len = objects.size();
	for (i = 0; i < len; i++)
		if(objects[i]->active)
			objects[i]->draw();
	//render player
	objects = layers[LAYER_PLAYER];
	len = objects.size();
	for (i = 0; i < len; i++)
		objects[i]->draw();

	SDL_RenderPresent(Main::Inst()->getRenderer());
}

void World::renderBackground()
{
	if (Camera::Inst()->getPosition().x - Main::Inst()->getWindowWidth() / 2 < 0)
	{
		TextureLoader::Inst()->drawEx(Background, 0, 0, 0, 0, Main::Inst()->getWindowWidth(), Main::Inst()->getWindowHeight());
	}
	else if (Camera::Inst()->getPosition().x + Main::Inst()->getWindowWidth() / 2 - width > 0)
	{
		TextureLoader::Inst()->drawEx(Background, width - Main::Inst()->getWindowWidth(), 0, 0, 0, Main::Inst()->getWindowWidth(), Main::Inst()->getWindowHeight());
	}
	else
	{
		TextureLoader::Inst()->drawEx(Background, Camera::Inst()->getPosition().x - Main::Inst()->getWindowWidth() / 2, 0, 0, 0, Main::Inst()->getWindowWidth(), Main::Inst()->getWindowHeight());
	}
}

void World::newProjectile(Vector2D* pos, string id, float velocity_x, float velocity_y, bool gravitational)
{
	int num = getLayer_projectile().size();
	cout << "aray length:" << num << endl;
	getLayer_projectile().push_back(new Projectile(pos, id, num, velocity_x, velocity_y, gravitational));
}
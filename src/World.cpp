#include "World.h"
#include "Main.h"
#include "IDSheet.h"
#include "SoundLoader.h"
#include "TextureLoader.h"
#include "Camera.h"
#include "NPC.h"
#include "Hostile.h"
#include "Item.h"

#define LAYERCOUNT 7

World* World::INSTANCE = 0;

void World::initialize()
{
	currentMapID = 0;
	///Load backgrounds
	TextureLoader::Inst()->load(BackgroundFile, Background);
	TextureLoader::Inst()->load(Background2File, Background2);
	///Load panels and uis
	TextureLoader::Inst()->load(UIpicFile, UIpic);
	TextureLoader::Inst()->load(HealthBarFile, HealthBar);
	TextureLoader::Inst()->load(ManaBarFile, ManaBar);
	TextureLoader::Inst()->load(InventoryGridFile, InventoryGrid);
	TextureLoader::Inst()->load(InventoryGridMaskFile, InventoryGridMask);
	TextureLoader::Inst()->load(InventoryCloseButtonFile, InventoryCloseButton);
	TextureLoader::Inst()->load(CharacterPanelPicFile, CharacterPanelPic);
	TextureLoader::Inst()->load(ExpBarFile, ExpBar);
	TextureLoader::Inst()->load(DialogBackgroundFile, DialogBackground);
	///Load tiles
	TextureLoader::Inst()->load(Tile01File, Tile01);
	TextureLoader::Inst()->load(BrickFile, Brick);
	///Load sprites
	TextureLoader::Inst()->load(WaterMushroomFrameFile, WaterMushroomFrame);
	TextureLoader::Inst()->load(LadderSpriteFile, LadderSprite);
	TextureLoader::Inst()->load(MapGateFile, MapGate);
	TextureLoader::Inst()->load(MapGate2File, MapGate2);
	///Load entities
	TextureLoader::Inst()->load(PlayerFrameFile, PlayerFrame);
	TextureLoader::Inst()->load(LeafNPCFile, LeafNPC);
	TextureLoader::Inst()->load(GhostNPCFile, GhostNPC);
	TextureLoader::Inst()->load(TestPortalFile, TestPortal);
	TextureLoader::Inst()->load(BlackBlockFile, BlackBlock);
	///Load Projectiles
	TextureLoader::Inst()->load(IchorKnifeProjectileFile, IchorKnifeProjectile);
	TextureLoader::Inst()->load(OrichalcumShortswordProjectileFile, OrichalcumShortswordProjectile);
	///Load Items
	TextureLoader::Inst()->load(WoodenSwordFile, WoodenSword);
	TextureLoader::Inst()->load(OrichalcumShortswordFile, OrichalcumShortsword);
	///Load sounds
	//SoundLoader::Inst()->load(Music01File, Music01, SOUND_MUSIC);
	//SoundLoader::Inst()->playMusic(Music01, 2);
	SoundLoader::Inst()->load(WalkOnSnow1File, WalkOnSnow1, SOUND_SFX);
	SoundLoader::Inst()->load(WalkOnSnow2File, WalkOnSnow2, SOUND_SFX);
	SoundLoader::Inst()->load(WalkOnSnow3File, WalkOnSnow3, SOUND_SFX);
	SoundLoader::Inst()->load(WalkOnSnow4File, WalkOnSnow4, SOUND_SFX);
	SoundLoader::Inst()->load(AttackSoundFile, AttackSound, SOUND_SFX);
	SoundLoader::Inst()->load(CollisionSouldFile, CollisionSound, SOUND_SFX);
	SoundLoader::Inst()->load(DamageSoundFile, DamageSound, SOUND_SFX);
	SoundLoader::Inst()->load(DeathSoundFile, DeathSound, SOUND_SFX);
	SoundLoader::Inst()->load(PortalNoiseFile, PortalNoise, SOUND_SFX);
	SoundLoader::Inst()->load(PickupSoundFile, PickupSound, SOUND_SFX);
	SoundLoader::Inst()->load(LevelupSoundFile, LevelupSound, SOUND_SFX);
	//defaultly load test01
	changeMap(MapTest01);
}

void World::ClearWorld()
{
	layer_background.clear();
	layer_tile.clear();
	layer_foreground.clear();
	layer_entity.clear();
	layer_projectile.clear();
	layer_text.clear();
}

void World::changeMap(int mapID)
{
	if (layer_player.empty())
	{
		Player* player = new Player(0, 0, PlayerFrame);
		getLayer_player().push_back(player);
		Camera::Inst()->Focus(player);
	}

	ClearWorld();
	currentMapID = mapID;
	if (mapID == MapTest01)
	{
		width = 3072;
		height = 1000;
		backgroundID = Background;
		///Spawn point
		Camera::Inst()->getTarget_nonConst()->setPosition(1000, height - 100);
		///tiles
		for (int i = 0; i < 10; i++)
			getLayer_tile().push_back(new Tile(47 * i, height - 37, Brick));
		for (int i = 10; i < 20; i++)
			getLayer_tile().push_back(new Tile(47 * i, height - 244, Brick));
		///sprites
		getLayer_background().push_back(new Sprite(1000, height - 136, WaterMushroomFrame));
		getLayer_foreground().push_back(new Sprite(19 * 47, height - 244, LadderSprite));
		getLayer_foreground().push_back(new Sprite(1600, height - 154, MapGate));
		///entities
		getLayer_entity().push_back(new NPC(2000, height - 100, LeafNPC));
		getLayer_entity().push_back(new NPC(1400, height - 80, GhostNPC));
		getLayer_entity().push_back(new NPC(1200, height - 105, TestPortal));
		getLayer_entity().push_back(new Hostile(2500, height - 200, BlackBlock, 0));
		return;
	}
	if (mapID == MapTest02)
	{
		width = 2048;
		height = 700;
		backgroundID = Background2;
		///Spawn point
		Camera::Inst()->getTarget_nonConst()->setPosition(0, height - 100);
		///sprites
		getLayer_foreground().push_back(new Sprite(100, height - 154, MapGate2));
		///items
		getLayer_entity().push_back(new Item(1200, 0, OrichalcumShortsword, 1));
	}
}

void World::updating()
{
	int k, i;
	int len;

	//update background
	len = layer_background.size();
	for (i = 0; i < len; i++)
		layer_background[i]->update();
	//update tiles
	len = layer_tile.size();
	for (i = 0; i < len; i++)
		layer_tile[i]->update();
	//update foreground
	len = layer_foreground.size();
	for (i = 0; i < len; i++)
		layer_foreground[i]->update();
	//update entities
	len = layer_entity.size();
	for (i = 0; i < len; i++)
		if(!layer_entity[i]->dead)
			layer_entity[i]->update();
	//update projectiles
	len = layer_projectile.size();
	for (i = 0; i < len; i++)
		if(layer_projectile[i]->active)
			layer_projectile[i]->update();
	//update players
	len = layer_player.size();
	for (i = 0; i < len; i++)
		layer_player[i]->update();
	//update texts
	len = layer_text.size();
	for (i = 0; i < len; i++)
		if (layer_text[i]->active)
			layer_text[i]->update();
}

void World::rendering()
{
	int k, i;
	int len;

	//render background
	SDL_SetRenderDrawColor(Main::Inst()->getRenderer(), 255, 255, 255, 255);
	RenderBackground();

	len = layer_background.size();
	for (i = 0; i < len; i++)
		layer_background[i]->draw();
	//render tiles
	len = layer_tile.size();
	for (i = 0; i < len; i++)
		layer_tile[i]->draw();
	//render foreground
	len = layer_foreground.size();
	for (i = 0; i < len; i++)
		layer_foreground[i]->draw();
	//render entities
	len = layer_entity.size();
	for (i = 0; i < len; i++)
		if (!layer_entity[i]->dead)
			layer_entity[i]->draw();
	//render projectiles
	len = layer_projectile.size();
	for (i = 0; i < len; i++)
		if (layer_projectile[i]->active)
			layer_projectile[i]->draw();
	//render players
	len = layer_player.size();
	for (i = 0; i < len; i++)
		layer_player[i]->draw();
	//render projectiles
	len = layer_text.size();
	for (i = 0; i < len; i++)
		if (layer_text[i]->active)
			layer_text[i]->draw();

	//render UI
	RenderUI();
}

void World::RenderBackground()
{
	int x, y;
	//x offset
	if (Camera::Inst()->getPosition().x - Main::Inst()->getRenderWidth() / 2 < 0)
		x = 0;
	else if (Camera::Inst()->getPosition().x + Main::Inst()->getRenderWidth() / 2 - width > 0)
		x = width - Main::Inst()->getRenderWidth();
	else
		x = Camera::Inst()->getPosition().x - Main::Inst()->getRenderWidth() / 2;
	//y offset
	if (Camera::Inst()->getPosition().y - Main::Inst()->getRenderHeight() / 2 < 0)
		y = 0;
	else if (Camera::Inst()->getPosition().y + Main::Inst()->getRenderHeight() / 2 - height > 0)
		y = Main::Inst()->getRenderHeight() - height;
	else
		y = Camera::Inst()->getPosition().y - Main::Inst()->getRenderHeight() / 2;
	
 	TextureLoader::Inst()->drawEx(backgroundID, x, y, 0, 0, Main::Inst()->getRenderWidth(), Main::Inst()->getRenderHeight());
}
 
void World::RenderUI()
{
	TextureLoader::Inst()->draw(UIpic, 0, Main::Inst()->getRenderHeight(), Main::Inst()->getRenderWidth(), UIHEIGHT);

	const Player* player = Camera::Inst()->getTarget();
	TextureLoader::Inst()->draw(HealthBar, 105, Main::Inst()->getRenderHeight() + 67, player->life * 292.0f / player->maxlife, 26);
	TextureLoader::Inst()->draw(ManaBar, 105, Main::Inst()->getRenderHeight() + 117, player->mana * 292.0f / player->maxmana, 26);
	
	Vector2D nameTextpos(20, Main::Inst()->getRenderHeight() + 10);
	Vector2D healthNumTextpos(406, Main::Inst()->getRenderHeight() + 65);
	Vector2D manaNumTextpos(406, Main::Inst()->getRenderHeight() + 117);
	nameText = new Textbox(nameTextpos, player->name, arial28, { 255,255,255 }, -1);
	nameText->draw();
	delete nameText;
	healthNumText = new Textbox(healthNumTextpos, to_string(player->life) + " / " + to_string(player->maxlife), arial28, { 255,255,255 }, -1);
	healthNumText->draw();
	delete healthNumText;
	manaNumText = new Textbox(manaNumTextpos, to_string(player->mana) + " / " + to_string(player->maxmana), arial28, { 255,255,255 }, -1);
	manaNumText->draw();
	delete manaNumText;
}

void World::newProjectile(Vector2D pos, string id, float velocity_x, float velocity_y, Entity* owner, bool gravitational)
{
	vector<Projectile*>& projectiles = getLayer_projectile();
	int len = projectiles.size();
	int i;
	for (i = 0; i < len; i++)
	{
		if (!projectiles[i]->active)
		{
			delete projectiles[i];
			projectiles[i] = new Projectile(pos, id, i, velocity_x, velocity_y, owner, gravitational);
			return;
		}
	}

	projectiles.push_back(new Projectile(pos, id, len, velocity_x, velocity_y, owner, gravitational));
}

void World::createText(int lastingTime, Vector2D pos, float velocity_x, float velocity_y, string text, string fontID, SDL_Color color)
{
	vector<Textbox*>& texts = getLayer_text();
	int len = texts.size();
	int i;
	for (i = 0; i < len; i++)
	{
		if (!texts[i]->active)
		{
			delete texts[i];
			texts[i] = new Textbox(pos, velocity_x, velocity_y, text, fontID, color, lastingTime);
			return;
		}
	}

	texts.push_back(new Textbox(pos, velocity_x, velocity_y, text, fontID, color, lastingTime));
}

void World::newHostile(int x, int y, string id)
{
	vector<Entity*>& entites = getLayer_entity();
	int len = entites.size();
	int i;
	for (i = 0; i < len; i++)
	{
		if (entites[i]->dead)
		{
			delete entites[i];
			entites[i] = new Hostile(x, y, id, i);
			return;
		}
	}

	entites.push_back(new Hostile(x, y, id, i));
}

void World::newItem(int x, int y, string id, int stack)
{
	vector<Entity*>& entites = getLayer_entity();
	int len = entites.size();
	int i;
	for (i = 0; i < len; i++)
	{
		if (entites[i]->dead)
		{
			delete entites[i];
			entites[i] = new Item(x, y, id, stack);
			return;
		}
	}

	entites.push_back(new Item(x, y, id, stack));
}

void World::newItem(int x, int y, float velocity_x, float velocity_y, string id, int stack)
{
	vector<Entity*>& entites = getLayer_entity();
	int len = entites.size();
	int i;
	for (i = 0; i < len; i++)
	{
		if (entites[i]->dead)
		{
			delete entites[i];
			entites[i] = new Item(x, y, velocity_x, velocity_y, id, stack);
			return;
		}
	}

	entites.push_back(new Item(x, y, velocity_x, velocity_y, id, stack));
}
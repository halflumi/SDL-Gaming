#include "World.h"
#include "Main.h"
#include "IDSheet.h"
#include "SoundLoader.h"
#include "TextureLoader.h"
#include "Camera.h"
#include "NPC.h"
#include "Hostile.h"
#include "Item.h"
#include "XmlParser.h"
#include "Effect.h"

#define LAYERCOUNT 7
#define HealthTextPos		191, Main::Inst()->getRenderHeight() + 1
#define ManaTextPos			191, Main::Inst()->getRenderHeight() + 22
#define xpTextPos			941, Main::Inst()->getRenderHeight() + 42 
#define HealthBarPos		39, Main::Inst()->getRenderHeight() + 9
#define ManaBarPos			39, Main::Inst()->getRenderHeight() + 30
#define XPBarPos			39, Main::Inst()->getRenderHeight() + 50
#define HealthBarLength		148
#define HealthBarHeight		9
#define xpBarLength			898

World* World::INSTANCE = 0;

World::World() : healthBar(HealthProgressBar, HealthBarLength, HealthBarHeight), manaBar(ManaProgressBar, HealthBarLength, HealthBarHeight), xpBar(XPProgressBar, HealthBarLength, HealthBarHeight)
{
	newGame = false;
}

void World::initialize()
{
	currentMapID = 0;
	///Load menu elements
	TextureLoader::Inst()->load(GameMenuBackgroundFile, GameMenuBackground);
	///Load backgrounds
	TextureLoader::Inst()->load(MapBackgroundFile, MapBackground);
	TextureLoader::Inst()->load(MapBackground2File, MapBackground2);
	///Load panels and uis
	TextureLoader::Inst()->load(UIpicFile, UIpic);
	TextureLoader::Inst()->load(InventoryGridFile, InventoryGrid);
	TextureLoader::Inst()->load(InventoryGridMaskFile, InventoryGridMask);
	TextureLoader::Inst()->load(InventoryCloseButtonFile, InventoryCloseButton);
	TextureLoader::Inst()->load(CharacterPanelPicFile, CharacterPanelPic);
	TextureLoader::Inst()->load(SkillPanelPicFile, SkillPanelPic);
	TextureLoader::Inst()->load(DialogBackgroundFile, DialogBackground);
	TextureLoader::Inst()->load(MessageboxMaskFile, MessageboxMask);
	TextureLoader::Inst()->load(InventoryArrangeButtonFile, InventoryArrangeButton);
	TextureLoader::Inst()->load(SkillPanelAddSkillButtonFile, SkillPanelAddSkillButton);
	TextureLoader::Inst()->load(SkillPanelMinusSkillButtonFile, SkillPanelMinusSkillButton);
	TextureLoader::Inst()->load(CharacterWeaponSlotFile, CharacterWeaponSlot);
	TextureLoader::Inst()->load(ItemInfoBackgroundFile, ItemInfoBackground);

	TextureLoader::Inst()->load(XPProgressBarFile, XPProgressBar);
	TextureLoader::Inst()->load(HealthProgressBarFile, HealthProgressBar);
	TextureLoader::Inst()->load(ManaProgressBarFile, ManaProgressBar);
	TextureLoader::Inst()->load(CharacterXPBarFile, CharacterXPBar);
	///Load skill icons
	TextureLoader::Inst()->load(SkillPhysicalTrainingIconFile, SkillPhysicalTrainingIcon);
	TextureLoader::Inst()->load(SkillDoubleThrowIconFile, SkillDoubleThrowIcon);
	TextureLoader::Inst()->load(SkillTripleThrowIconFile, SkillTripleThrowIcon);
	TextureLoader::Inst()->load(SkillLifeForceIconFile, SkillLifeForceIcon);
	TextureLoader::Inst()->load(SkillIronBodyIconFile, SkillIronBodyIcon);
	TextureLoader::Inst()->load(SkillLifeRegenerationIconFile, SkillLifeRegenerationIcon);
	TextureLoader::Inst()->load(SkillMPBoostIconFile, SkillMPBoostIcon);
	TextureLoader::Inst()->load(SkillCriticalThrowIconFile, SkillCriticalThrowIcon);
	TextureLoader::Inst()->load(SkillSummonAttackIconFile, SkillSummonAttackIcon);
	TextureLoader::Inst()->load(SkillSpeedupIconFile, SkillSpeedupIcon);
	///Load tiles
	TextureLoader::Inst()->load(BrickFile, Brick);
	TextureLoader::Inst()->load(Tile01File, Tile01);
	TextureLoader::Inst()->load(Tile02File, Tile02);
	TextureLoader::Inst()->load(Tile03File, Tile03);
	TextureLoader::Inst()->load(Tile04File, Tile04);
	TextureLoader::Inst()->load(Tile05File, Tile05);
	TextureLoader::Inst()->load(Tile06File, Tile06);
	TextureLoader::Inst()->load(Tile07File, Tile07);
	TextureLoader::Inst()->load(Tile08File, Tile08);
	TextureLoader::Inst()->load(Tile09File, Tile09);
	///Load sprites
	TextureLoader::Inst()->load(WaterMushroomFrameFile, WaterMushroomFrame);
	TextureLoader::Inst()->load(TestPortalFile, TestPortal);
	TextureLoader::Inst()->load(LadderSpriteFile, LadderSprite);
	TextureLoader::Inst()->load(MapGateFile, MapGate);
	TextureLoader::Inst()->load(MapGate2File, MapGate2);
	TextureLoader::Inst()->load(Sprite01File, Sprite01);
	TextureLoader::Inst()->load(Sprite02File, Sprite02);
	TextureLoader::Inst()->load(Sprite03File, Sprite03);
	TextureLoader::Inst()->load(Sprite04File, Sprite04);
	TextureLoader::Inst()->load(Sprite05File, Sprite05);
	TextureLoader::Inst()->load(Sprite06File, Sprite06);
	TextureLoader::Inst()->load(Sprite07File, Sprite07);
	TextureLoader::Inst()->load(Sprite08File, Sprite08);
	TextureLoader::Inst()->load(Sprite09File, Sprite09);
	TextureLoader::Inst()->load(Sprite10File, Sprite10);
	///Load entities
	TextureLoader::Inst()->load(PlayerFrameFile, PlayerFrame);
	TextureLoader::Inst()->load(LeafNPCFile, LeafNPC);
	TextureLoader::Inst()->load(GhostNPCFile, GhostNPC);
	TextureLoader::Inst()->load(MapleFlagNPCFile, MapleFlagNPC);
	TextureLoader::Inst()->load(SavePointNPCFile, SavePointNPC);
	TextureLoader::Inst()->load(ShopNPCFile, ShopNPC);
	TextureLoader::Inst()->load(BlackBlockFile, BlackBlock);
	TextureLoader::Inst()->load(DemonHostileFile, DemonHostile);
	TextureLoader::Inst()->load(HostileGhostMobFile, HostileGhostMob);
	TextureLoader::Inst()->load(HostileSkeletonFile, HostileSkeleton);
	TextureLoader::Inst()->load(HostileGhostMobFile, HostileGhostMob);
	TextureLoader::Inst()->load(HostileWoodMobFile, HostileWoodMob);
	TextureLoader::Inst()->load(HostileGiantCatFile, HostileGiantCat);
	TextureLoader::Inst()->load(HostilePigNPCFile, HostilePigNPC);
	///Load projectiles
	TextureLoader::Inst()->load(SubiDartProjectileFile, SubiDartProjectile);
	TextureLoader::Inst()->load(IronDartProjectileFile, IronDartProjectile);
	TextureLoader::Inst()->load(CrystalDartProjectileFile, CrystalDartProjectile);
	TextureLoader::Inst()->load(MokbiDartProjectileFile, MokbiDartProjectile);
	TextureLoader::Inst()->load(SteelyThrowingKnivesProjectileFile, SteelyThrowingKnivesProjectile);
	///Load items
	TextureLoader::Inst()->load(IronDartItemFile, IronDartItem);
	TextureLoader::Inst()->load(CrystalDartItemFile, CrystalDartItem);
	TextureLoader::Inst()->load(MokbiDartItemFile, MokbiDartItem);
	TextureLoader::Inst()->load(GoldCoinItemFile, GoldCoinItem);
	TextureLoader::Inst()->load(SteelyThrowingKnivesItemFile, SteelyThrowingKnivesItem);
	TextureLoader::Inst()->load(HealthPotionItemFile, HealthPotionItem);
	///Load effects
	TextureLoader::Inst()->load(SummonMagicEffectFile, SummonMagicEffect);
	TextureLoader::Inst()->load(SpeedupSkillEffectFile, SpeedupSkillEffect);
	///Load buffs
	TextureLoader::Inst()->load(SpeedupBuffFile, SpeedupBuff);
	///Load sounds
	SoundLoader::Inst()->load(WalkOnSnow1File, WalkOnSnow1, SOUND_SFX);
	SoundLoader::Inst()->load(WalkOnSnow2File, WalkOnSnow2, SOUND_SFX);
	SoundLoader::Inst()->load(WalkOnSnow3File, WalkOnSnow3, SOUND_SFX);
	SoundLoader::Inst()->load(WalkOnSnow4File, WalkOnSnow4, SOUND_SFX);
	SoundLoader::Inst()->load(AttackSoundFile, AttackSound, SOUND_SFX);
	SoundLoader::Inst()->load(CollisionSouldFile, CollisionSound, SOUND_SFX);
	SoundLoader::Inst()->load(PortalNoiseFile, PortalNoise, SOUND_SFX);
	SoundLoader::Inst()->load(PickupSoundFile, PickupSound, SOUND_SFX);
	SoundLoader::Inst()->load(LevelupSoundFile, LevelupSound, SOUND_SFX);
	SoundLoader::Inst()->load(JumpSoundFile, JumpSound, SOUND_SFX);
	SoundLoader::Inst()->load(PlayerDamageSoundFile, PlayerDamageSound, SOUND_SFX);
	SoundLoader::Inst()->load(WrapGateNoiseFile, WrapGateNoise, SOUND_SFX);
	SoundLoader::Inst()->load(HealingMagicSoundFile, HealingMagicSound, SOUND_SFX);
	SoundLoader::Inst()->load(SummonMagicUseSoundFile, SummonMagicUseSound, SOUND_SFX);
	SoundLoader::Inst()->load(SummonMagicHitSoundFile, SummonMagicHitSound, SOUND_SFX);
	SoundLoader::Inst()->load(SpeedupSkillSoundFile, SpeedupSkillSound, SOUND_SFX);

	SoundLoader::Inst()->load(DamageSoundFile, DamageSound, SOUND_SFX);
	SoundLoader::Inst()->load(DeathSoundFile, DeathSound, SOUND_SFX);
	SoundLoader::Inst()->load(DemonDamageSoundFile, DemonDamageSound, SOUND_SFX);
	SoundLoader::Inst()->load(DemonDieSoundFile, DemonDieSound, SOUND_SFX);
	SoundLoader::Inst()->load(GhostMobDamageSoundFile, GhostMobDamageSound, SOUND_SFX);
	SoundLoader::Inst()->load(GhostMobDieSoundFile, GhostMobDieSound, SOUND_SFX);
	SoundLoader::Inst()->load(GiantCatDamageSoundFile, GiantCatDamageSound, SOUND_SFX);
	SoundLoader::Inst()->load(GiantCatDieSoundFile, GiantCatDieSound, SOUND_SFX);
	SoundLoader::Inst()->load(SkeletonDamageSoundFile, SkeletonDamageSound, SOUND_SFX);
	SoundLoader::Inst()->load(SkeletonDieSoundFile, SkeletonDieSound, SOUND_SFX);
	SoundLoader::Inst()->load(WoodMobDamageSoundFile, WoodMobDamageSound, SOUND_SFX);
	SoundLoader::Inst()->load(WoodMobDieSoundFile, WoodMobDieSound, SOUND_SFX);
	SoundLoader::Inst()->load(PigDamageSoundFile, PigDamageSound, SOUND_SFX);
	SoundLoader::Inst()->load(PigDieSoundFile, PigDieSound, SOUND_SFX);
	///Load player data from xml
	if (!newGame)
		XmlParser::Inst()->loadCharacter();
	changeMap(XmlParser::Inst()->mapID, MAPCHANGE_LOAD);
	timer = MyTimer(true);
	///load UI
	Vector2D healthNumTextpos(HealthTextPos);
	Vector2D manaNumTextpos(ManaTextPos);
	Vector2D xpTextpos(xpTextPos);
	healthNumText = Textbox(healthNumTextpos, "", segoeui18, COLOR_WHITE, -1);
	manaNumText = Textbox(manaNumTextpos, "", segoeui18, COLOR_WHITE, -1);
	xpNumText = Textbox(xpTextpos, "", segoeui18, COLOR_WHITE, -1);
	healthBar.setPosition(HealthBarPos);
	manaBar.setPosition(ManaBarPos);
	xpBar.setPosition(XPBarPos);
}

void World::clearWorld()
{
	layer_background.clear();
	layer_tile.clear();
	layer_foreground.clear();
	layer_entity.clear();
	layer_projectile.clear();
	layer_text.clear();
}

void World::startNewGame(bool demonic)
{
	newGame = true;
	if(demonic)
		XmlParser::Inst()->mapID = MapDemo;
	else
		XmlParser::Inst()->mapID = MapTest01;
	XmlParser::Inst()->level = 1;
	XmlParser::Inst()->xp = 0;
	XmlParser::Inst()->life = 100;
	XmlParser::Inst()->mana = 30;
}

void World::changeMap(int mapID, MapChangeType form)
{
	if (layer_player.empty())
	{
		Player* player = new Player(PlayerFrame, 0, 0);
		getLayer_player().push_back(player);
		Camera::Inst()->focus(player);
	}

	clearWorld();
	
	if (mapID == MapTest01)
	{
		width = 3072;
		height = 1000;
		backgroundID = MapBackground;
		///Spawn point
		switch (form)
		{
		case MAPCHANGE_LOAD:
			Camera::Inst()->getTarget_nonConst()->setPosition(1000, height - 100);
			break;
		case MAPCHANGE_LEFT:
			Camera::Inst()->getTarget_nonConst()->setPosition(0, height - 100);
			break;
		}
		///tiles
		for (int i = 10; i < 20; i++)
			getLayer_tile().push_back(new Tile(Brick, 47 * i, height - 244));
		///sprites
		getLayer_background().push_back(new Sprite(WaterMushroomFrame, 1000, height - 136));
		getLayer_foreground().push_back(new Sprite(TestPortal, 1200, height - 105));
		getLayer_foreground().push_back(new Sprite(LadderSprite, 19 * 47, height - 244));
		getLayer_foreground().push_back(new Sprite(MapGate, 0, height - 154));
		///entities
		getLayer_entity().push_back(new NPC(LeafNPC, 2000, height - 100));
		getLayer_entity().push_back(new NPC(ShopNPC, 1600, height - 215));
		getLayer_entity().push_back(new NPC(GhostNPC, 1400, height - 80));
		getLayer_entity().push_back(new NPC(MapleFlagNPC, 800, height - 177));
		getLayer_entity().push_back(new Hostile(BlackBlock, 0, 2500, height - 200));
		getLayer_entity().push_back(new Hostile(HostileGiantCat, 0, 2700, height - 200));	
		getLayer_entity( ).push_back(new Hostile(HostileSkeleton, 0, 2700, height - 200));
		getLayer_entity( ).push_back(new Hostile(HostileSkeleton, 0, 2700, height - 200));
		getLayer_entity( ).push_back(new Hostile(HostileSkeleton, 0, 2700, height - 200));
		getLayer_entity( ).push_back(new Hostile(HostileWoodMob, 0, 2700, height - 200));
		getLayer_entity( ).push_back(new Hostile(HostileWoodMob, 0, 2700, height - 200));
		getLayer_entity( ).push_back(new Hostile(HostileWoodMob, 0, 2700, height - 200));
		getLayer_entity( ).push_back(new Hostile(HostileWoodMob, 0, 2700, height - 200));
		getLayer_entity( ).push_back(new Hostile(HostileWoodMob, 0, 2700, height - 200));
		///items
		return;
	}
	if (mapID == MapTest02)
	{
		currentMapID = mapID; ///contain savepoint
		width = 2048;
		height = 700;
		backgroundID = MapBackground2;
		///Spawn point
		switch (form)
		{
		case MAPCHANGE_LOAD:
			Camera::Inst()->getTarget_nonConst()->setPosition(1600, height - 100);
			break;
		case MAPCHANGE_RIGHT:
			Camera::Inst()->getTarget_nonConst()->setPosition(width - 50, height - 100);
			break;
		}
		///sprites
		getLayer_foreground().push_back(new Sprite(MapGate2, width - 108, height - 154));
		///entities
		getLayer_entity().push_back(new NPC(SavePointNPC, 1600, height - 211));
		///items
		return;
	}
	if (mapID == MapDemo)
	{
		int i;
		width = 3072;
		height = 1000;
		backgroundID = MapBackground;
		///Spawn point
		switch (form)
		{
		case MAPCHANGE_LOAD:
			Camera::Inst()->getTarget_nonConst()->setPosition(500, height - 200);
			break;
		}
		///tiles
		for (i = 0; i < 12; i++)
		{
			getLayer_tile().push_back(new Tile(Tile01, i * 270, height - 60));
			getLayer_tile().push_back(new Tile(Tile02, i * 270 + 90, height - 60));
			getLayer_tile().push_back(new Tile(Tile03, i * 270 + 180, height - 60));
		}
		for (i = 0; i < 10; i++)
		{
			getLayer_tile().push_back(new Tile(Tile04, i * 270, height - 88));
			getLayer_tile().push_back(new Tile(Tile05, i * 270 + 90, height - 88));
			getLayer_tile().push_back(new Tile(Tile06, i * 270 + 180, height - 88));
		}
		getLayer_tile().push_back(new Tile(Tile07, 10 * 270 - 26, height - 148));
		for (; i < 12; i++)
		{
			getLayer_tile().push_back(new Tile(Tile01, i * 270, height - 120));
			getLayer_tile().push_back(new Tile(Tile02, i * 270 + 90, height - 120));
			getLayer_tile().push_back(new Tile(Tile03, i * 270 + 180, height - 120));
			getLayer_tile().push_back(new Tile(Tile04, i * 270, height - 148));
			getLayer_tile().push_back(new Tile(Tile05, i * 270 + 90, height - 148));
			getLayer_tile().push_back(new Tile(Tile06, i * 270 + 180, height - 148));
		}
		getLayer_tile().push_back(new Tile(Tile09, 10 * 270 - 26, height - 121));
		///sprites
		getLayer_background().push_back(new Sprite(Sprite03, 0, height - 170));
		getLayer_background().push_back(new Sprite(Sprite02, 201, height - 170));
		getLayer_background().push_back(new Sprite(Sprite04, 455, height - 170));
		getLayer_background().push_back(new Sprite(Sprite01, 0, height - 365));
		getLayer_background().push_back(new Sprite(Sprite07, 300, height - 280));
		getLayer_background().push_back(new Sprite(Sprite05, 400, height - 140));
		getLayer_background().push_back(new Sprite(Sprite06, 456, height - 721));
		getLayer_background().push_back(new Sprite(Sprite08, 756, height - 123));
		getLayer_background().push_back(new Sprite(Sprite10, 786, height - 123));
		getLayer_background().push_back(new Sprite(Sprite09, 806, height - 123));
		getLayer_background().push_back(new Sprite(Sprite10, 856, height - 123));
		getLayer_background().push_back(new Sprite(Sprite08, 886, height - 123));
		getLayer_foreground().push_back(new Sprite(LadderSprite, 553, 704));
		///entities
		getLayer_entity().push_back(new Hostile(HostilePigNPC, 0, 200, height - 200));
		///items
		getLayer_entity().push_back(new Item(IronDartItem, 1, 500, 0));
		getLayer_entity().push_back(new Item(MokbiDartItem, 1, 500, 0));
		getLayer_entity().push_back(new Item(CrystalDartItem, 1, 500, 0));
		getLayer_entity().push_back(new Item(SteelyThrowingKnivesItem, 1, 500, 0));
		getLayer_entity().push_back(new Item(HealthPotionItem, 10, 500, 0));
		return;
	}
}

void World::AttackWave()
{
	int time = timer.getTicks();
	switch (time)
	{
	case 30:
	case 330:
	case 630:
	case 930:
	case 1230:
	case 1530:
	case 1830:
	case 2130:
		newHostile(HostileWoodMob, width - 10, 0);
		break;
	case 2730:
	case 3030:
		newHostile(HostileSkeleton, width - 10, 0);
		break;
	case 3630:
	case 3700:
		newHostile(HostileGiantCat, width - 10, 0);
		break;
	case 4000:
	case 4300:
		newHostile(HostileGhostMob, width - 10, 0);
		break;
	case 4900:
		newHostile(DemonHostile, width - 10, 0);
	}
}

void World::updating()
{
	int k, i;
	int len;

	//update camera to focused player
	Camera::Inst()->upadte();
	//demo attack wave
	AttackWave();

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
	//update effects
	len = layer_effect.size();
	for (i = 0; i < len; i++)
		if (layer_effect[i]->active)
			layer_effect[i]->update();
	//update texts
	len = layer_text.size();
	for (i = 0; i < len; i++)
		if (layer_text[i]->active)
			layer_text[i]->update();

	//update UI
	UpdateUI();
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
	//render effects
	len = layer_effect.size();
	for (i = 0; i < len; i++)
		if (layer_effect[i]->active)
			layer_effect[i]->draw();
	//render texts
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
 
void World::UpdateUI()
{
	const Player* player = Camera::Inst()->getTarget();

	healthBar.updateTarget(player->life, player->maxlife);
	manaBar.updateTarget(player->mana, player->maxmana);
	xpBar.updateTarget(player->exp, player->expToNextLevel);

	healthNumText.changeText(to_string(player->life) + " / " + to_string(player->maxlife));
	manaNumText.changeText(to_string(player->mana) + " / " + to_string(player->maxmana));
	xpNumText.changeText(to_string(player->exp) + " / " + to_string(player->expToNextLevel));
}

void World::RenderUI()
{
	TextureLoader::Inst()->draw(UIpic, 0, Main::Inst()->getRenderHeight(), Main::Inst()->getRenderWidth(), UIHEIGHT);
	healthBar.draw();
	manaBar.draw();
	xpBar.draw();

	healthNumText.draw();
	manaNumText.draw();
	xpNumText.draw();
}

void World::newProjectile(int id, Vector2D pos, float velocity_x, float velocity_y, int minATT, int maxATT, int critChance, bool friendly, bool gravitational)
{
	vector<Projectile*>& projectiles = getLayer_projectile();
	int len = projectiles.size();
	int i;
	for (i = 0; i < len; i++)
	{
		if (!projectiles[i]->active)
		{
			delete projectiles[i];
			projectiles[i] = new Projectile(id, i, pos, velocity_x, velocity_y, minATT, maxATT, critChance, friendly, gravitational);
			return;
		}
	}

	projectiles.push_back(new Projectile(id, len, pos, velocity_x, velocity_y, minATT, maxATT, critChance, friendly, gravitational));
}

void World::createText(Vector2D pos, float velocity_x, float velocity_y, string text, int fontID, SDL_Color color, int lastingTime)
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

void World::newHostile(int id, int x, int y)
{
	vector<Entity*>& entites = getLayer_entity();
	int len = entites.size();
	int i;
	for (i = 0; i < len; i++)
	{
		if (entites[i]->dead)
		{
			delete entites[i];
			entites[i] = new Hostile(id, i, x, y);
			return;
		}
	}

	entites.push_back(new Hostile(id, i, x, y));
}

void World::newItem(int id, int stack, int x, int y)
{
	vector<Entity*>& entites = getLayer_entity();
	int len = entites.size();
	int i;
	for (i = 0; i < len; i++)
	{
		if (entites[i]->dead)
		{
			delete entites[i];
			entites[i] = new Item(id, stack, x, y);
			return;
		}
	}

	entites.push_back(new Item(id, stack, x, y));
}

void World::newItem(int id, int stack, int x, int y, float velocity_x, float velocity_y)
{
	vector<Entity*>& entites = getLayer_entity();
	int len = entites.size();
	int i;
	for (i = 0; i < len; i++)
	{
		if (entites[i]->dead)
		{
			delete entites[i];
			entites[i] = new Item(id, stack, x, y, velocity_x, velocity_y);
			return;
		}
	}

	entites.push_back(new Item(id, stack, x, y, velocity_x, velocity_y));
}

void World::newEffect(int id, int x, int y, int row)
{
	vector<Object*>& effects = getLayer_effect();
	int len = effects.size();
	int i;
	for (i = 0; i < len; i++)
	{
		if (effects[i]->active)
		{
			delete effects[i];
			effects[i] = new Effect(id, x, y, row);
			return;
		}
	}

	effects.push_back(new Effect(id, x, y, row));
}

void World::newSkillEffect(int id, int x, int y, int row, int minATT, int maxATT, int critChance)
{
	vector<Object*>& effects = getLayer_effect();
	int len = effects.size();
	int i;
	for (i = 0; i < len; i++)
	{
		if (effects[i]->active)
		{
			delete effects[i];
			effects[i] = new Effect(id, x, y, row, minATT, maxATT, critChance);
			return;
		}
	}

	effects.push_back(new Effect(id, x, y, row, minATT, maxATT, critChance));
}

void World::newTile(int id, int x, int y)
{
	layer_tile.push_back(new Tile(id, x, y));
}
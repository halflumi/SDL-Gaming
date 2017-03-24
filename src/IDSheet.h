#pragma once
#include <SDL.h>
#include <string>

///Transfers
std::string ScancodeToString(SDL_Scancode scannode);
int ExpSheet(int level);
///const
//global
#define TOTALSKILLS 8
#define MAXLEVEL 10
#define INVENTORYSIZE 36
#define CLICKCOOLDOWN 80
#define PRESSCOOLDOWN 100
#define UIHEIGHT 66
//colors
#define COLOR_BLACK		{0,0,0}
#define COLOR_GREY		{192,192,192}
#define COLOR_WHITE		{255,255,255}
#define COLOR_RED		{255,0,0}
#define COLOR_GREEN		{0,255,0}
#define COLOR_BLUE		{0,0,255}
#define COLOR_CLAN		{0,255,255}
#define COLOR_PURPLE	{255,0,255}
#define COLOR_YELLOW	{255,241,0}
#define COLOR_ORANGE	{241,145,73}
//savedata filepath
#define SettingsFile "../save/settings.xm"
#define SavedataFile "../save/savedata.xm"

enum SkillIndex
{
	SkillIndexPhysicalTraining,
	SkillIndexDoubleThrow,
	SkillIndexTripleThrow,
	SkillIndexLifeForce,
	SkillIndexIronBody,
	SkillIndexLifeRegeneration,
	SkillIndexMPBoost,
	SkillIndexCriticalThrow
};

enum MapChangeType
{
	MAPCHANGE_LOAD,
	MAPCHANGE_LEFT,
	MAPCHANGE_RIGHT
};
///typeID 100xxxxx
//Object type
#define TypeButton							10010000
#define TypeInventory						10010001
#define TypeInventoryItem					10010002
#define TypeCharacterPanel					10010003
#define TypeDialog							10010004
#define TypeTextbox							10010005
#define TypeNPC								10010006
#define TypeHostile							10010007
#define TypeTile							10010008
#define TypePlayer							10010009
#define TypeProjectile						10010010
#define TypeSprite							10010011
#define TypeItem							10010012
#define TypeSkillPanel						10010013
#define TypeSkillSlot						10010014
#define TypeBuff							10010015
//menuID 101
#define MenuMain							10110000
#define MenuOptions							10110001
#define MenuGameMain						10110002
#define MenuControlSettings					10110003
#define MenuGameOver						10110004
//mapID 102
#define MapTest01							10210001
#define MapTest02							10210002
#define MapDemo								10210003
//menu elementsID 103
#define DemoButton							10300001
#define NewGameButton						10310000
#define ExitButton							10310001
#define OptionButton						10310002
#define ResolutionText						10310003
#define ResolutionListbox					10310004
#define FullscreenText						10310005
#define FullscreenCheckbox					10310006
#define FullscreenCheckboxFile				"../assets/UI/FullscreenCheckbox.png"
#define VolumnLButton						10310007
#define VolumnLButtonFile					"../assets/UI/VolumnLButton.png"
#define VolumnRButton						10310008
#define VolumnRButtonFile					"../assets/UI/VolumnRButton.png"
#define VolumnMasterText					10310009
#define VolumnMasterNumber					10310010
#define VolumnMusicText						10310011
#define VolumnMusicNumber					10310012
#define VolumnSfxText						10310013
#define VolumnSfxNumber						10310014
#define BackButton							10310015
#define ContinueButton						10310016
#define ControlSettingsButton				10310017
#define MainMenuBackgroundView				10310018
#define MainMenuBackgroundViewFile			"../assets/UI/MainMenuBackgroundView.png"
#define OptionsMenuView						10310019
#define OptionsMenuViewFile					"../assets/UI/OptionsMenuView.png"

#define ControlMovingUpText					10310200
#define ControlMovingUpButton				10310201
#define ControlMovingDownText				10310202
#define ControlMovingDownButton				10310203
#define ControlMovingLeftText				10310204
#define ControlMovingLeftButton				10310205
#define ControlMovingRightText				10310206
#define ControlMovingRightButton			10310207
#define ControlCharacterPanelText			10310208
#define ControlCharacterPanelButton			10310209
#define ControlSkillPanelText				10310210
#define ControlSkillPanelButton				10310211
#define ControlInventoryText				10310212
#define ControlInventoryButton				10310213
#define ControlSkillHotkey1Text				10310214
#define ControlSkillHotkey1Button			10310215
#define ControlSkillHotkey2Text				10310216
#define ControlSkillHotkey2Button			10310217
#define ControlSkillHotkey3Text				10310218
#define ControlSkillHotkey3Button			10310219

#define GameMenuBackground					10310100
#define GameMenuBackgroundFile				"../assets/UI/GameMenuBackground.png"
#define ResumeButton						10310101
#define ExittoMainMenuButton				10310102
#define ExittoDesktopButton					10310103
#define GameOverText						10310104
//button typeID 104
#define ButtonTypeTextbox					10410000
#define ButtonTypeButton					10410001
#define ButtonTypeBackground				10410002
//ItemClass 105
#define ItemClassWeapon						10510000
//skillID 106
#define SkillPhysicalTraining				10610000
#define SkillPhysicalTrainingIcon			10610001
#define SkillPhysicalTrainingIconFile		"../assets/skills/SkillPhysicalTrainingIcon.png"
#define SkillDoubleThrow					10610002
#define SkillDoubleThrowIcon				10610003
#define SkillDoubleThrowIconFile			"../assets/skills/SkillDoubleThrowIcon.png"
#define SkillLifeForce						10610004
#define SkillLifeForceIcon					10610005
#define SkillLifeForceIconFile				"../assets/skills/SkillLifeForceIcon.png"
#define SkillIronBody						10610006
#define SkillIronBodyIcon					10610007
#define SkillIronBodyIconFile				"../assets/skills/SkillIronBodyIcon.png"
#define SkillLifeRegeneration				10610008
#define SkillLifeRegenerationIcon			10610009
#define SkillLifeRegenerationIconFile		"../assets/skills/SkillLifeRegenerationIcon.png"
#define SkillMPBoost						10610010
#define SkillMPBoostIcon					10610011
#define SkillMPBoostIconFile				"../assets/skills/SkillMPBoostIcon.png"
#define SkillTripleThrow					10610012
#define SkillTripleThrowIcon				10610013
#define SkillTripleThrowIconFile			"../assets/skills/SkillTripleThrowIcon.png"
#define SkillCriticalThrow					10610014
#define SkillCriticalThrowIcon				10610015
#define SkillCriticalThrowIconFile			"../assets/skills/SkillCriticalThrowIcon.png"
//skilClass 107
#define SkillClassHealingMagic				10710000
#define SkillClassAttackingMagic			10710001

///fonts 200xxxxx
#define segoeuiFile							"../fonts/segoeui.ttf"
#define segoeui18							20010000
#define segoeui22							20010001
#define segoeui28							20010002
#define arialFile							"../fonts/arial.ttf"
#define arial28_bold						20010010
#define arial48_bold						20010011
#define arial72_bold						20010012
///texture res 300xxxxx
//menu res
#define MainMenuPic							30010000
#define MainMenuPicFile						"../assets/UI/MainMenuBackground.png"
//background 301
#define MapBackground						30110000
#define MapBackgroundFile					"../assets/Background.png"
#define MapBackground2						30110001
#define MapBackground2File					"../assets/background2.png"
//panel and UIs 302
#define UIpic								30210000
#define UIpicFile							"../assets/UI/UIpic.png"
#define HealthBar							30210001
#define HealthBarFile						"../assets/UI/HealthBar.png"
#define ManaBar								30210002
#define ManaBarFile							"../assets/UI/ManaBar.png"
#define InventoryGrid						30210003
#define InventoryGridFile					"../assets/UI/InventoryGrid.png"
#define InventoryGridMask					30210004
#define InventoryGridMaskFile				"../assets/UI/InventoryGridMask.png"
#define InventoryCloseButton				30210005
#define InventoryCloseButtonFile			"../assets/UI/InventoryCloseButton.png"
#define CharacterPanelPic					30210006
#define CharacterPanelPicFile				"../assets/UI/CharacterPanel.png"
#define ExpBar								30210007
#define ExpBarFile							"../assets/UI/ExpBar.png"
#define DialogBackground					30210008
#define DialogBackgroundFile				"../assets/UI/DialogBackground.png"
#define MessageboxMask						30210009
#define MessageboxMaskFile					"../assets/UI/MessageboxMask.png"
#define SkillPanelPic						30210010
#define SkillPanelPicFile					"../assets/UI/SkillPanelPic.png"
#define InventoryArrangeButton				30210011
#define InventoryArrangeButtonFile			"../assets/UI/InventoryArrangeButton.png"
#define SkillPanelAddSkillButton			30210012
#define SkillPanelAddSkillButtonFile		"../assets/UI/SkillPlusButton.png"
#define SkillPanelMinusSkillButton			30210013
#define SkillPanelMinusSkillButtonFile		"../assets/UI/SkillMinusButton.png"
#define xpBar								30210014
#define xpBarFile							"../assets/UI/expBar.png"
//Hostile 303
#define BlackBlock							30310000
#define BlackBlockFile						"../assets/entities/BlackBlock.png"
#define DemonHostile						30310001
#define DemonHostileFile					"../assets/entities/Demon.png"
#define HostileGhostMob						30310002
#define HostileGhostMobFile					"../assets/entities/GhostMob.png"
#define HostileSkeleton						30310003
#define HostileSkeletonFile					"../assets/entities/Skeleton.png"
#define HostileWoodMob						30310004
#define HostileWoodMobFile					"../assets/entities/WoodMob.png"
#define HostileGiantCat						30310005
#define HostileGiantCatFile					"../assets/entities/GiantCat.png"
#define HostilePigNPC						30310006
#define HostilePigNPCFile					"../assets/entities/PigNPC.png"
//Item 304
#define IronDartItem						30410000
#define IronDartItemName					"Iron Dart"
#define IronDartItemFile					"../assets/items/IronDartItem.png"
#define CrystalDartItem						30410001
#define CrystalDartName						"Crystal Dart"
#define CrystalDartItemFile					"../assets/items/CrystalDartItem.png"
#define MokbiDartItem						30410002
#define MokbiDartName						"Mokbi Dart"
#define MokbiDartItemFile					"../assets/items/MokbiDartItem.png"
//NPC 305
#define LeafNPC								30510000
#define LeafNPCFile							"../assets/LeafNPC.png"
#define GhostNPC							30510001
#define GhostNPCFile						"../assets/GhostNPC.png"
#define MapleFlagNPC						30510003
#define MapleFlagNPCFile					"../assets/MapleFlagNPC.png"
#define SavePointNPC						30510004
#define SavePointNPCFile					"../assets/SavePointNPC.png"
#define ShopNPC								30510005
#define ShopNPCFile							"../assets/ShopNPC.png"
//player 306
#define PlayerFrame							30610000
#define PlayerFrameFile						"../assets/PlayerFrame.png"
//projectile 307
#define SubiDartProjectile					30710000
#define SubiDartProjectileFile				"../assets/items/SubiDartProjectile.png"
#define IronDartProjectile					30710004
#define IronDartProjectileFile				"../assets/items/IronDartProjectile.png"
#define CrystalDartProjectile				30710005
#define CrystalDartProjectileFile			"../assets/items/CrystalDartProjectile.png"
#define MokbiDartProjectile					30710006
#define MokbiDartProjectileFile				"../assets/items/MokbiDartProjectile.png"
//sprite 308
#define WaterMushroomFrame					30810000
#define WaterMushroomFrameFile				"../assets/WaterMushroomFrame.png"
#define LadderSprite						30810001
#define LadderSpriteFile					"../assets/sprites/LadderSprite2.png"
#define MapGate								30810002
#define MapGateFile							"../assets/MapGate.png"
#define MapGate2							30810003
#define MapGate2File						"../assets/MapGate2.png"
#define TestPortal							30810004
#define TestPortalFile						"../assets/TestPortal.png"
#define Sprite01							30810005
#define Sprite01File						"../assets/sprites/Sprite01.png"
#define Sprite02							30810006
#define Sprite02File						"../assets/sprites/Sprite02.png"
#define Sprite03							30810007
#define Sprite03File						"../assets/sprites/Sprite03.png"
#define Sprite04							30810008
#define Sprite04File						"../assets/sprites/Sprite04.png"
#define Sprite05							30810009
#define Sprite05File						"../assets/sprites/Sprite05.png"
#define Sprite06							30810010
#define Sprite06File						"../assets/sprites/Sprite06.png"
#define Sprite07							30810011
#define Sprite07File						"../assets/sprites/Sprite07.png"
#define Sprite08							30810012
#define Sprite08File						"../assets/sprites/Sprite08.png"
#define Sprite09							30810013
#define Sprite09File						"../assets/sprites/Sprite09.png"
#define Sprite10							30810014
#define Sprite10File						"../assets/sprites/Sprite09.png"
//#define LadderSprite2						30810015
//#define LadderSprite2File					"../assets/sprites/LadderSprite2.png"
//Tile 309
#define Brick								30910000
#define BrickFile							"../assets/Brick.png"
#define Tile01								30910001
#define Tile01File							"../assets/tiles/Tile01.png"
#define Tile02								30910002
#define Tile02File							"../assets/tiles/Tile02.png"
#define Tile03								30910003
#define Tile03File							"../assets/tiles/Tile03.png"
#define Tile04								30910004
#define Tile04File							"../assets/tiles/Tile04.png"
#define Tile05								30910005
#define Tile05File							"../assets/tiles/Tile05.png"
#define Tile06								30910006
#define Tile06File							"../assets/tiles/Tile06.png"
#define Tile07								30910007
#define Tile07File							"../assets/tiles/Tile07.png"
#define Tile08								30910008
#define Tile08File							"../assets/tiles/Tile08.png"
#define Tile09								30910009
#define Tile09File							"../assets/tiles/Tile09.png"
///sounds 400xxxxx
//musics 400
#define Music01								40010000
#define Music01File							"../sounds/GoPicnic.mp3"
#define Music02								40010001
#define Music02File							"../sounds/music/AboveTheTreetops.mp3"
//menu sfxs 401
#define MenuMouseClick						40110000
#define MenuMouseClickFile					"../sounds/MenuMouseClick.mp3"
#define ControlKeyChangeSound1				40110001
#define ControlKeyChangeSound1File			"../sounds/MechanicalKey1.wav"
#define ControlKeyChangeSound2				40110001
#define ControlKeyChangeSound2File			"../sounds/MechanicalKey2.wav"
#define ControlKeyChangeSound3				40110001
#define ControlKeyChangeSound3File			"../sounds/MechanicalKey3.wav"
#define ControlKeyChangeSound4				40110001
#define ControlKeyChangeSound4File			"../sounds/MechanicalKey4.wav"
#define ControlKeyChangeSound5				40110001
#define ControlKeyChangeSound5File "		../sounds/MechanicalKey5.wav"

//game sfxs 402
#define WalkOnSnow1							40210001
#define WalkOnSnow1File						"../sounds/Snow1.ogg"
#define WalkOnSnow2							40210002
#define WalkOnSnow2File						"../sounds/Snow2.ogg"
#define WalkOnSnow3							40210003
#define WalkOnSnow3File						"../sounds/Snow3.ogg"
#define WalkOnSnow4							40210004
#define WalkOnSnow4File						"../sounds/Snow4.ogg"
#define AttackSound							40210005
#define AttackSoundFile						"../sounds/barehands.Attack.mp3"
#define CollisionSound						40210006
#define CollisionSouldFile					"../sounds/dualBow.Attack2.mp3"
#define DamageSound							40210007
#define DamageSoundFile						"../sounds/0100131.Damage.mp3"
#define DeathSound							40210008
#define DeathSoundFile						"../sounds/0100131.Die.mp3"
#define PortalNoise							40210009
#define PortalNoiseFile						"../sounds/PortalNoise.wav"
#define PickupSound							40210010
#define PickupSoundFile						"../sounds/PickUpItem.mp3"
#define LevelupSound						40210011
#define LevelupSoundFile					"../sounds/LevelupSound.wav"
#define JumpSound							40210012
#define JumpSoundFile						"../sounds/Jump.mp3"
#define PlayerDamageSound					40210013
#define PlayerDamageSoundFile				"../sounds/0100100.Damage.mp3"
#define WrapGateNoise						40210014
#define WrapGateNoiseFile					"../sounds/Portal.mp3"
#define HealingMagicSound					40210015
#define HealingMagicSoundFile				"../sounds/0001004.Use.mp3"
#define SpeedBuffSound						40210016
#define SpeedBuffSoundFile					"../sounds/0001004.Use.mp3"

#define DemonDamageSound					40210017
#define DemonDamageSoundFile				"../sounds/mob/DemonDamage.wav"
#define DemonDieSound						40210018
#define DemonDieSoundFile					"../sounds/mob/DemonDie.wav"
#define GhostMobDamageSound					40210019
#define GhostMobDamageSoundFile				"../sounds/mob/GhostMobDamage.wav"
#define GhostMobDieSound					40210020	   
#define GhostMobDieSoundFile				"../sounds/mob/GhostMobDie.wav"
#define GiantCatDamageSound					40210021
#define GiantCatDamageSoundFile				"../sounds/mob/GiantCatDamage.mp3"
#define GiantCatDieSound					40210022	   
#define GiantCatDieSoundFile				"../sounds/mob/GiantCatDie.mp3"
#define SkeletonDamageSound					40210023
#define SkeletonDamageSoundFile				"../sounds/mob/SkeletonDamage.wav"
#define SkeletonDieSound					40210024	   
#define SkeletonDieSoundFile				"../sounds/mob/SkeletonDie.wav"
#define WoodMobDamageSound					40210025
#define WoodMobDamageSoundFile				"../sounds/mob/WoodMobDamage.mp3"
#define WoodMobDieSound						40210026	  
#define WoodMobDieSoundFile					"../sounds/mob/WoodMobDie.mp3"
#define PigDamageSound						40210027
#define PigDamageSoundFile					"../sounds/mob/PigDamage.mp3"
#define PigDieSound							40210028	   
#define PigDieSoundFile						"../sounds/mob/PigDie.mp3"

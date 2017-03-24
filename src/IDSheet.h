#pragma once
#include <SDL.h>
#include <string>

///Transfers
std::string ScancodeToString(SDL_Scancode scannode);
int ExpSheet(int level);
///const
//global
#define TOTALSKILLS 2
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
#define COLOR_ORANGE	{241,145,73}
//savedata filepath
#define SettingsFile "..\\save\\settings.xm"
#define SavedataFile "..\\save\\savedata.xm"

enum SkillIndex
{
	HealingMagicIndex,
	DoubleIchorKnifeIndex
};

enum MapChangeType
{
	MAPCHANGE_LOAD,
	MAPCHANGE_LEFT,
	MAPCHANGE_RIGHT
};
///typeID 100xxxxx
//Object type
#define TypeButton						10010000
#define TypeInventory					10010001
#define TypeInventoryItem				10010002
#define TypeCharacterPanel				10010003
#define TypeDialog						10010004
#define TypeTextbox						10010005
#define TypeNPC							10010006
#define TypeHostile						10010007
#define TypeTile						10010008
#define TypePlayer						10010009
#define TypeProjectile					10010010
#define TypeSprite						10010011
#define TypeItem						10010012
#define TypeSkillPanel					10010013
#define TypeSkillSlot					10010014
#define TypeBuff						10010015
//menuID 101
#define MenuMain						10110000
#define MenuOptions						10110001
#define MenuGameMain					10110002
#define MenuControlSettings				10110003
#define MenuGameOver					10110004
//mapID 102
#define MapTest01						10210001
#define MapTest02						10210002
//menu elementsID 103
#define NewGameButton					10310000
#define ExitButton						10310001
#define OptionButton					10310002
#define ResolutionText					10310003
#define ResolutionListbox				10310004
#define FullscreenText					10310005
#define FullscreenCheckbox				10310006
#define FullscreenCheckboxFile			"..\\assets\\FullscreenCheckbox.png"
#define VolumnLButton					10310007
#define VolumnLButtonFile				"..\\assets\\VolumnLButton.png"
#define VolumnRButton					10310008
#define VolumnRButtonFile				"..\\assets\\VolumnRButton.png"
#define VolumnMasterText				10310009
#define VolumnMasterNumber				10310010
#define VolumnMusicText					10310011
#define VolumnMusicNumber				10310012
#define VolumnSfxText					10310013
#define VolumnSfxNumber					10310014
#define BackButton						10310015
#define ContinueButton					10310016
#define ControlSettingsButton			10310017
#define MainMenuBackgroundView			10310018
#define MainMenuBackgroundViewFile		"..\\assets\\MainMenuBackgroundView.png"
#define OptionsMenuView					10310019
#define OptionsMenuViewFile				"..\\assets\\OptionsMenuView.png"

#define ControlMovingUpText				10310200
#define ControlMovingUpButton			10310201
#define ControlMovingDownText			10310202
#define ControlMovingDownButton			10310203
#define ControlMovingLeftText			10310204
#define ControlMovingLeftButton			10310205
#define ControlMovingRightText			10310206
#define ControlMovingRightButton		10310207
#define ControlCharacterPanelText		10310208
#define ControlCharacterPanelButton		10310209
#define ControlSkillPanelText			10310210
#define ControlSkillPanelButton			10310211
#define ControlInventoryText			10310212
#define ControlInventoryButton			10310213
#define ControlSkillHotkey1Text			10310214
#define ControlSkillHotkey1Button		10310215
#define ControlSkillHotkey2Text			10310216
#define ControlSkillHotkey2Button		10310217
#define ControlSkillHotkey3Text			10310218
#define ControlSkillHotkey3Button		10310219

#define GameMenuBackground				10310100
#define GameMenuBackgroundFile			"..\\assets\\GameMenuBackground.png"
#define ResumeButton					10310101
#define ExittoMainMenuButton			10310102
#define ExittoDesktopButton				10310103
#define GameOverText					10310104
//button typeID 104
#define ButtonTypeTextbox				10410000
#define ButtonTypeButton				10410001
#define ButtonTypeBackground			10410002
//ItemClass 105
#define ItemClassWeapon					10510000
//skillID 106
#define HealingMagicSkill				10610000
#define HealingMagicSkillIcon			10610001
#define HealingMagicSkillIconFile		"..\\assets\\HealingMagicSkill.png"
#define IchorKnifeSkill					10610002
#define IchorKnifeSkillIcon				10610003
#define IchorKnifeSkillIconFile			"..\\assets\\IchorKnifeSkill.png"
//skilClass 107
#define SkillClassHealingMagic			10710000
#define SkillClassAttackingMagic		10710001

///fonts 200xxxxx
#define segoeuiFile						"..\\fonts\\segoeui.ttf"
#define segoeui18						20010000
#define segoeui22						20010001
#define segoeui28						20010002
#define arialFile						"..\\fonts\\arial.ttf"
#define arial28_bold					20010010
#define arial48_bold					20010011
#define arial72_bold					20010012
///texture res 300xxxxx
//menu res
#define MainMenuPic						30010000
#define MainMenuPicFile					"..\\assets\\MainMenuBackground.png"
//background 301
#define MapBackground					30110000
#define MapBackgroundFile				"..\\assets\\Background.png"
#define MapBackground2					30110001
#define MapBackground2File				"..\\assets\\background2.png"
//panel and UIs 302
#define UIpic							30210000
#define UIpicFile						"..\\assets\\UIpic.png"
#define HealthBar						30210001
#define HealthBarFile					"..\\assets\\HealthBar.png"
#define ManaBar							30210002
#define ManaBarFile						"..\\assets\\ManaBar.png"
#define InventoryGrid					30210003
#define InventoryGridFile				"..\\assets\\InventoryGrid.png"
#define InventoryGridMask				30210004
#define InventoryGridMaskFile			"..\\assets\\InventoryGridMask.png"
#define InventoryCloseButton			30210005
#define InventoryCloseButtonFile		"..\\assets\\InventoryCloseButton.png"
#define CharacterPanelPic				30210006
#define CharacterPanelPicFile			"..\\assets\\CharacterPanel.png"
#define ExpBar							30210007
#define ExpBarFile						"..\\assets\\ExpBar.png"
#define DialogBackground				30210008
#define DialogBackgroundFile			"..\\assets\\DialogBackground.png"
#define MessageboxMask					30210009
#define MessageboxMaskFile				"..\\assets\\MessageboxMask.png"
#define SkillPanelPic					30210010
#define SkillPanelPicFile				"..\\assets\\SkillPanelPic.png"
#define InventoryArrangeButton			30210011
#define InventoryArrangeButtonFile		"..\\assets\\InventoryArrangeButton.png"
#define SkillPanelAddSkillButton		30210012
#define SkillPanelAddSkillButtonFile	"..\\assets\\SkillPlusButton.png"
#define SkillPanelMinusSkillButton		30210013
#define SkillPanelMinusSkillButtonFile	"..\\assets\\SkillMinusButton.png"
#define xpBar							30210014
#define xpBarFile						"..\\assets\\expBar.png"
//Hostile 303
#define BlackBlock						30310000
#define BlackBlockFile					"..\\assets\\BlackBlock.png"
#define DemonHostile					30310001
#define DemonHostileFile				"..\\assets\\Demon.png"
//Item 304
#define IronDartItem					30410000
#define IronDartItemName				"Iron Dart"
#define IronDartItemFile				"..\\assets\\items\\IronDartItem.png"
//NPC 305
#define LeafNPC							30510000
#define LeafNPCFile						"..\\assets\\LeafNPC.png"
#define GhostNPC						30510001
#define GhostNPCFile					"..\\assets\\GhostNPC.png"
#define MapleFlagNPC					30510003
#define MapleFlagNPCFile				"..\\assets\\MapleFlagNPC.png"
#define SavePointNPC					30510004
#define SavePointNPCFile				"..\\assets\\SavePointNPC.png"
#define ShopNPC							30510005
#define ShopNPCFile						"..\\assets\\ShopNPC.png"
//player 306
#define PlayerFrame						30610000
#define PlayerFrameFile					"..\\assets\\PlayerFrame.png"
//projectile 307
#define IchorKnifeProjectile			30710000
#define IchorKnifeProjectileFile		"..\\assets\\IchorKnifeProjectile.png"
#define OrichalcumShortswordProjectile	30710001
#define OrichalcumShortswordProjectileFile "..\\assets\\OrichalcumShortsword.png"
#define PurificationBulletProjectile	30710002
#define PurificationBulletProjectileFile	"..\\assets\\PurificationBulletProjectile.png"
#define ChlorophyteTrackerProjectile	30710003
#define ChlorophyteTrackerProjectileFile	"..\\assets\\ChlorophyteTracker.png"
//sprite 308
#define WaterMushroomFrame 30810000
#define WaterMushroomFrameFile "..\\assets\\WaterMushroomFrame.png"
#define LadderSprite 30810001
#define LadderSpriteFile "..\\assets\\LadderSprite.png"
#define MapGate 30810002
#define MapGateFile "..\\assets\\MapGate.png"
#define MapGate2 30810003
#define MapGate2File "..\\assets\\MapGate2.png"
#define TestPortal 30810004
#define TestPortalFile "..\\assets\\TestPortal.png"
//Tile 309
#define Brick 30910000
#define BrickFile "..\\assets\\Brick.png"
#define Tile01 30910001
#define Tile01File "..\\assets\\Tile01.png"
///sounds 400xxxxx
//musics 400
#define Music01 40010000
#define Music01File "..\\sounds\\GoPicnic.mp3"
//menu sfxs 401
#define MenuMouseClick				40110000
#define MenuMouseClickFile			"..\\sounds\\MenuMouseClick.mp3"
#define ControlKeyChangeSound1		40110001
#define ControlKeyChangeSound1File	"..\\sounds\\MechanicalKey1.wav"
#define ControlKeyChangeSound2		40110001
#define ControlKeyChangeSound2File	"..\\sounds\\MechanicalKey2.wav"
#define ControlKeyChangeSound3		40110001
#define ControlKeyChangeSound3File	"..\\sounds\\MechanicalKey3.wav"
#define ControlKeyChangeSound4		40110001
#define ControlKeyChangeSound4File	"..\\sounds\\MechanicalKey4.wav"
#define ControlKeyChangeSound5		40110001
#define ControlKeyChangeSound5File "..\\sounds\\MechanicalKey5.wav"

//game sfxs 402
#define WalkOnSnow1					40210001
#define WalkOnSnow1File				"..\\sounds\\Snow1.ogg"
#define WalkOnSnow2					40210002
#define WalkOnSnow2File				"..\\sounds\\Snow2.ogg"
#define WalkOnSnow3					40210003
#define WalkOnSnow3File				"..\\sounds\\Snow3.ogg"
#define WalkOnSnow4					40210004
#define WalkOnSnow4File				"..\\sounds\\Snow4.ogg"
#define AttackSound					40210005
#define AttackSoundFile				"..\\sounds\\barehands.Attack.mp3"
#define CollisionSound				40210006
#define CollisionSouldFile			"..\\sounds\\dualBow.Attack2.mp3"
#define DamageSound					40210007
#define DamageSoundFile				"..\\sounds\\0100131.Damage.mp3"
#define DeathSound					40210008
#define DeathSoundFile				"..\\sounds\\0100131.Die.mp3"
#define PortalNoise					40210009
#define PortalNoiseFile				"..\\sounds\\PortalNoise.wav"
#define PickupSound					40210010
#define PickupSoundFile				"..\\sounds\\PickUpItem.mp3"
#define LevelupSound				40210011
#define LevelupSoundFile			"..\\sounds\\LevelupSound.wav"
#define JumpSound					40210012
#define JumpSoundFile				"..\\sounds\\Jump.mp3"
#define PlayerDamageSound			40210013
#define PlayerDamageSoundFile		"..\\sounds\\0100100.Damage.mp3"
#define WrapGateNoise				40210014
#define WrapGateNoiseFile			"..\\sounds\\Portal.mp3"
#define HealingMagicSound			40210015
#define HealingMagicSoundFile		"..\\sounds\\0001004.Use.mp3"
#define SpeedBuffSound				40210016
#define SpeedBuffSoundFile			"..\\sounds\\0001004.Use.mp3"
#define DemonDamageSound			40210017
#define DemonDamageSoundFile		"..\\sounds\\DemonDamage.wav"
#define DemonDeathSound				40210018
#define DemonDeathSoundFile			"..\\sounds\\DemonDie.wav"

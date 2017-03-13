#pragma once
///const
//global
#define CLICKCOOLDOWN 80
#define PRESSCOOLDOWN 100
#define UIHEIGHT 168
//colors
#define COLOR_WHITE {255,255,255}
#define COLOR_RED {255,0,0}
#define COLOR_GREEN {0,255,0}
#define COLOR_BLUE {0,0,255}
#define COLOR_CLAN {0,255,255}
#define COLOR_ORANGE {241,145,73}
//savedata filepath
#define SettingsFile "save\\settings.xm"
#define SavedataFile "save\\savedata.xm"
///typeID 100xxxxx
//Object type
#define TypeButton 10010000
#define TypeInventory 10010001
#define TypeInventoryItem 10010002
#define TypeCharacterPanel 10010003
#define TypeDialog 10010004
#define TypeTextbox 10010005
#define TypeNPC 10010006
#define TypeHostile 10010007
#define TypeTile 10010008
#define TypePlayer 10010009
#define TypeProjectile 10010010
#define TypeSprite 10010011
#define TypeItem 10010012
//menuID 101
#define MenuMain 10110000
#define MenuOptions 10110001
#define MenuGameMain 10110002
//mapID 102
#define MapTest01 10210001
#define MapTest02 10210002
//menu elementsID 103
#define NewGameButton 10310000
#define ExitButton 10310001
#define OptionButton 10310002
#define ResolutionText 10310003
#define ResolutionListbox 10310004
#define FullscreenText 10310005
#define FullscreenCheckbox 10310006
#define FullscreenCheckboxFile "assets\\FullscreenCheckbox.png"
#define VolumnLButton 10310007
#define VolumnLButtonFile "assets\\VolumnLButton.png"
#define VolumnRButton 10310008
#define VolumnRButtonFile "assets\\VolumnRButton.png"
#define VolumnMasterText 10310009
#define VolumnMasterNumber 10310010
#define VolumnMusicText 10310011
#define VolumnMusicNumber 10310012
#define VolumnSfxText 10310013
#define VolumnSfxNumber 10310014
#define BackButton 10310015
#define ContinueButton 10310016

#define GameMenuBackground 10310100
#define GameMenuBackgroundFile "assets\\GameMenuBackground.png"
#define ResumeButton 10310101
#define ExittoMainMenuButton 10310102
#define ExittoDestopButton 10310103
//button typeID 104
#define ButtonTypeTextbox 10410000
#define ButtonTypeButton 10410001
//ItemClass 105
#define ItemClass_Weapon 10510000
///fonts 200xxxxx
#define segoeuiFile "fonts\\segoeui.ttf"
#define segoeui18 20010000
#define segoeui22 20010001
#define segoeui28 20010002
#define arialFile "fonts\\arial.ttf"
#define arial28_bold 20010010
#define arial48_bold 20010011
#define arial72_bold 20010012
///texture res 300xxxxx
//menu res
#define MainMenuPic 30010000
#define MainMenuPicFile "assets\\MainMenuBackground.png"
//background 301
#define MapBackground 30110000
#define MapBackgroundFile "assets\\Background.png"
#define MapBackground2 30110001
#define MapBackground2File "assets\\background2.png"
//panel and UIs 302
#define UIpic 30210000
#define UIpicFile "assets\\UIpic.png"
#define HealthBar 30210001
#define HealthBarFile "assets\\HealthBar.png"
#define ManaBar 30210002
#define ManaBarFile "assets\\ManaBar.png"
#define InventoryGrid 30210003
#define InventoryGridFile "assets\\InventoryGrid.png"
#define InventoryGridMask 30210004
#define InventoryGridMaskFile "assets\\InventoryGridMask.png"
#define InventoryCloseButton 30210005
#define InventoryCloseButtonFile "assets\\InventoryCloseButton.png"
#define CharacterPanelPic 30210006
#define CharacterPanelPicFile "assets\\CharacterPanel.png"
#define ExpBar 30210007
#define ExpBarFile "assets\\ExpBar.png"
#define DialogBackground 30210008
#define DialogBackgroundFile "assets\\DialogBackground.png"
#define MessageboxMask 30210009
#define MessageboxMaskFile "assets\\MessageboxMask.png"
//Hostile 303
#define BlackBlock 30310000
#define BlackBlockFile "assets\\BlackBlock.png"
//Item 304
#define WoodenSword 30410000
#define WoodenSwordName "Wooden Sword"
#define WoodenSwordFile "assets\\WoodenSword.png"
#define OrichalcumShortsword 30410001
#define OrichalcumShortswordName "Orichalcum Shortsword"
#define OrichalcumShortswordFile "assets\\OrichalcumShortsword.png"
//NPC 305
#define LeafNPC 30510000
#define LeafNPCFile "assets\\LeafNPC.png"
#define GhostNPC 30510001
#define GhostNPCFile "assets\\GhostNPC.png"
#define MapleFlagNPC 30510003
#define MapleFlagNPCFile "assets\\MapleFlagNPC.png"
#define SavePointNPC 30510004
#define SavePointNPCFile "assets\\SavePointNPC.png"
//player 306
#define PlayerFrame 30610000
#define PlayerFrameFile "assets\\PlayerFrame.png"
//projectile 307
#define IchorKnifeProjectile 30710000
#define IchorKnifeProjectileFile "assets\\IchorKnifeProjectile.png"
#define OrichalcumShortswordProjectile 30710001
#define OrichalcumShortswordProjectileFile "assets\\OrichalcumShortsword.png"
//sprite 308
#define WaterMushroomFrame 30810000
#define WaterMushroomFrameFile "assets\\WaterMushroomFrame.png"
#define LadderSprite 30810001
#define LadderSpriteFile "assets\\LadderSprite.png"
#define MapGate 30810002
#define MapGateFile "assets\\MapGate.png"
#define MapGate2 30810003
#define MapGate2File "assets\\MapGate2.png"
#define TestPortal 30810004
#define TestPortalFile "assets\\TestPortal.png"
//Tile 309
#define Brick 30910000
#define BrickFile "assets\\Brick.png"
#define Tile01 30910001
#define Tile01File "assets\\Tile01.png"
///sounds 400xxxxx
//musics 400
#define Music01 40010000
#define Music01File "sounds\\GoPicnic.mp3"
//sfxs 401
#define MenuMouseClick 40110000
#define MenuMouseClickFile "sounds\\MenuMouseClick.mp3"

#define WalkOnSnow1 40110001
#define WalkOnSnow1File "sounds\\Snow1.ogg"
#define WalkOnSnow2 40110002
#define WalkOnSnow2File "sounds\\Snow2.ogg"
#define WalkOnSnow3 40110003
#define WalkOnSnow3File "sounds\\Snow3.ogg"
#define WalkOnSnow4 40110004
#define WalkOnSnow4File "sounds\\Snow4.ogg"
#define AttackSound 40110005
#define AttackSoundFile "sounds\\barehands.Attack.mp3"
#define CollisionSound 40110006
#define CollisionSouldFile "sounds\\dualBow.Attack2.mp3"
#define DamageSound 40110007
#define DamageSoundFile "sounds\\0100131.Damage.mp3"
#define DeathSound 40110008
#define DeathSoundFile "sounds\\0100131.Die.mp3"
#define PortalNoise 40110009
#define PortalNoiseFile "sounds\\PortalNoise.wav"
#define PickupSound 40110010
#define PickupSoundFile "sounds\\PickUpItem.mp3"
#define LevelupSound 40110011
#define LevelupSoundFile "sounds\\LevelupSound.wav"
#define JumpSound 40110012
#define JumpSoundFile "sounds\\Jump.mp3"
#define PlayerDamageSound 40110013
#define PlayerDamageSoundFile "sounds\\0100100.Damage.mp3"
#define WrapGateNoise 40110014
#define WrapGateNoiseFile "sounds\\Portal.mp3"

int ExpSheet(int level);
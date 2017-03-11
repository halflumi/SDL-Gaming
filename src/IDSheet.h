#pragma once

//global
#define CLICKCOOLDOWN 100
#define PRESSCOOLDOWN 100
#define UIHEIGHT 168
//colors
#define COLOR_WHITE {255,255,255}
#define COLOR_RED {255,0,0}
#define COLOR_GREEN {0,255,0}
#define COLOR_BLUE {0,0,255}
#define COLOR_ORANGE {241,145,73}
//menuID
#define Menu_Main 10000
#define Menu_Options 10001
//menu elements
#define MainMenu "Main_Menu"
#define MainMenuFile "assets\\Main_Menu.png"
#define NewGameButton "NewGameButton"
#define ExitButton "ExitButton"
#define OptionButton "OptionButton"
#define FullscreenText "FullscreenText"
#define FullscreenCheckbox "FullscreenCheckbox"
#define FullscreenCheckboxFile "assets\\FullscreenCheckbox.png"
#define BackButton "BackButton"
//fonts
#define segoeuiFile "fonts\\segoeui.ttf"
#define segoeui18 "segoeui18"
#define segoeui22 "segoeui22"
#define segoeui28 "segoeui28"
#define arialFile "fonts\\arial.ttf"
#define arial28 "arial28"
#define arial48 "arial48"
//mapID
#define MapTest01 10001
#define MapTest02 10002
//background
#define Background "background"
#define BackgroundFile "assets\\Background.png"
#define Background2 "background2"
#define Background2File "assets\\background2.png"
//panel and UIs
#define UIpic "UIpic"
#define UIpicFile "assets\\UIpic.png"
#define HealthBar "HealthBar"
#define HealthBarFile "assets\\HealthBar.png"
#define ManaBar "ManaBar"
#define ManaBarFile "assets\\ManaBar.png"
#define InventoryGrid "InventoryGrid"
#define InventoryGridFile "assets\\InventoryGrid.png"
#define InventoryGridMask "InventoryGridMask"
#define InventoryGridMaskFile "assets\\InventoryGridMask.png"
#define InventoryCloseButton "InventoryCloseButton"
#define InventoryCloseButtonFile "assets\\InventoryCloseButton.png"
#define CharacterPanelPic "CharacterPanel"
#define CharacterPanelPicFile "assets\\CharacterPanel.png"
#define ExpBar "ExpBar"
#define ExpBarFile "assets\\ExpBar.png"
#define DialogBackground "DialogBackground"
#define DialogBackgroundFile "assets\\DialogBackground.png"

//Object type
#define TypeButton "button"
#define TypeInventory "inventory"
#define TypeInventoryItem "inventoryitem"
#define TypeCharacterPanel "characterpanel"
#define TypeDialog "dialog"
#define TypeTextbox "textbox"
#define TypeNPC "npc"
#define TypeHostile "hostile"
#define TypeTile "tile"
#define TypePlayer "player"
#define TypeProjectile "projectile"
#define TypeSprite "sprite"
#define TypeItem "item"

//Hostile
#define BlackBlock "BlackBlock"
#define BlackBlockFile "assets\\BlackBlock.png"
//ItemClass
#define ItemClass_Weapon 1
//Item
#define WoodenSword "WoodenSword"
#define WoodenSwordFile "assets\\WoodenSword.png"
#define OrichalcumShortsword "OrichalcumShortsword"
#define OrichalcumShortswordFile "assets\\OrichalcumShortsword.png"
//NPC
#define LeafNPC "LeafNPC"
#define LeafNPCFile "assets\\LeafNPC.png"
#define GhostNPC "GhostNPC"
#define GhostNPCFile "assets\\GhostNPC.png"
#define TestPortal "TestPortal"
#define TestPortalFile "assets\\TestPortal.png"
//player
#define PlayerFrame "PlayerFrame"
#define PlayerFrameFile "assets\\PlayerFrame.png"
//projectile
#define IchorKnifeProjectile "IchorKnifeProjectile"
#define IchorKnifeProjectileFile "assets\\IchorKnifeProjectile.png"
#define OrichalcumShortswordProjectile "OrichalcumShortswordProjectile"
#define OrichalcumShortswordProjectileFile "assets\\OrichalcumShortsword.png"
//sprite
#define WaterMushroomFrame "WaterMushroomFrame"
#define WaterMushroomFrameFile "assets\\WaterMushroomFrame.png"
#define LadderSprite "LadderSprite"
#define LadderSpriteFile "assets\\LadderSprite.png"
#define MapGate "MapGate"
#define MapGateFile "assets\\MapGate.png"
#define MapGate2 "MapGate2"
#define MapGate2File "assets\\MapGate2.png"
//Tile
#define Brick "Brick"
#define BrickFile "assets\\Brick.png"
#define Tile01 "Tile01"
#define Tile01File "assets\\Tile01.png"
//sounds
#define Music01 "GoPicnic"
#define Music01File "sounds\\GoPicnic.mp3"

#define MenuMouseClick "MenuMouseClick"
#define MenuMouseClickFile "sounds\\MenuMouseClick.mp3"

#define WalkOnSnow1 "Snow1"
#define WalkOnSnow1File "sounds\\Snow1.ogg"
#define WalkOnSnow2 "Snow2"
#define WalkOnSnow2File "sounds\\Snow2.ogg"
#define WalkOnSnow3 "Snow3"
#define WalkOnSnow3File "sounds\\Snow3.ogg"
#define WalkOnSnow4 "Snow4"
#define WalkOnSnow4File "sounds\\Snow4.ogg"
#define AttackSound "barehands.Attack"
#define AttackSoundFile "sounds\\barehands.Attack.mp3"
#define CollisionSound "dualBow.Attack2"
#define CollisionSouldFile "sounds\\dualBow.Attack2.mp3"
#define DamageSound "0100131.Damage"
#define DamageSoundFile "sounds\\0100131.Damage.mp3"
#define DeathSound "0100131.Die"
#define DeathSoundFile "sounds\\0100131.Die.mp3"
#define PortalNoise "PortalNoise"
#define PortalNoiseFile "sounds\\PortalNoise.wav"
#define PickupSound "PickUpItem"
#define PickupSoundFile "sounds\\PickUpItem.mp3"
#define LevelupSound "LevelupSound"
#define LevelupSoundFile "sounds\\LevelupSound.wav"
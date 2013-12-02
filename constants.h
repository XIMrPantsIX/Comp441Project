// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 constants.h v1.1

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//=============================================================================
// Function templates for safely dealing with pointer referenced items.
// The functions defined by these templates may be called using a normal
// function call syntax. The compiler will create a function that replaces T
// with the type of the calling parameter.
//=============================================================================
// Safely release pointer referenced item
template <typename T>
inline void safeRelease(T& ptr)
{
    if (ptr)
    { 
        ptr->Release(); 
        ptr = NULL;
    }
}
#define SAFE_RELEASE safeRelease            // for backward compatiblility

// Safely delete pointer referenced item
template <typename T>
inline void safeDelete(T& ptr)
{
    if (ptr)
    { 
        delete ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE safeDelete              // for backward compatiblility

// Safely delete pointer referenced array
template <typename T>
inline void safeDeleteArray(T& ptr)
{
    if (ptr)
    { 
        delete[] ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE_ARRAY safeDeleteArray   // for backward compatiblility

// Safely call onLostDevice
template <typename T>
inline void safeOnLostDevice(T& ptr)
{
    if (ptr)
        ptr->onLostDevice(); 
}
#define SAFE_ON_LOST_DEVICE safeOnLostDevice    // for backward compatiblility

// Safely call onResetDevice
template <typename T>
inline void safeOnResetDevice(T& ptr)
{
    if (ptr)
        ptr->onResetDevice(); 
}
#define SAFE_ON_RESET_DEVICE safeOnResetDevice  // for backward compatiblility

//=============================================================================
//                  Constants
//=============================================================================

// window
const char CLASS_NAME[] = "Anax";
const char GAME_TITLE[] = "Anax";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  1280;               // width of game in pixels
const UINT GAME_HEIGHT = 640;               // height of game in pixels

// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const RECT  COLLISION_TILE = {-94,-280,94,400};
const RECT	COLLISION_BOX_SKELLINGTON = {-25, -50, 25, 50};
const RECT  COLLISION_BOX_HERO = {-22,-39,22,39};
const RECT COLLISION_BOX_SLIME = {-30,-30, 30, 30};
const RECT COLLISION_BOX_PUCK = {-10, -10, 10, 10};
const float   COLLISION_RADIUS = 29;
const int FIREBALL_DMG = 2;

// graphic images
const char MOUNTAIN_IMAGE[] =   "pictures\\Mountain2.png";     // dude it's a farm
const char CLOUD_IMAGE[] = "pictures\\Cloudinvisibro.png";
const char CLOUD2_IMAGE[] = "pictures\\Cloud.png";
const char TILE1_IMAGE[] = "pictures\\Tile1.png";
const char BACKGROUND_IMAGE[] = "pictures\\background.png";
const char CATTAILS[] = "pictures\\cattails.png";
const char HERO_IMAGE[] = "pictures\\DudeManBro.png";
const char MC_HERO_IMAGE[] = "pictures\\Master Chief DudeManBro.png";
const char HERO_SWORD_IMAGE[]= "pictures\\SwordSpriteSheet.png";
const char TILE2_IMAGE[] = "pictures\\Stone Tile.png";
const char CASTLE_TILE[] = "pictures\\Castle.png";
const char CASTLE_WALL_TILE[] = "pictures\\Castle Wall.png";
const char BUSHES_IMAGE[] = "pictures\\Bushes.png";
const char FLOWERS_IMAGE[] = "pictures\\Flowers.png";
const char DISK_FLOWERS_IMAGE[] = "pictures\\Disk Flowers.png";
const char TORCH_IMAGE[] = "pictures\\Torches.png";
const char TREE_IMAGE[] = "pictures\\Tree.png";
const char HEART_IMAGE[] = "pictures\\Heart.png";
const char HALF_HEART_IMAGE[] = "pictures\\Half Heart.png";
const char EMPTY_HEART_IMAGE[] = "pictures\\Empty Heart.png";
const char DIALOG_BOX_IMAGE[] = "pictures\\menuBack.png";
const char SLIMES_IMAGE[] = "pictures\\Slimes.png";
const char CAVE_WALL_IMAGE[] = "pictures\\Cave Wall.png";
const char NO_SWORD_IMAGE[] = "pictures\\noSwordSpriteSheet.png";
const char MC_NO_SWORD_IMAGE[] = "pictures\\Master Chief No Sword.png";
const char SWORD_IN_STONE_IMAGE[] = "pictures\\swordSpriteSheet.png";
const char SKELLINGTON_IMAGE[] = "pictures\\skellington.png";
const char FIREBALL_IMAGE[] = "pictures\\Fireball.png";
const char MAGICMISSILE_IMAGE[] = "pictures\\MagicMissile.png";
const char DEATH_SHEET_IMAGE[] = "pictures\\Death Sheet.png";
const char END_SCREEN_IMAGE[] = "pictures\\End Screen.png";

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY			= VK_ESCAPE;	// escape key
const UCHAR ALT_KEY			= VK_MENU;		// Alt key
const UCHAR PADDLE_LEFT		= VK_LEFT;		// left arrow
const UCHAR PADDLE_RIGHT	= 0x64;		// right arrow
const UCHAR ENTER_KEY		= VK_RETURN;	//  Enter Key
const UCHAR SPACE_KEY		= VK_SPACE;		// Spacebar


// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[]  = "audio\\Win\\Wave Bank.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\Sound Bank.xsb";

// audio cues
const char SKELLINGTON[] = "bonehead";
const char SKELLINGTON_DIE[] = "boneheaddead";
const char JUMP[] = "jump";
const char LAND[] = "land";
const char SLIME[]   = "slimemove";
const char SLIME_DIE[] = "pfshfhsfhl";
const char WHOOSH[] = "whoosh";
const char LVL1BG[] = "level1";
const char LVL2BG[] = "level2";


//Animation STURRRRRRFFFFFS
//Animation STURRRRRRFFFFFS
const int HERO_STANDING_LEFT_START = 2;
const int HERO_STANDING_LEFT_END = 3;
const int HERO_STANDING_RIGHT_START = 0;
const int HERO_STANDING_RIGHT_END = 1;
const int HERO_WALKING_LEFT_START = 4;
const int HERO_WALKING_LEFT_END = 8;
const int HERO_WALKING_RIGHT_START = 10;
const int HERO_WALKING_RIGHT_END = 14;
const int HERO_JUMPING_LEFT_START = 16;
const int HERO_JUMPING_LEFT_END = 19;
const int HERO_JUMPING_RIGHT_START = 20;
const int HERO_JUMPING_RIGHT_END = 24;
const int HERO_ATTACKING_RIGHT_START = 25;
const int HERO_ATTACKING_RIGHT_END = 33;
const int HERO_ATTACKING_LEFT_START = 35;
const int HERO_ATTACKING_LEFT_END = 43;

const int UNARMED_STANDING_LEFT_START = 44+2;
const int UNARMED_STANDING_LEFT_END = 44+3;
const int UNARMED_STANDING_RIGHT_START = 44+0;
const int UNARMED_STANDING_RIGHT_END = 44+1;
const int UNARMED_WALKING_LEFT_START = 44+4;
const int UNARMED_WALKING_LEFT_END = 44+8;
const int UNARMED_WALKING_RIGHT_START = 44+10;
const int UNARMED_WALKING_RIGHT_END = 44+14;
const int UNARMED_JUMPING_LEFT_START = 44+16;
const int UNARMED_JUMPING_LEFT_END = 44+19;
const int UNARMED_JUMPING_RIGHT_START = 44+20;
const int UNARMED_JUMPING_RIGHT_END = 44+24;


const int SLIME_0 = 0;
const int SLIME_1 = 1;
const int SLIME_2 = 2;
const int SLIME_3 = 3;

const int TORCH_FIRST = 1;
const int TORCH_LAST = 3;

const int SWORD_FIRST = 0;
const int SWORD_LAST = 27;

const int SKELLINGTON_0 = 0;
const int SKELLINGTON_1 = 1;
const int SKELLINGTON_2 = 2;
const int SKELLINGTON_3 = 3;
const int SKELLINGTON_4 = 4;
const int SKELLINGTON_5 = 5;


#endif


//how do you defeat a mini minotaur?
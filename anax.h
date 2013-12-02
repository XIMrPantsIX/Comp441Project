#ifndef _ANAX_H
#define	_ANAX_H
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <sstream>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "textDX.h"
#include "menu.h"
#include "entity.h"
#include "Mountain.h"
#include "Tile.h"
#include "Hero.h"
#include "Slime.h"
#include "skellington.h";
using std::string;

const int MAX_SKELLINGTONS = 20;
const int MAX_SLIMES = 5;
const int MOUNTAIN_MAX = 7;
const int MAX_FLOWERS = 30;
const int MAX_DISK_FLOWERS = 30;
const int MAX_TREES = 30;
const int MAX_BUSHES = 30;
const int MAX_CASTLE_WALLS = 100;
const int MAX_TORCHES = 30;
enum DIRECTIONS {left, right, middle, up, down, rightSpecial};
enum LEVEL_TEXTURE {level1, level2, level3};

class Anax : public Game
{
private:
	Menu *mainMenu;
	std::string outString;
	bool isMenuOn;
	bool isDialogOn;
	bool isRunningGame;
	bool isGameOver;
	float world_coordinates;
	bool moveScreen;
	float frameTimeSword;
	float frameTimeTorch;
	int endOfLevel;
	bool cheatsOn;

	//World Members
	TextDX *dxCoordinates;
	TextDX *dxDialog;
	VECTOR2 collisionVector;    // collision vector
	TextureManager cloudTexture;
	TextureManager cloud2Texture;
	TextureManager mountainTexture;
	TextureManager frontMountainsTexture;
	TextureManager backgroundTexture;
	TextureManager dialogBoxTexture;
	TextureManager cattailsTexture;
	TextureManager flowersTexture;
	TextureManager diskFlowersTexture;
	TextureManager treeTexture;
	TextureManager bushesTexture;
	TextureManager torchTexture;
	TextureManager heartTexture;
	TextureManager heart2Texture;
	TextureManager heart3Texture;
	TextureManager halfHeartTexture;
	TextureManager halfHeart2Texture;
	TextureManager halfHeart3Texture;
	TextureManager emptyHeartTexture;
	TextureManager emptyHeart2Texture;
	TextureManager emptyHeart3Texture;
	TextureManager caveWallTexture;
	TextureManager swordTexture;
	TextureManager skellingtonTexture;
	TextureManager magicMissileTexture;
	TextureManager deathSheetTexture;
	TextureManager endScreenTexture;
	Image background;
	Image dialogBox;
	Entity cattails;
	Entity cloud;
	Entity cloud2;
	Entity flowers[MAX_FLOWERS];
	Entity diskFlowers[MAX_DISK_FLOWERS];
	Entity tree[MAX_TREES];
	Entity bushes[MAX_BUSHES];
	Entity torch[MAX_TORCHES];
	Entity heart;
	Entity heart2;
	Entity heart3;
	Entity halfHeart;
	Entity halfHeart2;
	Entity halfHeart3;
	Entity emptyHeart;
	Entity emptyHeart2;
	Entity emptyHeart3;
	Entity caveWall;
	Entity sword;
	Entity skellington;
	Entity magicMissile;
	Entity deathSheet;
	Entity endScreen;
	std::stringstream ss;
	string dialogIn;
	string in;
	Mountain mountain[MOUNTAIN_MAX];
	Mountain frontMountains[MOUNTAIN_MAX];
	int mountainSide[MOUNTAIN_MAX];
	int mountainFront[MOUNTAIN_MAX];
	/*  end world members  */


	/*Character Members*/
	TextureManager heroTexture;
	Hero dudeManBro;
	TextureManager unarmedHeroTexture;
	Hero unarmedHero;
	TextureManager slimeTexture;

	/*Map Members*/
	TextureManager tile1Texture;
	TextureManager tile2Texture;
	TextureManager castleTexture;
	TextureManager castleWallTexture;
	Tile tile1[MAX_TILES];
	Tile tile2[MAX_TILES];
	Tile castle;
	Tile castleWall[MAX_CASTLE_WALLS];



	Enemy *enemy[2][50];




public:
	
	Anax();
	virtual ~Anax();
	void initialize(HWND hwnd);
	//Updates
	void handleInput();
	void setGameState(int i);
	void resetGameState(int i);

	/*this section overrides Game: */
    void update();            
    void collisions();  
    void render();      
    void releaseAll();
    void resetAll();

	int gameState;
	/*character Functions*/
	void initializeEntities(HWND hwnd);
	void entityTileCollisions();
	void entityEntityCollisions();
	void updateEntities();
	/*World Functions*/
	int getMountainSide(int side);
	int getMountainFront(int side);
	int nextPeak(int i, int side);
	void initializeWorld(HWND hwnd);
	void updateWorld1(float frameTime);
	void updateWorld2(float frameTime);
	void displayCoordinates();
	void dialogChecker();
	void turnDialogOn();
	string getDialog(){return dialogIn;}
	/*MapTile Functions*/
	void initializeTiles(HWND hwnd);
	void updateTiles(float frameTime);
	float tilePositionPlacerX(int i);
	float tilePositionPlacerY(int i);
	void initializeUI(HWND hwnd);
	void initializeEnemies(HWND hwnd);
	/*Render Helpers*/
	void drawHealth();












	void initializeSkellington(HWND hwnd, int i);
	void initializeSlime(HWND hwnd, int i);
};

#endif
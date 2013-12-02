#include "Anax.h"

/*****************************************************************************************************
// Class initialize function
// Initializes all sprites 
*****************************************************************************************************/
void Anax::initialize(HWND hwnd) {
	Game::initialize(hwnd);
	endOfLevel = false;
	cheatsOn = false;
	gameState = 0;
	world_coordinates = 0;
	moveScreen = false;
	isDialogOn = true;
	frameTimeSword = 0;
	frameTimeTorch = 0;
	isRunningGame = false;
	vector<string> v;
	v.push_back("PLAY");
	v.push_back("CHEATS OFF");
	v.push_back("QUIT");
	v.push_back("ANAX");
	mainMenu = new Menu(v,D3DXVECTOR2(GAME_WIDTH/2,GAME_HEIGHT/2));
	mainMenu->initialize(graphics, input);
	if(dxDialog->initialize(graphics, 15, true, false, "Arial") == false)
    throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing output font"));
	initializeWorld(hwnd);
	initializeTiles(hwnd);
	initializeEntities(hwnd);
	initializeEnemies(hwnd);
	initializeUI(hwnd);

}

void Anax::resetGameState(int i) {
	if(i==0) {
		isRunningGame = false;
	}
	endOfLevel = false;
	world_coordinates = 0;
	moveScreen = true;
	isRunningGame = true;
	for(int j=0;j<MAX_TILES;j++) {
		tile1[j].setX(tilePositionPlacerX(j));
		tile2[j].setX(tilePositionPlacerX(j));
	}
	castle.setX(tilePositionPlacerX(26));
	for(int i=0;i<MAX_CASTLE_WALLS;i++) {
		castleWall[i].setX(i*castleWall[i].getScaledWidth()-100);
	}
	cattails.setX(tilePositionPlacerX(3));
	dudeManBro.setX(tile1[1].getX());
	dudeManBro.setY(tilePositionPlacerY(1) - dudeManBro.getScaledHeight() + heroNS::frameCompensation);
	dudeManBro.setCurrentFrame(HERO_STANDING_RIGHT_START);
	dudeManBro.setFrameDelay((float)0.2);
	dudeManBro.setDeadTimer(0);
	dudeManBro.setHealth(6);
	for(int i=0;i<MAX_SKELLINGTONS;i++) {
		enemy[1][i]->setX(tile2[i*2].getX()+2);
		enemy[1][i]->setY(tile2[i*2].getY()-enemy[1][i]->getScaledHeight()+25);
		enemy[1][i]->setFrameDelay(.02);
		enemy[1][i]->setHealth(3);
		enemy[1][i]->setActive(true);
		enemy[1][i]->setVisible(true);
	}
	for(int i=0;i<MAX_SLIMES;i++) {
		enemy[0][i]->setX(tile1[(i+3)*2].getX());
		enemy[0][i]->setY(tile1[(i+3)*2].getY()-enemy[0][i]->getScaledHeight()-1);
		enemy[0][i]->setFrames(SLIME_0,SLIME_3);
		enemy[0][i]->setCurrentFrame(SLIME_0);
		enemy[0][i]->setFrameDelay((float)0.2);
		enemy[0][i]->setHealth(1);
		enemy[0][i]->setActive(true);
		enemy[0][i]->setVisible(true);
	}
}
/*****************************************************************************************************
// Anax tile initialize
// Initialize textures for all tiles, tiles are passive enviroment elements which are placed in the world
*****************************************************************************************************/
void Anax::initializeTiles(HWND hwnd){
//Initialize Dirt Blocks
	if (!tile1Texture.initialize(graphics,TILE1_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile 1 texture"));
	if (!tile2Texture.initialize(graphics,TILE2_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile 2 texture"));

	for(int i = 0; i < MAX_TILES; i++){
		if (!tile1[i].initialize(this,189, 600, 0, &tile1Texture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile 1"));
		tile1[i].setX(tilePositionPlacerX(i));
		tile1[i].setCollisionType(entityNS::BOX);
		tile1[i].setEdge(COLLISION_TILE);
	}

	for(int i = 0;i < MAX_TILES; i++) {
		if(!tile2[i].initialize(this,189,600,0,&tile2Texture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile 2"));

	//Set position of Castle blocks
		tile2[i].setX(tilePositionPlacerX(i));
	//Set Castle Block Collision
		tile2[i].setCollisionType(entityNS::BOX);
		tile2[i].setEdge(COLLISION_TILE);
	}
	tile1[0].setY(tilePositionPlacerY(1));
	tile1[1].setY(tilePositionPlacerY(1));
	tile1[2].setY(tilePositionPlacerY(2));
	tile1[3].setY(tilePositionPlacerY(3));
	tile1[4].setY(tilePositionPlacerY(2));
	tile1[5].setY(tilePositionPlacerY(2));
	tile1[6].setY(tilePositionPlacerY(1));
	tile1[7].setY(tilePositionPlacerY(0));
	tile1[8].setY(tilePositionPlacerY(1));
	tile1[9].setY(tilePositionPlacerY(1));
	tile1[10].setY(tilePositionPlacerY(1));
	tile1[11].setY(tilePositionPlacerY(0));
	tile1[12].setY(tilePositionPlacerY(2));
	tile1[13].setY(tilePositionPlacerY(3));
	tile1[14].setY(tilePositionPlacerY(4));
	tile1[15].setY(tilePositionPlacerY(0));
	tile1[16].setY(tilePositionPlacerY(0));
	tile1[17].setY(tilePositionPlacerY(1));
	tile1[18].setY(tilePositionPlacerY(2));
	tile1[19].setY(tilePositionPlacerY(2));
	tile1[20].setY(tilePositionPlacerY(2));
	tile1[21].setY(tilePositionPlacerY(1));
	for(int i=22;i<MAX_TILES;i++) {
		tile1[i].setY(tilePositionPlacerY(0));
	}

	tile2[0].setY(tilePositionPlacerY(1));
	tile2[1].setY(tilePositionPlacerY(1));
	tile2[2].setY(tilePositionPlacerY(1));
	tile2[3].setY(tilePositionPlacerY(1));
	tile2[4].setY(tilePositionPlacerY(0));
	tile2[5].setY(tilePositionPlacerY(1));
	tile2[6].setY(tilePositionPlacerY(1));
	tile2[7].setY(tilePositionPlacerY(1));
	tile2[8].setY(tilePositionPlacerY(1));
	tile2[9].setY(tilePositionPlacerY(2));
	tile2[10].setY(tilePositionPlacerY(3));
	tile2[11].setY(tilePositionPlacerY(4));
	tile2[12].setY(tilePositionPlacerY(5));
	tile2[13].setY(tilePositionPlacerY(5));
	tile2[14].setY(tilePositionPlacerY(5));
	tile2[15].setY(tilePositionPlacerY(5));
	tile2[16].setY(tilePositionPlacerY(5));
	tile2[17].setY(tilePositionPlacerY(4));
	tile2[18].setY(tilePositionPlacerY(3));
	tile2[19].setY(tilePositionPlacerY(2));
	tile2[20].setY(tilePositionPlacerY(1));
	tile2[21].setY(tilePositionPlacerY(1));
	tile2[22].setY(tilePositionPlacerY(1));
	tile2[23].setY(tilePositionPlacerY(1));
	tile2[24].setY(tilePositionPlacerY(1));
	tile2[25].setY(tilePositionPlacerY(1));
	for(int i=26;i<MAX_TILES;i++) {
		tile2[i].setY(tilePositionPlacerY(0));
	}
//Initialize Castle
	if (!castleTexture.initialize(graphics,CASTLE_TILE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing castle tile texture"));
    if (!castle.initialize(this,527, 448, 0, &castleTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing castle tile"));
	castle.setScale((float)1.25);
	castle.setX(tilePositionPlacerX(26));
	castle.setY(tilePositionPlacerY(7)-40);

//Initialize CastleWall
	if (!castleWallTexture.initialize(graphics,CASTLE_WALL_TILE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing castleWall tile texture"));
	for(int i = 0; i < MAX_CASTLE_WALLS; i++){
		if (!castleWall[i].initialize(this,399, 448, 0, &castleWallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing castleWall tile"));
	castleWall[i].setScale((float)2);
	castleWall[i].setX(i*castleWall[i].getScaledWidth()-100 - world_coordinates);
	castleWall[i].setY(tilePositionPlacerY(7)-40);
	}
}


/*****************************************************************************************************
// Anax Initialize Entities
// Initializes all sprites with dynamic behavior
*****************************************************************************************************/
void Anax::initializeEntities(HWND hwnd){

	//Armed Hero
	 if (!heroTexture.initialize(graphics,HERO_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hero texture"));
    if (!dudeManBro.initialize(this,128, 128, 44, &heroTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing The Dude"));
	dudeManBro.setX(tile1[1].getX());
	dudeManBro.setY(tilePositionPlacerY(1) - dudeManBro.getScaledHeight() + heroNS::frameCompensation);
	dudeManBro.setCurrentFrame(HERO_STANDING_RIGHT_START);
	dudeManBro.setFrameDelay((float)0.2);
	dudeManBro.setCollisionType(entityNS::BOX);
	dudeManBro.setEdge(COLLISION_BOX_HERO);
}


/*****************************************************************************************************
// Anax initialize world
// Initializes all sprites that compose the static background and scenery
*****************************************************************************************************/
void Anax::initializeWorld(HWND hwnd){

	//coordinates system
	if(dxCoordinates->initialize(graphics, 50, true, false, "Arial") == false)
    throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
	if(dxDialog->initialize(graphics, 50, true, false, "Arial") == false)
    throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));


	//background
	if (!backgroundTexture.initialize(graphics, BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	if (!background.initialize(graphics,0,0,0,&backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));
	background.setScale(2);
	if (!dialogBoxTexture.initialize(graphics, DIALOG_BOX_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dialogBox texture"));
	if (!dialogBox.initialize(graphics,0,0,0,&dialogBoxTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dialogBox"));
	dialogBox.setX(320);
	dialogBox.setY(140);
	//cloud
	if (!cloudTexture.initialize(graphics,CLOUD_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cloud texture"));
    if (!cloud.initialize(this,320, 128, 0, &cloudTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cloud"));

	//mountains
	if (!mountainTexture.initialize(graphics,MOUNTAIN_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mountain texture"));
	for(int i=0; i<MOUNTAIN_MAX; i++){

    if (!mountain[i].initialize(this,320, 60, 0, &mountainTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mountain"));
	}
	
	for(int i=0; i<MOUNTAIN_MAX; i++){
	 if (!frontMountainsTexture.initialize(graphics,MOUNTAIN_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mountain texture"));

    if (!frontMountains[i].initialize(this,320, 60, 0, &mountainTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mountain"));
	}

	//Cattails
	if (!cattailsTexture.initialize(graphics,CATTAILS))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cattails texture"));
    if (!cattails.initialize(this,320, 128, 0, &cattailsTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cattails"));
	cattails.setScale(3.0);

	//Flowers
	if (!flowersTexture.initialize(graphics,FLOWERS_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing flowers texture"));
	for(int i = 0; i < MAX_FLOWERS; i++){
		if (!flowers[i].initialize(this,59, 16, 0, &flowersTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing flowers"));
	}
	flowers[0].setX(100);
	flowers[0].setY(100);
	for(int i = 0; i < MAX_FLOWERS; i++){
		flowers[i].setScale(2);
	}

	//Bushes
	if (!bushesTexture.initialize(graphics,BUSHES_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bushes texture"));
	for(int i = 0; i < MAX_BUSHES; i++){
		if (!bushes[i].initialize(this,64, 16, 0, &bushesTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bushes"));
	}
	bushes[0].setX(200);
	bushes[0].setY(200);
	for(int i = 0; i < MAX_BUSHES; i++){
		bushes[i].setScale(2);
	}

	//Disk Flowers
	if (!diskFlowersTexture.initialize(graphics,DISK_FLOWERS_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing disk flowers texture"));
	for(int i = 0; i < MAX_DISK_FLOWERS; i++){
		if (!diskFlowers[i].initialize(this,40, 23, 0, &diskFlowersTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing disk flowers"));
	}
	diskFlowers[0].setX(300);
	diskFlowers[0].setX(300);
	for(int i = 0; i < MAX_DISK_FLOWERS; i++){
		diskFlowers[i].setScale(2);
	}

	//Tree
	if (!treeTexture.initialize(graphics,TREE_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tree texture"));
	for(int i = 0; i < MAX_TREES; i++){
		 if (!tree[i].initialize(this,128, 200, 0, &treeTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tree"));
	}
	tree[0].setX(400);
	tree[0].setY(400);
	for(int i = 0; i < MAX_TREES; i++){
		tree[i].setScale(1);
	}
    

for(int i=0; i<MAX_TORCHES; i++){
	if (!torchTexture.initialize(graphics,TORCH_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing torch texture"));
    if (!torch[i].initialize(this,34, 36, 5, &torchTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing torch"));
	}
	for(int i=0;i<MAX_TORCHES;i++) {
		torch[i].setScale((float)2.5);
		torch[i].setFrameDelay((float)0.2);
		torch[i].setCurrentFrame(TORCH_FIRST);
		torch[i].setFrames(TORCH_FIRST,TORCH_LAST);
		torch[i].setX(i*500 - world_coordinates);
		torch[i].setY(200);
	}


	//Cave Wall
	if (!caveWallTexture.initialize(graphics,CAVE_WALL_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing caveWall texture"));
    if (!caveWall.initialize(this,1080, 378, 0, &caveWallTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing caveWall"));
	caveWall.setX(0);
	caveWall.setY(0);

	//Sword
	if (!swordTexture.initialize(graphics,SWORD_IN_STONE_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sword in stone texture"));
    if (!sword.initialize(this,128, 128, 28, &swordTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sword in stone"));
	sword.setX(300);
	sword.setY(300);
	sword.setFrameDelay((float)0.1);
	sword.setFrames(SWORD_FIRST, SWORD_LAST);
	sword.setCurrentFrame(SWORD_FIRST);

	//Fireball
	if (!magicMissileTexture.initialize(graphics,MAGICMISSILE_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing magicMissile texture"));
    if (!magicMissile.initialize(this,32, 32, 0, &magicMissileTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing magicMissile"));
	magicMissile.setX(0);
	magicMissile.setY(0);
	magicMissile.setScale(1.5);
	magicMissile.setActive(false);
	magicMissile.setEdge(COLLISION_BOX_PUCK);
	magicMissile.setCollisionType(entityNS::BOX);

	//Death Sheet
	if (!deathSheetTexture.initialize(graphics,DEATH_SHEET_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing deathSheet texture"));
    if (!deathSheet.initialize(this,1080, 768, 0, &deathSheetTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing deathSheet"));
	deathSheet.setScale(1.25);
	deathSheet.setX(0);
	deathSheet.setY(0);

//End Screen
	if (!endScreenTexture.initialize(graphics,END_SCREEN_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing endScreen texture"));
    if (!endScreen.initialize(this,1080, 768, 0, &endScreenTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing endScreen"));
	endScreen.setScale(1.25);
	endScreen.setX(0);
	endScreen.setY(0);



	
    cloud.setX(0);               
    cloud.setY(0);
	cloud.setScale(1);
	cloud2.setScale(1);
    cloud2.setX(0);                   
    cloud2.setY(-100);
	mountainSide[MOUNTAIN_MAX-1]=right;
	mountainSide[0]=0;
	mountainFront[MOUNTAIN_MAX-1]=right;
	mountainFront[0]=0;

	for(int i=0; i<MOUNTAIN_MAX; i++){
		mountain[i].setScale(5);
		mountain[i].setX(i*320*mountain[i].getScale()-320*mountain[i].getScale());             
		mountain[i].setY((float)(GAME_HEIGHT - mountain[i].getScaledHeight()));
		frontMountains[i].setScale(3);
		frontMountains[i].setX(i*320*frontMountains[i].getScale());                  
		frontMountains[i].setY((float)(GAME_HEIGHT - frontMountains[i].getScaledHeight()));
	}
}

void Anax::initializeUI(HWND hwnd){
		//Heart
	if (!heartTexture.initialize(graphics,HEART_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing heart texture"));
    if (!heart.initialize(this,32, 32, 0, &heartTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing heart"));
	heart.setScale(2);
	heart.setX(0);
	heart.setY(0);

	//Heart2
	if (!heart2Texture.initialize(graphics,HEART_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing heart2 texture"));
    if (!heart2.initialize(this,32, 32, 0, &heart2Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing heart2"));
	heart2.setScale(2);
	heart2.setX(64);
	heart2.setY(0);

	//Heart3
	if (!heart3Texture.initialize(graphics,HEART_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing heart3 texture"));
    if (!heart3.initialize(this,32, 32, 0, &heart3Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing heart3"));
	heart3.setScale(2);
	heart3.setX(128);
	heart3.setY(0);

	//Half Heart
	if (!halfHeartTexture.initialize(graphics,HALF_HEART_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing halfHeart texture"));
    if (!halfHeart.initialize(this,32, 32, 0, &halfHeartTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing halfHeart"));
	halfHeart.setScale(2);
	halfHeart.setX(0);
	halfHeart.setY(0);

	//Half Heart2
	if (!halfHeart2Texture.initialize(graphics,HALF_HEART_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing halfHeart2 texture"));
    if (!halfHeart2.initialize(this,32, 32, 0, &halfHeart2Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing halfHeart2"));
	halfHeart2.setScale(2);
	halfHeart2.setX(64);
	halfHeart2.setY(0);

	//Half Heart3
	if (!halfHeart3Texture.initialize(graphics,HALF_HEART_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing halfHeart3 texture"));
    if (!halfHeart3.initialize(this,32, 32, 0, &halfHeart3Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing halfHeart3"));
	halfHeart3.setScale(2);
	halfHeart3.setX(128);
	halfHeart3.setY(0);

	//Empty Heart
	if (!emptyHeartTexture.initialize(graphics,EMPTY_HEART_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing emptyHeart texture"));
    if (!emptyHeart.initialize(this,32, 32, 0, &emptyHeartTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing emptyHeart"));
	emptyHeart.setScale(2);
	emptyHeart.setX(0);
	emptyHeart.setY(0);

	//Empty Heart2
	if (!emptyHeart2Texture.initialize(graphics,EMPTY_HEART_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing emptyHeart2 texture"));
    if (!emptyHeart2.initialize(this,32, 32, 0, &emptyHeart2Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing emptyHeart2"));
	emptyHeart2.setScale(2);
	emptyHeart2.setX(64);
	emptyHeart2.setY(0);

	//Empty Heart3
	if (!emptyHeart3Texture.initialize(graphics,EMPTY_HEART_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing emptyHeart3 texture"));
    if (!emptyHeart3.initialize(this,32, 32, 0, &emptyHeart3Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing emptyHeart3"));
	emptyHeart3.setScale(2);
	emptyHeart3.setX(128);
	emptyHeart3.setY(0);


}


void Anax::initializeEnemies(HWND hwnd){

	for(int i = 0; i<MAX_SLIMES; i++){
		enemy[0][i]=new Slime();
	}
	for(int i = 0; i<MAX_SKELLINGTONS; i++){
		enemy[1][i]= new Skellington();
	}
	for(int i = 0; i<MAX_SLIMES; i++){
		initializeSlime(hwnd, i);
	}
	for(int i = 0; i<MAX_SKELLINGTONS; i++){
		initializeSkellington(hwnd, i);
	}
}


void Anax::initializeSkellington(HWND hwnd, int i){
//Skellington
	if (!skellingtonTexture.initialize(graphics,SKELLINGTON_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing skellington texture"));
    if (!enemy[1][i]->initialize(this,128, 128, 6, &skellingtonTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing skellington"));
	enemy[1][i]->setX(tile2[i*2].getX()+2);
	enemy[1][i]->setY(tile2[i*2].getY()-enemy[1][i]->getScaledHeight()+25);
	enemy[1][i]->setCollisionType(entityNS::BOX);
	enemy[1][i]->setEdge(COLLISION_BOX_SKELLINGTON);
	enemy[1][i]->setFrameDelay(.02);
}

void Anax::initializeSlime(HWND hwnd, int i){
//Slime
	if (!slimeTexture.initialize(graphics,SLIMES_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing slime texture"));
    if (!enemy[0][i]->initialize(this,62, 62, 4, &slimeTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing slime"));
	enemy[0][i]->setX(tile1[(i+3)*2].getX());
	enemy[0][i]->setY(tile1[(i+3)*2].getY()-enemy[0][i]->getScaledHeight()-1);
	enemy[0][i]->setFrames(SLIME_0,SLIME_3);
	enemy[0][i]->setCurrentFrame(SLIME_0);
	enemy[0][i]->setFrameDelay((float)0.2);
	enemy[0][i]->setCollisionType(entityNS::BOX);
	enemy[0][i]->setEdge(COLLISION_BOX_SLIME);
}
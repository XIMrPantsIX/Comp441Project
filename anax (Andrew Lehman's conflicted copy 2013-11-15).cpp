#include "Anax.h"
/*****************************************************************************************************
// Anax Constructor & Deconstructor
//	
*****************************************************************************************************/
Anax::Anax(){
	dxCoordinates = new TextDX();
	dxDialog = new TextDX();
}
Anax::~Anax(){releaseAll();}

/*****************************************************************************************************
// Class initialize function
// Initializes all sprites 
*****************************************************************************************************/
void Anax::initialize(HWND hwnd){
		Game::initialize(hwnd);
		world_coordinates = 0;
		moveScreen = false;
		isDialogOn = true;
		dialogIn = "Welcome to WomboCom!\n Press Enter to Continue!";
		isRunningGame = false;
		initializeWorld(hwnd);
		initializeTiles(hwnd);
		initializeEntities(hwnd);
}

/*****************************************************************************************************
// Anax Update function
// Calls update functions for all sprites and members, called every cycle of game loop
*****************************************************************************************************/
void Anax::update(){ 
	if(input->isKeyDown(VK_ESCAPE)){
		exit(0);
	}
	updateWorld(frameTime);
	updateTiles(frameTime);
	handleInput();	
	displayCoordinates();
	dialogChecker();
	if(isDialogOn){}
	if(isRunningGame){
		updateEntities();
	}
}

/*****************************************************************************************************
// Anax Collisions
// Handles all collision detection, called every cycle of game loop
*****************************************************************************************************/
void Anax::collisions(){
	entityTileCollisions();
	}



/*****************************************************************************************************
// Anax Input Handler
// Checks all input devices, called every cycle of game loop
*****************************************************************************************************/
void Anax::handleInput(){
	if(input->isKeyDown(VK_CONTROL)&&input->isKeyDown(0x43)) {
		PostQuitMessage(0);
		return;
	}
	if(isDialogOn){
		if(input->isKeyDown(VK_RETURN)){
			isDialogOn = false;
			isRunningGame = true;
			moveScreen = true;
		}
	}
	/*check to see if World can move again after collision*/
	else if(isRunningGame){	
	if(input->isKeyDown(VK_LEFT)&&dudeManBro.isFacingRight()&&moveScreen==false)
		moveScreen = true;
	if(input->isKeyDown(VK_RIGHT)&&dudeManBro.isFacingLeft()&&moveScreen==false)
		moveScreen = true;

	if(input->isKeyDown(VK_RIGHT)){
		if(moveScreen){
			world_coordinates += 175*frameTime;
			slime.setX(slime.getX()-175*frameTime);
		}
		dudeManBro.walk(right);
	}
	if(input->isKeyDown(VK_LEFT)){
		if(moveScreen){
			world_coordinates -= 175*frameTime;
			slime.setX(slime.getX()+175*frameTime);
		}
		dudeManBro.walk(left);
	}
	if(!input->isKeyDown(VK_LEFT)&&!input->isKeyDown(VK_RIGHT)&&!input->isKeyDown(VK_UP)&&!input->isKeyDown(VK_SPACE)){
		dudeManBro.walk(middle);
	}
	if(input->isKeyDown(VK_SPACE)&&dudeManBro.isFacingLeft()&&dudeManBro.canJump()){
		dudeManBro.jump(left);
	}
	if(input->isKeyDown(VK_SPACE)&&dudeManBro.isFacingRight()&&dudeManBro.canJump()){
		dudeManBro.jump(right);
	}
	}
}
	

/*****************************************************************************************************
// Anax render function
// Draws all sprites to screen, called every cycle of game loop
*****************************************************************************************************/
void Anax::render(){
	graphics->spriteBegin();
	background.draw();
	for(int i=0; i<MOUNTAIN_MAX; i++)
		mountain[i].draw(graphicsNS::OLIVE);
	for(int i=0; i<MOUNTAIN_MAX; i++)
		frontMountains[i].draw();
	cloud.draw();
	cloud2.draw();
	for(int i=0; i<MAX_TILES; i++){
		tile1[i].draw(graphicsNS::OLIVE);
	}
	cattails.draw();
	castle.draw();
	dudeManBro.draw();
	drawHealth();
	slime.draw();
	fireball.draw();
	//caveWall.draw();
	
	dxCoordinates->print(in,GAME_WIDTH - 1000, 0);


	if(isDialogOn){
		in = getDialog();
		dialogBox.draw();
		dxDialog->print(in, 400, 150);
	}
	graphics->spriteEnd();
}

/*****************************************************************************************************
// Anax Initialize Entities
// Initializes all sprites with dynamic behavior
*****************************************************************************************************/
void Anax::initializeEntities(HWND hwnd){

	//Armed Hero
	 if (!heroTexture.initialize(graphics,HERO_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hero texture"));
    if (!dudeManBro.initialize(this,128, 128, 27, &heroTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing The Dude"));
	dudeManBro.setX(tile1[1].getX());
	dudeManBro.setY(tilePositionPlacerY(1) - dudeManBro.getScaledHeight() + heroNS::frameCompensation);
	dudeManBro.setCurrentFrame(HERO_STANDING_RIGHT_START);
	dudeManBro.setFrameDelay(.2);
	dudeManBro.setCollisionType(entityNS::BOX);
	dudeManBro.setEdge(COLLISION_BOX_HERO);
	//Unarmed Hero
	if (!unarmedHeroTexture.initialize(graphics,NO_SWORD_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing unarmedHero texture"));
    if (!unarmedHero.initialize(this,128, 128, 27, &unarmedHeroTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing unarmed Hero"));
	unarmedHero.setX(tile1[1].getX());
	unarmedHero.setY(tilePositionPlacerY(1) - dudeManBro.getScaledHeight() + heroNS::frameCompensation);
	unarmedHero.setCurrentFrame(UNARMED_STANDING_RIGHT_START);
	unarmedHero.setFrameDelay(.2);
	unarmedHero.setCollisionType(entityNS::BOX);
	unarmedHero.setEdge(COLLISION_BOX_HERO);
}

/*****************************************************************************************************
// Anax Update Entities
// Calls update function for all entity classes
*****************************************************************************************************/
void Anax::updateEntities(){
	dudeManBro.update(frameTime);
	slime.update(frameTime);
}
	

void Anax::entityTileCollisions(){
collisionVector.x = 0;
	collisionVector.y = 0;
	for(int i=0; i< MAX_TILES; i++){
		if(dudeManBro.getX()+40>=tile1[i].getX()&&dudeManBro.getX()+dudeManBro.getScaledWidth()-40<=tile1[i].getX()+tile1[i].getScaledWidth())
			if(tile1[i].getY()>dudeManBro.getY()+dudeManBro.getScaledHeight()&&!(dudeManBro.isJumpingLeft()||dudeManBro.isJumpingRight())){
				dudeManBro.fall();
			}
		if(dudeManBro.collidesWith(tile1[i],collisionVector)){
 			if(abs(collisionVector.y)>=abs(collisionVector.x)){
				dudeManBro.land();
				dudeManBro.setY(tile1[i].getY()-dudeManBro.getScaledHeight()+heroNS::frameCompensation);
			}
			if(abs(collisionVector.y)<=abs(collisionVector.x)){
				if(collisionVector.x<0){
					dudeManBro.setX(dudeManBro.getX()+4);
					dudeManBro.walk(middle);
					moveScreen = false;
				}
				if(collisionVector.x>0){
					dudeManBro.setX(dudeManBro.getX()-4);	
					dudeManBro.walk(middle);
					moveScreen = false;
				}
				moveScreen = false;
			}
		}
		}
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
	for(int i=0; i<MOUNTAIN_MAX; i++){
	 if (!mountainTexture.initialize(graphics,MOUNTAIN_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mountain texture"));

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
    if (!flowers.initialize(this,59, 16, 0, &flowersTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing flowers"));

	//Bushes
	if (!bushesTexture.initialize(graphics,BUSHES_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bushes texture"));
    if (!bushes.initialize(this,64, 16, 0, &bushesTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bushes"));

	//Disk Flowers
	if (!diskFlowersTexture.initialize(graphics,DISK_FLOWERS_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing disk flowers texture"));
    if (!diskFlowers.initialize(this,40, 23, 0, &diskFlowersTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing disk flowers"));

	//Tree
	if (!treeTexture.initialize(graphics,TREE_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tree texture"));
    if (!tree.initialize(this,128, 200, 0, &treeTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tree"));

	//Torch
	if (!torchTexture.initialize(graphics,TORCH_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing torch texture"));
    if (!torch.initialize(this,171, 36, 0, &torchTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing torch"));

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

	//Slime
	if (!slimeTexture.initialize(graphics,SLIMES_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing slime texture"));
    if (!slime.initialize(this,62, 62, 0, &slimeTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing slime"));
	slime.setX(500);
	slime.setY(500);
	slime.setCurrentFrame(SLIME_1);
	slime.setFrameDelay(.2);
	slime.setCollisionType(entityNS::BOX);
	slime.setEdge(COLLISION_BOX_SLIME);

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
    if (!sword.initialize(this,128, 128, 0, &swordTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sword in stone"));
	sword.setX(0);
	sword.setY(0);

	//Skellington
	if (!skellingtonTexture.initialize(graphics,SKELLINGTON_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing skellington texture"));
    if (!skellington.initialize(this,128, 128, 0, &skellingtonTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing skellington"));
	skellington.setX(0);
	skellington.setY(0);

	//Fireball
	if (!magicMissileTexture.initialize(graphics,FIREBALL_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing magicMissile texture"));
    if (!magicMissile.initialize(this,32, 32, 0, &magicMissileTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing magicMissile"));
	magicMissile.setX(0);
	magicMissile.setY(0);


	
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
		mountain[i].setY(GAME_HEIGHT - mountain[i].getScaledHeight());
		frontMountains[i].setScale(3);
		frontMountains[i].setX(i*320*frontMountains[i].getScale());                  
		frontMountains[i].setY(GAME_HEIGHT - frontMountains[i].getScaledHeight());
	}
}

/*****************************************************************************************************
// Anax update world
// Updates all sprites that compose the static background and scenery
*****************************************************************************************************/
void Anax::updateWorld(float frameTime){
		cloud.setX(cloud.getX()+1);
	if(cloud.getX()>GAME_WIDTH) cloud.setX(0-cloud.getWidth()*cloud.getScale());

	//Mountain move code	
	for(int i=0; i<MOUNTAIN_MAX; i++){
		if(input->isKeyDown(VK_LEFT)&&moveScreen){
		mountain[i].setX(mountain[i].getX()+.25);
		if(mountain[i].getX()>=GAME_WIDTH&&mountainSide[i]==right){
			mountain[i].setX(mountain[getMountainSide(left)].getX()-mountain[i].getScaledWidth()+1);
			mountainSide[getMountainSide(left)] = middle;
			mountainSide[i] = left;
			mountainSide[nextPeak(i, right)] = right;
		}
		}
		if(input->isKeyDown(VK_RIGHT)&&moveScreen){
		mountain[i].setX(mountain[i].getX()-.25);
		if(mountain[i].getX()+mountain[i].getScaledWidth()<=0&&mountainSide[i]==left){
			mountain[i].setX(mountain[getMountainSide(right)].getX()+mountain[i].getScaledWidth()-1);
			mountainSide[getMountainSide(right)] = middle;
			mountainSide[i] = right;
			mountainSide[nextPeak(i, left)] = left;
		}
		}
	}
	
	//Mountainfront move code
		for(int j=0; j<MOUNTAIN_MAX; j++){
		if(input->isKeyDown(VK_LEFT)&&moveScreen){
			frontMountains[j].setX(frontMountains[j].getX()+.55);
			if(frontMountains[j].getX()>=GAME_WIDTH&&mountainFront[j]==right){
				frontMountains[j].setX(frontMountains[getMountainFront(left)].getX()-frontMountains[j].getScaledWidth()+1);
				mountainFront[getMountainFront(left)] = middle;
				mountainFront[j] = left;
				mountainFront[nextPeak(j, right)] = right;
			}
		}
		if(input->isKeyDown(VK_RIGHT)&&moveScreen){
			frontMountains[j].setX(frontMountains[j].getX()-.55);
		if(frontMountains[j].getX()+frontMountains[j].getScaledWidth()<=0&&mountainFront[j]==left){
			frontMountains[j].setX(frontMountains[getMountainFront(right)].getX()+frontMountains[j].getScaledWidth()-1);
			mountainFront[getMountainFront(right)] = middle;
			mountainFront[j] = right;
			mountainFront[nextPeak(j, left)] = left;
		}
		}
		}

}

/*****************************************************************************************************
// Anax coordinate display
// output display to font.
*****************************************************************************************************/
void Anax::displayCoordinates(){
	std::stringstream s;
	s << world_coordinates;
	in.assign(s.str());

}
/*****************************************************************************************************
// Anax get mountain functions
// returns ith side of mountains 
*****************************************************************************************************/
int Anax::getMountainSide(int side){
	for(int i=0; i<MOUNTAIN_MAX; i++){
		if(mountainSide[i]==side) return i;
	}
}
int Anax::getMountainFront(int side){
	for(int i=0; i<MOUNTAIN_MAX; i++){
		if(mountainFront[i]==side) return i;
	}
}

/*****************************************************************************************************
// Anax nextPeak function
// 
*****************************************************************************************************/
int Anax::nextPeak(int i, int side){
	//note: Pass in the i that just converted over to the next side. int "side" will be left for new left and right for new right;
	//since the array goes in order left to right, we just need to worry about where the 0/MAX line is.
	if(side==right){
		i--;
		if(i<0) i = MOUNTAIN_MAX - 1;
	}
	if(side==left){
		i++;
		if(i==MOUNTAIN_MAX) i = 0;
	}
	return i;
}


/*****************************************************************************************************
// Anax tile initialize
// Initialize textures for all tiles, tiles are passive enviroment elements which are placed in the world
*****************************************************************************************************/
void Anax::initializeTiles(HWND hwnd){
//Initialize Dirt Blocks
	if (!tile1Texture.initialize(graphics,TILE1_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile 1 texture"));
	for(int i = 0; i < MAX_TILES; i++){
    if (!tile1[i].initialize(this,189, 189, 0, &tile1Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile 1"));
//Set position of Dirt blocks
	tile1[i].setX(tilePositionPlacerX(i));
	tile1[i].setY(tilePositionPlacerY(i));
//Set Dirt Block Collision
	tile1[i].setCollisionType(entityNS::BOX);
	tile1[i].setEdge(COLLISION_TILE);
  }
//Initialize Stone Blocks
	if (!stoneTileTexture.initialize(graphics,STONE_TILE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing stone tile texture"));
	for(int i = 0; i < 10; i++){
    if (!stoneTile[i].initialize(this,189, 189, 0, &tile1Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing stone tile"));
	}
//Initialize Castle
	if (!castleTexture.initialize(graphics,CASTLE_TILE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing castle tile texture"));
    if (!castle.initialize(this,567, 567, 0, &castleTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing castle tile"));
	castle.setScale(1);
	castle.setX(650);
	castle.setY(GAME_HEIGHT - (castle.getScaledHeight() + 75));
//Set Position of Cattails
	cattails.setScale(1);
	cattails.setX(tilePositionPlacerX(3));
	cattails.setY(tilePositionPlacerY(3)-cattails.getHeight()*cattails.getScale());
}

/*****************************************************************************************************
// Anax update tiles
// All tile sprites are updated
*****************************************************************************************************/
void Anax::updateTiles(float frameTime){
	for(int i=0; i<MAX_TILES; i++){
		tile1[i].setX(tilePositionPlacerX(i));
	}
	cattails.setX(tilePositionPlacerX(3));
};

/*****************************************************************************************************
// Anax tile position (x,y) placers
// Functions return values which coorespond to world coordinates
*****************************************************************************************************/
float Anax::tilePositionPlacerX(int i){
	switch(i){
		case 0:
		case 1:
		case 2:
		case 3:
		case 4: 
		case 5:
		case 6: 
		case 7:
		case 8:
		case 9:
		default: return tile1[i].getScaledWidth() * i - world_coordinates;
	}
}
float Anax::tilePositionPlacerY(int i){
	switch(i){
	case 0:
		return GAME_HEIGHT - tile1[i].getScaledHeight();
	case 1:
		return GAME_HEIGHT - tile1[i].getScaledHeight() - 50;
	case 2:
		return GAME_HEIGHT - tile1[i].getScaledHeight() - 100;
	case 3:
		return GAME_HEIGHT - tile1[i].getScaledHeight() - 150;
	case 4:
		return GAME_HEIGHT - tile1[i].getScaledHeight() - 200;
	case 5:
		return GAME_HEIGHT - tile1[i].getScaledHeight() - 250;
	case 6:
		return GAME_HEIGHT - tile1[i].getScaledHeight() + 300;
	case 7: 
		return GAME_HEIGHT - tile1[i].getScaledHeight() - 189/2 - world_coordinates;
	case 8:
		return GAME_HEIGHT - tile1[i].getScaledHeight() + 189/2 - world_coordinates;
	case 9: 
		return GAME_HEIGHT - tile1[i].getScaledHeight() + 189/2 - world_coordinates;
	case 10:
		return GAME_HEIGHT - tile1[i].getScaledHeight() - 189/20 - world_coordinates;
	case 11:
		return GAME_HEIGHT - tile1[i].getScaledHeight() - 189/5 - world_coordinates;
	case 12:
		return GAME_HEIGHT - tile1[i].getScaledHeight() - 189/2 - world_coordinates;
	case 13:
		return GAME_HEIGHT - tile1[i].getScaledHeight() - 189/5 - world_coordinates;
		return GAME_HEIGHT - castle.getScaledHeight() - world_coordinates;
	case 14:
		return GAME_HEIGHT - tile1[i].getScaledHeight() - 189/20 - world_coordinates;
	default: return GAME_HEIGHT - tile1[i].getScaledHeight() + 189/2 - world_coordinates;
	}
}

/*****************************************************************************************************
// Anax render helpers
// Simplifies render function by adding functions for draw sprite switches 
*****************************************************************************************************/
void Anax::drawHealth()
{
	switch(dudeManBro.getHealth())
	{
	case 0:
		emptyHeart.draw();
		emptyHeart2.draw();
		emptyHeart3.draw();
		break;
	case 1:
		halfHeart.draw();
		emptyHeart2.draw();
		emptyHeart3.draw();
		break;
	case 2:
		heart.draw();
		emptyHeart2.draw();
		emptyHeart3.draw();
		break;
	case 3:
		heart.draw();
		halfHeart2.draw();
		emptyHeart3.draw();
		break;
	case 4:
		heart.draw();
		heart2.draw();
		emptyHeart3.draw();
		break;
	case 5:
		heart.draw();
		heart2.draw();
		halfHeart3.draw();
		break;
	case 6:
		heart.draw();
		heart2.draw();
		heart3.draw();
		break;
	default:
		emptyHeart.draw();
		halfHeart2.draw();
		heart3.draw();
	}
}

/*****************************************************************************************************
// Anax texture managers
// Releases all memory reserved for sprites upon exit
*****************************************************************************************************/
void Anax::releaseAll(){
	dxCoordinates->onLostDevice();
	dxDialog->onLostDevice();
	cloudTexture.onLostDevice();
	mountainTexture.onLostDevice();
	tile1Texture.onLostDevice();
	frontMountainsTexture.onLostDevice();
	cattailsTexture.onLostDevice();
	stoneTileTexture.onLostDevice();
	castleWallTexture.onLostDevice();
	castleTexture.onLostDevice();
	flowersTexture.onLostDevice();
	diskFlowersTexture.onLostDevice();
	bushesTexture.onLostDevice();
	torchTexture.onLostDevice();
	castleTexture.onLostDevice();
	castleWallTexture.onLostDevice();
	heartTexture.onLostDevice();
	halfHeartTexture.onLostDevice();
	emptyHeartTexture.onLostDevice();
	heart2Texture.onLostDevice();
	halfHeart2Texture.onLostDevice();
	emptyHeart2Texture.onLostDevice();
	heart3Texture.onLostDevice();
	halfHeart3Texture.onLostDevice();
	emptyHeart3Texture.onLostDevice();
	slimeTexture.onLostDevice();
	caveWallTexture.onLostDevice();
	magicMissileTexture.onLostDevice();
}
void Anax::resetAll(){
	dxCoordinates->onResetDevice();
	dxDialog->onResetDevice();
	cloudTexture.onResetDevice();
	mountainTexture.onResetDevice();
	frontMountainsTexture.onResetDevice();
	tile1Texture.onResetDevice();
	cattailsTexture.onResetDevice();
	stoneTileTexture.onResetDevice();
	castleWallTexture.onResetDevice();
	castleTexture.onResetDevice();
	flowersTexture.onResetDevice();
	diskFlowersTexture.onResetDevice();
	bushesTexture.onResetDevice();
	torchTexture.onResetDevice();
	castleTexture.onResetDevice();
	castleWallTexture.onResetDevice();
	heartTexture.onResetDevice();
	halfHeartTexture.onResetDevice();
	slimeTexture.onResetDevice();
	caveWallTexture.onResetDevice();
	magicMissileTexture.onResetDevice();
}


void Anax::dialogChecker(){
	displayCoordinates();
	switch(static_cast<int>(world_coordinates)){

	case 400:
		turnDialogOn();
		dialogIn = "...congrats. You totally passed \n a cattail. \n Press Enter to Continue";
		break;
	case 2111:
		turnDialogOn();
		dialogIn = "You stand on a Mountain.\n The peace is glorious. \n Now Let's go fight zombies. \n Press Enter to Continue";
		break;
	}
}

void Anax::turnDialogOn(){
		isDialogOn = true;
		isRunningGame = false;
		moveScreen = false;
		dudeManBro.walk(middle);
		dudeManBro.setX(dudeManBro.getX()+1);
		world_coordinates+=1;

}
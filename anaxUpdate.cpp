#include "Anax.h"

/*****************************************************************************************************
// Anax Update function
// Calls update functions for all sprites and members, called every cycle of game loop
*****************************************************************************************************/
void Anax::update(){ 
	if(input->isKeyDown(VK_ESCAPE)){
		exit(0);
	}
	switch(gameState)
	{
	case 0:
		audio->playCue(LVL1BG);
		updateWorld1(frameTime);
		mainMenu->update(gameState);
		if(mainMenu->getEggsOn()) {
			if (!heroTexture.initialize(graphics,MC_HERO_IMAGE))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hero texture"));
			if (!dudeManBro.initialize(this,128, 128, 44, &heroTexture))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing The Dude"));
			if (!magicMissileTexture.initialize(graphics,FIREBALL_IMAGE))
				 throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing magicMissile texture"));
			if (!magicMissile.initialize(this,32, 32, 0, &magicMissileTexture))
				 throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing magicMissile"));
			cheatsOn = true;
		}
		break;
	case 1:
		updateWorld1(frameTime);
		updateTiles(frameTime);
		handleInput();	
		displayCoordinates();
		dialogChecker();
		if(isDialogOn){}
		if(isRunningGame){
			updateEntities();
		}
		break;
	case 2:
		audio->stopCue(LVL1BG);
		audio->playCue(LVL2BG);
		updateWorld2(frameTime);
		updateTiles(frameTime);
		handleInput();	
		displayCoordinates();
		dialogChecker();
		if(isDialogOn){}
		if(isRunningGame){
			updateEntities();
		}
		break;
	default:

		break;
	}
	if(world_coordinates>4200&&gameState!=2) endOfLevel = true;

}

/*****************************************************************************************************
// Anax update world
// Updates all sprites that compose the static background and scenery
*****************************************************************************************************/
void Anax::updateWorld1(float frameTime){
	for(int i=0; i<MAX_TILES; i++){
		tile1[i].setActive(true);
		tile2[i].setActive(false);
	}
	for(int i=0; i<MAX_SKELLINGTONS; i++){
		enemy[1][i]->setActive(false);
	}
	for(int i=0; i<MAX_SLIMES; i++){
		enemy[0][i]->setActive(true);
	}
	cloud.setX(cloud.getX()+1);
	if(cloud.getX()>GAME_WIDTH) cloud.setX(0-cloud.getWidth()*cloud.getScale());

	//Castle Update
	if(input->isKeyDown(0x44)&&(dudeManBro.getX()>=GAME_WIDTH/4)) {
		if(!endOfLevel) {
			castle.setX(tile1[0].getScaledWidth() * 26 - world_coordinates);
		}
	}

	//Mountain move code	
	for(int i=0; i<MOUNTAIN_MAX; i++){
		if(input->isKeyDown(0x44)&&(dudeManBro.getX()>=GAME_WIDTH/4)){
			if(!endOfLevel) {
				mountain[i].setX(mountain[i].getX()-.25);
				if(mountain[i].getX()+mountain[i].getScaledWidth()<=0&&mountainSide[i]==left){
					mountain[i].setX(mountain[getMountainSide(right)].getX()+mountain[i].getScaledWidth()-1);
					mountainSide[getMountainSide(right)] = middle;
					mountainSide[i] = right;
					mountainSide[nextPeak(i, left)] = left;
				}
			}
		}
	}
	
	//Mountainfront move code
	for(int j=0; j<MOUNTAIN_MAX; j++){
		if(input->isKeyDown(0x44)&&(dudeManBro.getX()>=GAME_WIDTH/4)){
			if(!endOfLevel) {
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

}

void Anax::updateWorld2(float frameTime) {
	for(int i=0; i<MAX_TILES; i++){
		tile1[i].setActive(false);
		tile2[i].setActive(true);
	}
	for(int i=0; i<MAX_SKELLINGTONS; i++){
		enemy[1][i]->setActive(true);
	}
	for(int i=0; i<MAX_SLIMES; i++){
		enemy[0][i]->setActive(false);
	}
	for(int i=0;i<MAX_TORCHES;i++) {
		torch[i].update(frameTime);
	}
//Torches X Update

	if(input->isKeyDown(0x44)&&(dudeManBro.getX()>=GAME_WIDTH/4)){
		for(int i = 0; i < MAX_TORCHES; i++){
			torch[i].setX(i*500 - world_coordinates);
			torch[i].setY(200);
		}
		for(int i = 0; i < 100; i++){
			castleWall[i].setX(i*castleWall[i].getScaledWidth()-100 - world_coordinates);
			castleWall[i].setY(tilePositionPlacerY(7)-40);
		}
	}
}
/*****************************************************************************************************
// Anax update tiles
// All tile sprites are updated
*****************************************************************************************************/
void Anax::updateTiles(float frameTime){
	if(!endOfLevel) {
		for(int i=0; i<MAX_TILES; i++){
			tile1[i].setX(tilePositionPlacerX(i));
			tile2[i].setX(tilePositionPlacerX(i));
		}
	}
}

/*****************************************************************************************************
// Anax Update Entities
// Calls update function for all entity classes
*****************************************************************************************************/
void Anax::updateEntities(){
	dudeManBro.update(frameTime,magicMissile);
	dudeManBro.updateHit(frameTime);
	for(int i = 0; i<MAX_SLIMES; i++){
		enemy[0][i]->update(frameTime);
		enemy[0][i]->ai(frameTime, dudeManBro);
	}
	for(int i = 0; i<MAX_SKELLINGTONS; i++){
		enemy[1][i]->update(frameTime);
		enemy[1][i]->ai(frameTime, dudeManBro);
	}
	if(dudeManBro.getHealth() == 0){
		int timer = dudeManBro.setDead(true);
		if(timer >= 255){
			resetGameState(gameState);
			dudeManBro.setHealth(6);
		}
	}
	if(dudeManBro.getX()>GAME_WIDTH*0.6) {
		if(gameState==2) {
			//To be continued
			gameState = 0;
			//while(!input->anyKeyPressed())
			resetGameState(gameState);
			return;
		}
		gameState = 2;
		resetGameState(gameState);
	}
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
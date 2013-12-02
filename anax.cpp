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
	else if(isRunningGame) {	
		if(input->isKeyDown(0x41)&&dudeManBro.isFacingRight()&&moveScreen==false)
			moveScreen = true;
		if(input->isKeyDown(0x44)&&dudeManBro.isFacingLeft()&&moveScreen==false)
			moveScreen = true;
	
		if(input->isKeyDown(0x44)){
			if(moveScreen){
				if(!endOfLevel) {
					if(dudeManBro.getX()>=GAME_WIDTH/4){
						world_coordinates += 175*frameTime;
						dudeManBro.walk(rightSpecial);
						for(int i=0; i<MAX_SLIMES; i++){
							enemy[0][i]->setX(enemy[0][i]->getX()-175*frameTime);
						}
						for(int i=1; i<MAX_SKELLINGTONS; i++){
							enemy[1][i]->setX(enemy[1][i]->getX()-175*frameTime);
						}
					}
					else dudeManBro.walk(right);
					//for(int i=0; i<MAX_SLIMES; i++){
					//	enemy[0][i]->setX(enemy[0][i]->getX()-175*frameTime);
					//}
				}
				else {
					dudeManBro.setX(dudeManBro.getX()+175*frameTime);
					dudeManBro.walk(right);
				}
			}
		
		}
		if(input->isKeyDown(0x41)){
		dudeManBro.walk(left);
	}
	if(!input->isKeyDown(0x41)&&!input->isKeyDown(0x44)&&!input->isKeyDown(0x57)){
		dudeManBro.walk(middle);
	}
	if(input->isKeyDown(0x57)&&dudeManBro.isFacingLeft()&&dudeManBro.canJump()){
		dudeManBro.jump(left);

	}
	if(input->isKeyDown(0x57)&&dudeManBro.isFacingRight()&&dudeManBro.canJump()){
		dudeManBro.jump(right);
	}
	if(input->isKeyDown(VK_SPACE)&&dudeManBro.canAttack()){
		audio->playCue(WHOOSH);
		if(dudeManBro.isFacingRight())
			dudeManBro.attack(right,magicMissile);
		if(dudeManBro.isFacingLeft())
			dudeManBro.attack(left,magicMissile);
		}
	}
}
/*****************************************************************************************************
// Anax render function
// Draws all sprites to screen, called every cycle of game loop
*****************************************************************************************************/
void Anax::render(){
	graphics->spriteBegin();
	switch(gameState)
	{
	case 0:
		for(int i=0; i<MOUNTAIN_MAX; i++)
			mountain[i].draw(graphicsNS::OLIVE);
		for(int i=0; i<MOUNTAIN_MAX; i++)
			frontMountains[i].draw();
		cloud.setScale(4);
		cloud2.setScale(4);
		cloud.draw();
		cloud2.draw();
		
		mainMenu->update(gameState);

		mainMenu->displayMenu();
		break;
	case 1:
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
		if(dudeManBro.getIsHit()){
			dudeManBro.draw(graphicsNS::RED);
		}
		else{
			dudeManBro.draw();
		}
		magicMissile.draw();
		for(int i=0; i<MAX_SLIMES; i++){
			enemy[0][i]->draw();
		}
		castle.draw();
		drawHealth();

		if(isDialogOn){
			in = getDialog();
			dialogBox.draw();
			dxDialog->print(in, 400, 150);
		}
		
		break;
	case 2:
		if(world_coordinates>4700){
			endScreen.draw();
			if(input->anyKeyPressed()) {
				gameState=0;
				resetGameState(gameState);
			}
			break;
		}
		background.draw();
		for(int i = 0; i < MAX_CASTLE_WALLS; i++){		
			castleWall[i].draw();
		}
		for(int i=0; i<MAX_TILES; i++){
			tile2[i].draw();
		}
		
		magicMissile.draw();
		for(int i=0; i<MAX_TORCHES; i++){
			torch[i].draw();
		}
		for(int i=0; i<MAX_SKELLINGTONS; i++){
			if(enemy[1][i]->getIsHit()){
				enemy[1][i]->draw(graphicsNS::RED);
			}
			else{
				enemy[1][i]->draw();
			}
		}
		
		if(dudeManBro.getIsHit()){
			dudeManBro.draw(graphicsNS::RED);
		}
		else{
			dudeManBro.draw();
		}
		drawHealth();
		
		break;
	default:

		break;
	}
	deathSheet.draw(SETCOLOR_ARGB(dudeManBro.getDeadTimer(),255,255,255));
	//dxCoordinates->print(in,GAME_WIDTH - 1000, 0);
	graphics->spriteEnd();
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
	tile2Texture.onLostDevice();
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
	deathSheetTexture.onLostDevice();
	endScreenTexture.onLostDevice();
}
void Anax::resetAll(){
	dxCoordinates->onResetDevice();
	dxDialog->onResetDevice();
	cloudTexture.onResetDevice();
	mountainTexture.onResetDevice();
	frontMountainsTexture.onResetDevice();
	tile1Texture.onResetDevice();
	cattailsTexture.onResetDevice();
	tile2Texture.onResetDevice();
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
	deathSheetTexture.onResetDevice();
	endScreenTexture.onResetDevice();
}

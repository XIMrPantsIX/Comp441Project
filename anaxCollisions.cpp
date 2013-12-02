#include "Anax.h"

/*****************************************************************************************************
// Anax Collisions
// Handles all collision detection, called every cycle of game loop
*****************************************************************************************************/
void Anax::collisions(){
	entityTileCollisions();
	entityEntityCollisions();
	}


/*****************************************************************************************************
// Anax Entity Collisions
// CHandles collisions with tiles and entities
*****************************************************************************************************/
void Anax::entityTileCollisions(){
	collisionVector.x = 0;
	collisionVector.y = 0;
	for(int i=0; i< MAX_TILES; i++){

//fall code
switch(gameState){
case 1:
		if(dudeManBro.getX()+40>=tile1[i].getX()&&dudeManBro.getX()+dudeManBro.getScaledWidth()-40<=tile1[i].getX()+tile1[i].getScaledWidth())
			if(tile1[i].getY()>dudeManBro.getY()+dudeManBro.getScaledHeight()&&(!dudeManBro.isJumpingLeft()&&!dudeManBro.isJumpingRight())){
				dudeManBro.fall();
			}
		if(dudeManBro.collidesWith(tile1[i],collisionVector)){
 			if(dudeManBro.isLanding()){
				dudeManBro.land();
				dudeManBro.setY(tile1[i].getY()-dudeManBro.getScaledHeight()+heroNS::frameCompensation);
				return;
			}
			if(!dudeManBro.isLanding()){
				if(collisionVector.x<0){
					collisionVector.y = 0;
					dudeManBro.bounce(collisionVector,tile1[i]);
					dudeManBro.walk(middle);
					moveScreen = false;
				}
				if(collisionVector.x>0){
					collisionVector.y = 0;
					dudeManBro.bounce(collisionVector,tile1[i]);
					dudeManBro.walk(middle);
					moveScreen = false;
				}
		  if(!dudeManBro.collidesWith(tile1[i],collisionVector)){	
			  moveScreen = true;
		  }
			}
		}
for(int j=0; j<MAX_SLIMES; j++){
	collisionVector.x = 0;
	collisionVector.y = 0;
if(enemy[0][j]->getX()+40>=tile1[i].getX()&&enemy[0][j]->getX()+enemy[0][j]->getScaledWidth()-40<=tile1[i].getX()+tile1[i].getScaledWidth())
			if(tile1[i].getY()>enemy[0][j]->getY()+enemy[0][j]->getScaledHeight()){
				enemy[0][j]->fall();
			}
		if(enemy[0][j]->collidesWith(tile1[i],collisionVector)){
 			if(enemy[0][j]->isLanding()){
				enemy[0][j]->land();
				enemy[0][j]->setY(tile1[i].getY()-enemy[0][j]->getScaledHeight()-6);
			}
			if(!enemy[0][j]->isLanding()){
				if(collisionVector.x<0){
					enemy[0][j]->setX(enemy[0][j]->getX()-2);
					enemy[0][j]->setY(tile1[i].getY()-enemy[0][j]->getScaledHeight()-6);
					enemy[0][j]->bounce(collisionVector,tile1[i]);
				}
				if(collisionVector.x>0){
					enemy[0][j]->setX(enemy[0][j]->getX()+2);
					enemy[0][j]->setY(tile1[i].getY()-enemy[0][j]->getScaledHeight()-6);
					enemy[0][j]->bounce(collisionVector,tile1[i]);
				}
			}
		}
}
		break;
case 2:
		if(dudeManBro.getX()+40>=tile2[i].getX()&&dudeManBro.getX()+dudeManBro.getScaledWidth()-40<=tile2[i].getX()+tile2[i].getScaledWidth())
			if(tile2[i].getY()>dudeManBro.getY()+dudeManBro.getScaledHeight()&&(!dudeManBro.isJumpingLeft()&&!dudeManBro.isJumpingRight())){
				dudeManBro.fall();
			}
		if(dudeManBro.collidesWith(tile2[i],collisionVector)){
 			if(dudeManBro.isLanding()){
				dudeManBro.land();
				dudeManBro.setY(tile2[i].getY()-dudeManBro.getScaledHeight()+heroNS::frameCompensation);
				return;
			}
			if(!dudeManBro.isLanding()){
				if(collisionVector.x<0){
					collisionVector.y = 0;
					dudeManBro.bounce(collisionVector,tile2[i]);
					dudeManBro.walk(middle);
					moveScreen = false;
				}
				if(collisionVector.x>0){
					collisionVector.y = 0;
					dudeManBro.bounce(collisionVector,tile2[i]);
					dudeManBro.walk(middle);
					moveScreen = false;
				}
		  if(!dudeManBro.collidesWith(tile2[i],collisionVector)){	
			  moveScreen = true;
		  }
			}
			}

for(int j=0; j<MAX_SKELLINGTONS; j++){
	collisionVector.x = 0;
	collisionVector.y = 0;
if(enemy[1][j]->getX()+40>=tile2[i].getX()&&enemy[1][j]->getX()+enemy[1][j]->getScaledWidth()-40<=tile2[i].getX()+tile2[i].getScaledWidth())
			if(tile2[i].getY()-4>enemy[1][j]->getY()+enemy[1][j]->getScaledHeight()){
				enemy[1][j]->fall();
			}
		if(enemy[1][j]->collidesWith(tile2[i],collisionVector)){
 			if(enemy[1][j]->isLanding()){
				enemy[1][j]->land();
				enemy[1][j]->setY(tile2[i].getY()-enemy[1][j]->getScaledHeight()-4);
			}
			if(!enemy[1][j]->isLanding()){
				if(collisionVector.x<0){
					enemy[1][j]->bounce(collisionVector,tile2[i]);
				}
				if(collisionVector.x>0){
					enemy[1][j]->bounce(collisionVector,tile2[i]);
				}
			}
		}
}
	}
}
}

void Anax::entityEntityCollisions(){
	collisionVector.x = 0;
	collisionVector.y =0;
	for(int i=0; i<MAX_SLIMES; i++){
		if(magicMissile.collidesWith(*enemy[0][i], collisionVector)){
			enemy[0][i]->hit(FIREBALL_DMG, frameTime);
			audio->playCue(SLIME_DIE);
			magicMissile.setActive(false);
			magicMissile.setVisible(false);
		}
		if(!cheatsOn) {
			if(dudeManBro.collidesWith(*enemy[0][i], collisionVector)){
				dudeManBro.hit(1, frameTime);
			}
		}
	}
	for(int i=0; i<MAX_SKELLINGTONS; i++){
		if(magicMissile.collidesWith(*enemy[1][i], collisionVector)){
			enemy[1][i]->hit(FIREBALL_DMG, frameTime);
			audio->playCue(SKELLINGTON_DIE);
			magicMissile.setActive(false);
			magicMissile.setVisible(false);
		}
		if(!cheatsOn) {
			if(dudeManBro.collidesWith(*enemy[1][i], collisionVector)){
				dudeManBro.hit(1, frameTime);
			}
		}
	}
}
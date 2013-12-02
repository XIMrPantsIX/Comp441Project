#include "skellington.h"


Skellington::Skellington(){
	jumpLeft = true;
	jumpRight = false;
	landing = false;
	velocity.y = 0;
	health = 3;
	hitTimer=0;
	secondsPassed = 0;
	isHit = false;
}


void Skellington::ai(float frameTime, Entity &ent){
		if(ent.getX()>getX()){
			spriteData.flipHorizontal = true;
			if((getX()-ent.getX())>=20||getX()-ent.getX()<= 10){
				right();
			}
			else stop();
		}
		else{
			spriteData.flipHorizontal = false;
			if(getX()-ent.getX()>=20||getX()-ent.getX()<= 10){
				left();
			}
			else stop();
		}
	}

void Skellington::update(float frameTime){
	setFrames(SKELLINGTON_0,SKELLINGTON_5);
	if(Enemy::getHealth()<=0){
		setActive(false);
		setVisible(false);
	}
	if(isLanding()) updateFall(frameTime);
	Enemy::update(frameTime);
	updateHit(frameTime);
	spriteData.y -= velocity.y*frameTime;
}




void Skellington::hit(int damage, float frameTime){
	isHit = true;
	if(hitTimer == 0){
		health -= damage;
		if(health < 0)
			health = 0;
	}
	updateHit(frameTime);
}

void Skellington::updateHit(float frameTime){
	if(isHit){
		hitTimer += frameTime;
	}
	if(hitTimer > .5){
		hitTimer = 0;
		isHit = false;
	}
}
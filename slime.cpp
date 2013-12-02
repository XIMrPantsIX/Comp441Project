
#include "Slime.h"


Slime::Slime(){
	jumpLeft = true;
	jumpRight = false;
	landing = false;
	canJump = true;
	velocity.y = 0;
	health = 1;
	secondsPassed = 0;
}


void Slime::ai(float frameTime, Entity &ent){
		Enemy::ai(frameTime,ent);
}
void Slime::update(float frameTime){

	if(Enemy::getHealth()<=0){
		setActive(false);
		setVisible(false);
	}
	if(isLanding()) updateFall(frameTime);
	spriteData.y -= velocity.y*frameTime;
	Enemy::update(frameTime);
}

void Slime::updateFall(float frameTime){
		velocity.y = -slimeNS::SPEED*2;
}
void Slime::updateJump(float frameTime){}


void Slime::jump(int direction) {}

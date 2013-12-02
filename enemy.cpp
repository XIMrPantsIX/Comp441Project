
#include "enemy.h"

Enemy::Enemy(){
	walkingLeft = false;
	walkingRight = false;
	facingLeft = true;
	facingRight = false;
	jumpLeft = false;
	jumpRight = false;
	landing = false;
	velocity.x = 0;
	velocity.y = 0;
	health = 5;
	secondsPassed = 0;
	isHit = false;
	hitTimer = 0;
}


void Enemy::update(float frameTime)
{
	if(isFacingRight() && walkingRight == false){}
	if(isWalkingLeft()){}
	if(isWalkingRight()){}
	if(isFacingLeft()&&!isWalkingLeft()){}
	spriteData.x += velocity.x*frameTime;
	Entity::update(frameTime);
}


void Enemy::walk(int direction){
	if(direction == 0){ walkingLeft = true; walkingRight = false; facingLeft = true; facingRight = false;
		left();
	}
	if(direction == 1){ walkingRight = true; walkingLeft = false; facingRight = true; facingLeft = false;
		right();
	}
	if(direction == 2){ walkingRight = false; walkingLeft = false;
		stop();
	}
}
void Enemy::face(int direction){
	if(direction == 0){ facingLeft = true; facingRight = false;}
	if(direction == 1){facingRight = true; facingLeft = false;}
}
void Enemy::jump(int direction){}
	


void Enemy::updateJump(float frameTime){}
void Enemy::fall(){}
void Enemy::land(){}
void Enemy::updateFall(float frameTime){}
void Enemy::incDmgCounter(){dmgCounter++;}
int Enemy::getDmgCounter(){return dmgCounter;}

void Enemy::hit(int damage, float frameTime){
	health -= damage;
	if (health < 0)
		health = 0;
}

void Enemy::ai(float frameTime, Entity &ent){
	secondsPassed += frameTime;
	if(secondsPassed<=1.0){ 
		left(); facingLeft = true; facingRight = false;}
	if(secondsPassed>1.0){ 
		right(); facingRight = true; facingLeft = false;}
	if(secondsPassed>2.0) secondsPassed = 0;
}

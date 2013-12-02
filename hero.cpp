#include "Hero.h"


Hero::Hero(){
	walkingLeft = false;
	walkingRight = false;
	facingLeft = true;
	facingRight = false;
	jumpLeft = false;
	jumpRight = false;
	landing = false;
	hasWeapon = true;
	attackLeft = false;
	attackRight = false;
	secondsAttacking = 0;
	velocity.y = 0;
	health = 6;
	hitTimer = (float)0.1;
	deadTimer = 0;
	isHit = false;
}


void Hero::update(float frameTime, Entity &missile)
{
	if(isFacingRight() && !walkingRight && !jumpRight && !attackRight){
		setFrames(HERO_STANDING_RIGHT_START + isArmed(), HERO_STANDING_RIGHT_END + isArmed());
	}
	if(isWalkingLeft()){
		setFrames(HERO_WALKING_LEFT_START + isArmed(), HERO_WALKING_LEFT_END + isArmed());
	}
	if(isWalkingRight()){
		setFrames(HERO_WALKING_RIGHT_START + isArmed(), HERO_WALKING_RIGHT_END + isArmed());
	}
	if(isFacingLeft() && !walkingLeft && !jumpLeft && !attackLeft){
		setFrames(HERO_STANDING_LEFT_START + isArmed(), HERO_STANDING_LEFT_END + isArmed());
	}
	if(isAttackingLeft()){
		updateAttack(frameTime,missile);
	}
	if(isAttackingRight()){
		updateAttack(frameTime,missile);
	}
	if((jumpLeft||jumpRight))
		updateJump(frameTime);
	if(!(jumpLeft||jumpRight)){
		secondsJumped = 0;
		velocity.y = 0;
	}
	if(landing) updateFall(frameTime);

	if(spriteData.x < 0) spriteData.x = 0;
	spriteData.y -= velocity.y*frameTime;
	spriteData.x += velocity.x*frameTime;
	Entity::update(frameTime);
}


void Hero::walk(int direction){
	if(direction == 0){ walkingLeft = true; walkingRight = false; facingLeft = true; facingRight = false;
		velocity.x = -heroNS::SPEED;
	}
	if(direction == 1){ walkingRight = true; walkingLeft = false; facingRight = true; facingLeft = false;
		velocity.x = heroNS::SPEED;
	}
	if(direction == 2){ walkingRight = false; walkingLeft = false;
		velocity.x = 0;
	}
	if(direction == 5){ walkingRight = true; walkingLeft = false; facingRight = true; facingLeft = false;
		velocity.x = 0;
	}
}
void Hero::face(int direction){
	if(direction == 0){ facingLeft = true; facingRight = false;}
	if(direction == 1){facingRight = true; facingLeft = false;}
}
void Hero::jump(int direction){
	if(direction == 0){facingLeft = true; facingRight = false; jumpLeft = true; jumpRight = false;}
	if(direction == 1){facingLeft = false; facingRight = true; jumpLeft = false; jumpRight = true;}
	if(direction == 2){jumpLeft = false; jumpRight = false;}
}

void Hero::attack(int direction, Entity &missile){
	if(!(attackLeft||attackRight)){
		if(direction == 0){
			face(0);
			missile.setActive(true);
			missile.setVisible(true);
			missile.setX(spriteData.x - 10);
			missile.setY(spriteData.y + 50);
			attackLeft = true;
			missile.flipHorizontal(true);
		}
		if(direction == 1){
			face(1);
			missile.setActive(true);
			missile.setVisible(true);
			missile.setX(spriteData.x + spriteData.width - 50);
			missile.setY(spriteData.y + 50);
			attackRight = true;
			missile.flipHorizontal(false);
		}
	}

}

void Hero::updateAttack(float frameTime, Entity &missile){
	secondsAttacking += frameTime;

	if(attackLeft)
		missile.setX(missile.getX()-heroNS::SPEED*2*frameTime);
	if(attackRight)
		missile.setX(missile.getX()+heroNS::SPEED*2*frameTime);

	if(attackLeft){
		int i = 2;
		if(.0<=secondsAttacking)setCurrentFrame(HERO_ATTACKING_LEFT_START); 
		if(i*0.02<secondsAttacking)setCurrentFrame(HERO_ATTACKING_LEFT_START+1); 
		if(i*0.04<secondsAttacking)setCurrentFrame(HERO_ATTACKING_LEFT_START+2);
		if(i*0.06<secondsAttacking)setCurrentFrame(HERO_ATTACKING_LEFT_START+3);
		if(i*0.08<secondsAttacking)setCurrentFrame(HERO_ATTACKING_LEFT_START+4);
		if(i*.12<secondsAttacking)setCurrentFrame(HERO_ATTACKING_LEFT_START+5);
		if(i*.14<secondsAttacking)setCurrentFrame(HERO_ATTACKING_LEFT_START+6);
		if(i*.16<secondsAttacking)setCurrentFrame(HERO_ATTACKING_LEFT_START+7);
		if(i*.18<secondsAttacking)setCurrentFrame(HERO_ATTACKING_LEFT_START+8);
		if(secondsAttacking   >  i*.20)setCurrentFrame(HERO_ATTACKING_LEFT_END);
		if(secondsAttacking>i*.22){
			attackLeft = false;
			walk(2);
			secondsAttacking = 0;
			missile.setActive(false);
			missile.setVisible(false);
		}
	}
	if(attackRight){
		int i = 2;
		if(.0<=secondsAttacking)setCurrentFrame(HERO_ATTACKING_RIGHT_END); 
		if(i*0.02<secondsAttacking)setCurrentFrame(HERO_ATTACKING_RIGHT_START+8); 
		if(i*0.04<secondsAttacking)setCurrentFrame(HERO_ATTACKING_RIGHT_START+7);
		if(i*0.06<secondsAttacking)setCurrentFrame(HERO_ATTACKING_RIGHT_START+6);
		if(i*0.08<secondsAttacking)setCurrentFrame(HERO_ATTACKING_RIGHT_START+5);
		if(i*.12<secondsAttacking)setCurrentFrame(HERO_ATTACKING_RIGHT_START+4);
		if(i*.14<secondsAttacking)setCurrentFrame(HERO_ATTACKING_RIGHT_START+3);
		if(i*.16<secondsAttacking)setCurrentFrame(HERO_ATTACKING_RIGHT_START+2);
		if(i*.18<secondsAttacking)setCurrentFrame(HERO_ATTACKING_RIGHT_START+1);
		if(secondsAttacking   >   i*.20)setCurrentFrame(HERO_ATTACKING_RIGHT_START);
		if(secondsAttacking>i*.22){
			attackRight = false;
			secondsAttacking = 0;
			walk(2);
			missile.setActive(false);
			missile.setVisible(false);
		}
			
	}

	
}
void Hero::updateJump(float frameTime){
	secondsJumped += frameTime;
	if(secondsJumped<=.1){
			if(jumpLeft) setCurrentFrame(HERO_JUMPING_LEFT_START + isArmed());
			if(jumpRight)setCurrentFrame(HERO_JUMPING_RIGHT_START + isArmed());
			return;
	}
	if(secondsJumped<=.2){
			if(jumpLeft) setCurrentFrame(HERO_JUMPING_LEFT_START+1 + isArmed());
			if(jumpRight)setCurrentFrame(HERO_JUMPING_RIGHT_START+1 + isArmed());
			return;
	}
	if(secondsJumped<=.3){
			if(jumpLeft) setCurrentFrame(HERO_JUMPING_LEFT_START+2 + isArmed());
			if(jumpRight)setCurrentFrame(HERO_JUMPING_RIGHT_START+2 + isArmed());
			return;
	}
	if(secondsJumped<=.7){
		velocity.y = heroNS::SPEED*2;
			if(jumpLeft) setCurrentFrame(HERO_JUMPING_LEFT_START+3 + isArmed());
			if(jumpRight)setCurrentFrame(HERO_JUMPING_RIGHT_START+3 + isArmed());
	}
	else{
		fall();
		updateFall(frameTime);
	}
}

void Hero::fall(){
	landing=true;
	if(facingLeft) jumpLeft =true;
	if(facingRight)jumpRight=true;
}
void Hero::land(){
	landing=false;
	jump(2);
}
void Hero::updateFall(float frameTime){
	velocity.y = -heroNS::SPEED*2;
	if(jumpLeft) setCurrentFrame(HERO_JUMPING_LEFT_START+3 + isArmed());
	if(jumpRight)setCurrentFrame(HERO_JUMPING_RIGHT_START+3 + isArmed());
}

void Hero::hit(int damage, float frameTime){
	isHit = true;
	if(hitTimer == 0){
		health -= damage;
		if(health < 0)
			health = 0;
	}
	updateHit(frameTime);
}

void Hero::updateHit(float frameTime){
	if(isHit){
		hitTimer += frameTime;
	}
	if(hitTimer > 1){
		hitTimer = 0;
		isHit = false;
	}
}

int Hero::setDead(bool d){
	dead = d;
	deadTimer += 1;
	if(deadTimer > 255){
		deadTimer = 0;
		dead = false;
	}
	return deadTimer;
}

              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#ifndef _HERO_H                 // Prevent multiple definitions if this 
#define _HERO_H   
class Hero;

#include "entity.h"
#include "constants.h"

namespace heroNS
{
    const int WIDTH = 128;                   // image width
    const int HEIGHT = 64;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float SPEED = 250;    
	const int frameCompensation = 40;
	
   
}

// inherits from Entity class
class Hero : public Entity
{
private:
  
    bool collision;                 
    bool target;           

	//gamestate checkers
	bool walkingLeft;
	bool walkingRight;
	bool facingLeft;
	bool facingRight;
	bool jumpLeft;
	bool jumpRight;
	bool jumpStatLeft;
	bool jumpStatRight;
	bool attackLeft;
	bool attackRight;
	bool landing;
	bool hasWeapon;
	float hitTimer;
	bool dead;
	int deadTimer;
	bool isHit;

	float secondsJumped;
	float secondsAttacking;
	int health;
public:
    // constructor
	Hero();

    // inherited member functions
	void update(float frameTime, Entity &missile);

    // Set collision Boolean
    void setCollision(bool c)
    {collision = c;}

    // Set collision type (NONE, CIRCLE, BOX, ROTATED_BOX)
    virtual void setCollisionType(entityNS::COLLISION_TYPE ctype)
    {collisionType = ctype;}

    // Set RECT structure used for BOX and ROTATED_BOX collision detection.
    void setEdge(RECT e) {edge = e;}

	int setDead(bool d);

	int getDeadTimer(){return deadTimer;}
	bool getIsHit(){return isHit;}

	/*********HOMEGROWN FUNCTIONS*********/

	//less typing
	int getScaledWidth(){return (int)(getWidth()*getScale());}
	int getRightEdge(){return (int)(getX()+getScaledWidth());}
	int getScaledHeight(){return (int)(getHeight()*getScale());}

	//Character State Checks
	bool isWalkingLeft(){ return walkingLeft;}
	bool isWalkingRight(){ return walkingRight;}
	bool isFacingLeft(){return facingLeft;}
	bool isFacingRight(){return facingRight;}
	bool isJumpingLeft(){return jumpLeft;}
	bool isJumpingRight(){return jumpRight;}
	bool isAttackingLeft(){return attackLeft;}
	bool isAttackingRight(){return attackRight;}
	bool isLanding(){return landing;}
	bool canJump() {if(secondsJumped>=.5) return false; else return true;}
	bool canAttack(){if(secondsAttacking>0) return false; else return true;}
	void face(int direction);
	void walk(int direction);
	void jump(int direction);
	void fall();
	void land();
	void attack(int direction, Entity &missile);
	void updateJump(float frameTime);
	void updateFall(float frameTime);
	void updateAttack(float frameTime, Entity &missile);
	void updateHit(float frameTime);
	int isArmed(){if(hasWeapon)return 0; else return 44;}
    // Get collision
    bool getCollision() {return collision;}
	int getHealth() {return health;}
	void setHealth(int health) {Hero::health = health;}
	void setDeadTimer(int t) {deadTimer = t; dead=false;}

    // Get collision type
    entityNS::COLLISION_TYPE getCollisionType() {return collisionType;}

    void right()
    {
        velocity.x = heroNS::SPEED;
    }
    void left()
    {
        velocity.x = -heroNS::SPEED;
    }
	void stop()
	{
		velocity.x = 0;
	}
	void hit(int damage, float frameTime);
};
#endif


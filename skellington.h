#define WIN32_LEAN_AND_MEAN
#ifndef _SKELLINGTON_H                 // Prevent multiple definitions if this 
#define _SKELLINGTON_H  

class Skellington;

#include "entity.h"
#include "enemy.h"
#include "constants.h"


namespace skellingtonNS
{
	const int WIDTH = 62;                   // image width
    const int HEIGHT = 62;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float SPEED = 150;    
	const int frameCompensation = 40;
}

class Skellington: public Enemy
{ 
protected:
    bool collision;                 
    bool target;           
	float hitTimer;
	//gamestate checkers
	bool jumpLeft;
	bool jumpRight;
	bool jumpStatLeft;
	bool jumpStatRight;
	bool landing;
	float secondsPassed;
	float secondsJumped;
	bool isHit;
public:
	Skellington();
    // inherited member functions
	 void update(float frameTime);

    // Set collision Boolean
    void setCollision(bool c)
    {collision = c;}

    // Set collision type (NONE, CIRCLE, BOX, ROTATED_BOX)
     void setCollisionType(entityNS::COLLISION_TYPE ctype)
    {collisionType = ctype;}

    // Set RECT structure used for BOX and ROTATED_BOX collision detection.
    void setEdge(RECT e) {edge = e;}

	void setIsHit(bool h){isHit = h;}
	bool getIsHit(){return isHit;}
	void updateHit(float frameTime);

	/*********HOMEGROWN FUNCTIONS*********/

	//less typing
	 int getScaledWidth(){return (int)(getWidth()*getScale());}
	 int getRightEdge(){return (int)(getX()+getScaledWidth());}
	 int getScaledHeight(){return (int)(getHeight()*getScale());}

	//Character State Checks
	 bool isJumpingLeft(){return jumpLeft;}
	 bool isJumpingRight(){return jumpRight;}
	 bool isLanding(){return landing;}
	 void ai(float frameTime, Entity &ent);
	 void hit(int direction, float frameTime);
    // Get collision
    bool getCollision() {return collision;}
	int getHealth() {return health;}
	
	void jump(int direction)
	{
		if(direction == 0){jumpLeft = true; jumpRight = false;}
		if(direction == 1){jumpLeft = false; jumpRight = true;}
		if(direction == 2){jumpLeft = false; jumpRight = false;}
	}

	void fall(){
		landing=true;
	}
	void land(){
		landing = false;
	}
	void updateFall(float frameTime){
		velocity.y = -skellingtonNS::SPEED;
	}


    // Get collision type
    entityNS::COLLISION_TYPE getCollisionType() {return collisionType;}
};



#endif
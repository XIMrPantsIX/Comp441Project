#define WIN32_LEAN_AND_MEAN
#ifndef _SLIME_H                 // Prevent multiple definitions if this 
#define _SLIME_H  

class Slime;

#include "entity.h"
#include "enemy.h"
#include "constants.h"


namespace slimeNS
{
	const int WIDTH = 62;                   // image width
    const int HEIGHT = 62;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float SPEED = 100;    
	const int frameCompensation = 40;
}

class Slime: public Enemy
{ 
protected:
    bool collision;                 
    bool target;           

	//gamestate checkers
	bool jumpLeft;
	bool jumpRight;
	bool jumpStatLeft;
	bool jumpStatRight;
	bool landing;
	bool canJump;
	float secondsPassed;
	float secondsJumped;
public:
	Slime();
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
    // Get collision
    bool getCollision() {return collision;}
	int getHealth() {return health;}
	
	void jump(int direction);
	void fall(){landing=true;}
	void land(){
		landing=false;
	}
	void updateFall(float frameTime);
	void updateJump(float frameTime);

    // Get collision type
    entityNS::COLLISION_TYPE getCollisionType() {return collisionType;}
};



#endif
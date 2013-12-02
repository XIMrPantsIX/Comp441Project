#ifndef _MOUNTAIN_H
#define _MOUNTAIN_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"


class Mountain: public Entity{
public:
    Mountain();


	// inherited member functions
    void update(float frameTime);
	void worldCompensation();
	int getScaledWidth(){return (int)(getWidth()*getScale());}
	int getRightEdge(){return (int)(getX()+getScaledWidth());}
	int getScaledHeight(){return (int)(getHeight()*getScale());}
	void spawnMountainLeft(); //these do nothing
	void spawnMountainRight();
	void spawnMountainMiddle();


private:
	

	DWORD color;
	int value;
};



#endif
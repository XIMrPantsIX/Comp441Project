#ifndef _TILE_H
#define _TILE_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
 

const int MAX_TILES = 30;

class Tile: public Entity{
public:
	Tile();


	// inherited member functions
    void update(float frameTime);
	int getScaledWidth(){return (int)(getWidth()*getScale());}
	int getRightEdge(){return (int)(getX()+getScaledWidth());}
	int getScaledHeight(){return (int)(getHeight()*getScale());}



	
private:
	

	DWORD color;
	int value;
};



#endif
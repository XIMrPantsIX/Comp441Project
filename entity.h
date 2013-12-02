

#ifndef _ENTITY_H               
#define _ENTITY_H               
#define WIN32_LEAN_AND_MEAN

class Entity;

#include "image.h"
#include "input.h"
#include "game.h"
#include "audio.h"

namespace entityNS
{
    enum COLLISION_TYPE {NONE, CIRCLE, BOX, ROTATED_BOX, PIXEL_PERFECT};
    const float GRAVITY = 6.67428e-11f;         // gravitational constant
}

class Entity : public Image
{
    // Entity properties
private:
	VECTOR2 position;

  protected:
    entityNS::COLLISION_TYPE collisionType;
    VECTOR2 center;         
    VECTOR2 collisionCenter; 
    float   radius;         
    VECTOR2 distSquared;    
    float   sumRadiiSquared;
    // edge specifies the collision box relative to the center of the entity.
    // left and top are typically negative numbers
    RECT    edge;           // for BOX and ROTATED_BOX collision detection
    VECTOR2 corners[4];     // for ROTATED_BOX collision detection
    VECTOR2 edge01,edge03;  // edges used for projection
    float   edge01Min, edge01Max, edge03Min, edge03Max; // min and max projections
    VECTOR2 velocity;       
    VECTOR2 deltaV;         // added to velocity during next call to update()
    float   mass;           
    float   health;         
    float   rr;             
    float   force;          
    float   gravity;        
    Input   *input;         
    HRESULT hr;             
    bool    active;         
    bool    rotatedBoxReady;   

    // Circular collision detection 
    virtual bool collideCircle(Entity &ent, VECTOR2 &collisionVector);
    // Axis aligned box collision detection
    virtual bool collideBox(Entity &ent, VECTOR2 &collisionVector);
    // Separating axis collision detection between boxes
    virtual bool collideRotatedBox(Entity &ent, VECTOR2 &collisionVector);
    // Separating axis collision detection between box and circle
    virtual bool collideRotatedBoxCircle(Entity &ent, VECTOR2 &collisionVector);
    // Separating axis collision detection helper functions
    void computeRotatedBox();
    bool projectionsOverlap(Entity &ent, VECTOR2 &collisionVector);
    bool collideCornerCircle(VECTOR2 corner, Entity &ent, VECTOR2 &collisionVector);

  public:
    Entity();
    virtual ~Entity() {}

    ////////////////////////////////////////
    //           Get functions            //
    ////////////////////////////////////////

    virtual const VECTOR2* getCenter()  {
        center = VECTOR2(getCenterX(),getCenterY());
        return &center;
    }

    virtual const VECTOR2* getCollisionCenter() { return &collisionCenter; }
    virtual float getRadius() const     {return radius;}
	virtual const RECT& getEdge() const {return edge;}
    virtual const VECTOR2* getCorner(UINT c) const {
        if(c>=4)  c=0;
        return &corners[c]; 
    }
    virtual const VECTOR2 getVelocity() const {return velocity;}
	virtual bool  getActive()         const {return active;}
	virtual float getMass()           const {return mass;}
	virtual float getGravity()        const {return gravity;}
    virtual float getHealth()         const {return health;}

    virtual entityNS::COLLISION_TYPE getCollisionType() {return collisionType;}
	VECTOR2 getPosition() {return position;}
	float getPositionX() {return position.x;}
	float getPositionY() {return position.y;}

    ////////////////////////////////////////
    //           Set functions            //
    ////////////////////////////////////////

    virtual void  setVelocity(VECTOR2 v)    {velocity = v;}
    virtual void  setDeltaV(VECTOR2 dv)     {deltaV = dv;}
    virtual void  setActive(bool a)         {active = a;}
    virtual void  setHealth(float h)         {health = h;}
    virtual void  setMass(float m)          {mass = m;}
    virtual void  setGravity(float g)       {gravity = g;}
    virtual void setCollisionRadius(float r)    {radius = r;}
    virtual void setCollisionCenter(VECTOR2 cc) {collisionCenter = cc;}
    virtual void setCollisionType(entityNS::COLLISION_TYPE ctype)  {collisionType = ctype;}
	virtual void setEdge(RECT e)    {edge = e;}
    virtual void setRotatedBoxReady(bool r) {rotatedBoxReady = r;}

	void setPosition(VECTOR2 pos) {position = pos;}
	void setPositionX(float pos) {position.x = pos;}
	void setPositionY(float pos) {position.y = pos;} 
	void incPositionX(float pos) {position.x += pos;}
	void incPositionY(float pos) {position.y += pos;}
	void incPosition(VECTOR2 pos) {position += pos;}


    ////////////////////////////////////////
    //         Other functions            //
    ////////////////////////////////////////




    virtual void update(float frameTime);     // typically called once per frame

    //     *gamePtr = pointer to Game object
    //      width = width of Image in pixels  (0 = use full texture width)
    //      height = height of Image in pixels (0 = use full texture height)
    //      ncols = number of columns in texture (1 to n) (0 same as 1)
    //      *textureM = pointer to TextureManager object
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
    virtual void activate();
    virtual void ai(float frameTime, Entity &ent);
    virtual bool outsideRect(RECT rect);
	virtual bool collidesWith(Entity &ent, VECTOR2 &collisionVector);
    virtual void damage(int weapon);
    void bounce(VECTOR2 &collisionVector, Entity &ent);
    void gravityForce(Entity *other, float frameTime);
};

#endif

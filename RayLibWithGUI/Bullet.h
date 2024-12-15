// Specification file for bullet class
// Extends actor, moves every frame and collides with objects


#include "Actor.h"

#ifndef BULLET_H
#define BULLET_H

class Bullet : public Actor {

private:
	float speed = 0;
	float lifeTimeMax = 1; 
	float lifeTime = lifeTimeMax; // When lifetime expires, bullet is erased


public:
	Bullet();

	// Set and get functions
	void setSpeed(float);
	float getSpeed();
	void setLifeTimeMax(float);
	float getLifeTimeMax();
	void setLifeTime(float);
	float getLifeTime();

	// Called every frame
	void process();
	void draw();

	// Collisions function
	void beginOverlap(Actor* a);

	// Damage function
	void takeDamage(float);

	
};



#endif

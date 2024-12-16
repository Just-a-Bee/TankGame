// Specification file for FireTank Class
// Extends tank, has the ability to fire


#include "Tank.h"
#include "Bullet.h"

#ifndef FIRETANK_H
#define FIRETANK_H

class FireTank : public Tank {
private:
	// Firing vars
	float cooldown = 0;
	float cooldownMax = .3f;
	float bulletSpeed = 50;
public:
	// Constructor function
	FireTank();

	// Set and get functions
	void setCooldown(float);
	float getCooldown();
	void setCooldownMax(float);
	float getCooldownMax();
	void setBulletSpeed(float);
	float getBulletSpeed();

	// Called every frame
	void process();

	// Function to fire, adds a bullet to the manager's vector
	void fire();


};



#endif
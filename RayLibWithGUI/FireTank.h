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
	int shotCount = 1; // number of bullets to fire
	float shotSpread = 0; // degrees to spread the shots evenly between (eg 30 means +- 15? degrees from forward)
	// Bullet pool vars
	Bullet* bulletPool = nullptr;
	int fireIndex = 0;
	int bulletCount = 20;

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
	void setShotCount(int shotCount) { this->shotCount = shotCount;}
	float getShotCount() { return shotCount; }
	void setShotSpread(float shotSpread) { this->shotSpread = shotSpread; }
	float getShotSpread() { return shotSpread; }

	// Called every frame
	void process();

	// Function to fire, adds a bullet to the manager's vector
	void fire();

	~FireTank();

};



#endif
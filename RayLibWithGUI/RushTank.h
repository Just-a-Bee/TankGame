// Specification file for Rush Tank
// Faster than normal tanks, does less damage on contact

#include "Tank.h"

#ifndef RUSHTANK_H
#define RUSHTANK_H

class RushTank : public Tank {
public:
	RushTank() {
		setMoveSpeed(8);
		setRotateSpeed(60);
		setHealth(1);
		setCollideDamage(2);
		setMaxHealth(1);
	}
};


#endif
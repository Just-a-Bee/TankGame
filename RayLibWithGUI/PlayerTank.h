// Specification file for tank actor
// Drawn with a mesh, can move and fire


#include "FireTank.h"


#ifndef PLAYERTANK_H
#define PLAYERTANK_H

class Powerup;

class PlayerTank : public FireTank {
private:
	Powerup* currentPowerup;

public:
	// Begin overlap used for collecting powerups
	void beginOverlap(Actor* a) override;

	void process() override;

	void deactivatePowerup();

	Powerup* getCurrentPowerup() { return currentPowerup; };

	~PlayerTank();
};



#endif
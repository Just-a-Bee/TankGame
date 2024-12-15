// Specification file for AIController 
// Moves the tank to attack tanks on other teams

#include "TankController.h"

#ifndef AICONTROLLER_H
#define AICONTROLLER_H

class AIController : public TankController {
private:
	// Constants
	const float MAX_TARGET_RANGE = 100;
	const float WIDE_TOLERANCE = 45;
	const float NARROW_TOLERANCE = 5;
	
	Vector3 moveTarget = Vector3Zero(); // Target position to move to
	bool doPathfinding = true; // Turned false to block constant calls to findTarget() while moving
	void turnAndMove(float);
	Tank* findTarget();
	Vector3 findMoveTarget();

public:
	void process();
};

#endif
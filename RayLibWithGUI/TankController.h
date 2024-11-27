// Specification file for tank controller classes, process function is called by controlled tank every frame

#include "Tank.h"
#include "FireTank.h"

// Base class doesn't do anything
#ifndef TANKCONTROLLER_H
#define TANKCONTROLLER_H

class TankController {
private:
	// Pointer to the tank this object controls
	Tank* controlledTank = nullptr;

public:
	// Constructor functions
	TankController();
	TankController(Tank*);
	// Set get functions
	Tank* getControlledTank();
	void setControlledTank(Tank*);
	// Process function
	virtual void process();

};

#endif

// AI controller moves the tank to attack tanks on other teams
#ifndef AICONTROLLER_H
#define AICONTROLLER_H

class AIController : public TankController {
private:
	const float MAX_TARGET_RANGE = 100;
public:
	void process();
	Tank* findTarget();
};

#endif
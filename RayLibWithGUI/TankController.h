// Specification file for tank controller classes
// Uses strategy pattern to allow tanks to have different behaviors
// Process function is called by controlled tank every frame

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


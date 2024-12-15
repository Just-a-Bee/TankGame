// Implementation file for tankContoller class
// Uses strategy pattern to allow tanks to have different behaviors


#include "TankController.h"

	// Constructor functions
TankController::TankController() {}
TankController::TankController(Tank* t) {
	controlledTank = t;
}

// Set get functions
Tank* TankController::getControlledTank() {
	return controlledTank;
}
void TankController::setControlledTank(Tank* t) {
	controlledTank = t;
}

// Process function, overriden by child classes
void TankController::process() {}



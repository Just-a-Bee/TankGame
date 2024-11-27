// Implementation file for tankContoller class


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


void AIController::process() {

	// Turn to face target
	Tank* target = findTarget();
	if (target) {
		// This math is so complicated honestly I dont get it
		Vector3 vectorToTarget = Vector3Normalize(Vector3Subtract(target->getPosition(), getControlledTank()->getPosition())); // Calculate the direction to the player
		float targetRotation = (Vector2Angle(Vector2{ 1, 0 }, Vector2{ vectorToTarget.x, -vectorToTarget.z }) * RAD2DEG); // Calculate the angle we want to point at
		float turnAngle = getControlledTank()->toValidAngle(getControlledTank()->getRotation() - targetRotation); // Calculate the angle that must be turned by

		// If angle is very far off, just turn
		if (abs(turnAngle) > 45)
		{
			if (turnAngle >= 0)
				getControlledTank()->move(1, -1);
			else
				getControlledTank()->move(-1, 1);
		}
		// If angle is less far off, turn and move
		else if (abs(turnAngle) > 3) {
			if (turnAngle >= 0)
				getControlledTank()->move(1, 0);
			else
				getControlledTank()->move(0, 1);
		}
		// If angle is very close, move forward
		else
			getControlledTank()->move(1, 1);
	}

	// Do firing only if controlled tank can fire
	FireTank* controlledAsFireTank = dynamic_cast<FireTank*>(getControlledTank());
	if (controlledAsFireTank)
		controlledAsFireTank->fire();
}

Tank* AIController::findTarget() {
	Tank* target = nullptr;
	float nearestDistance = MAX_TARGET_RANGE;


	// iterate over actors, picking the cloest tank on another team
	for (Actor* a : getControlledTank()->getManager()->getActors()) {
		Tank* aTank = dynamic_cast<Tank*>(a);
		if (aTank) {
			if (aTank->getTeam() != getControlledTank()->getTeam()) {
				if ((Vector3Length(Vector3Subtract(getControlledTank()->getPosition(), aTank->getPosition()))) < nearestDistance) {
					target = aTank;
				}
			}
		}
	}

	return target;


}
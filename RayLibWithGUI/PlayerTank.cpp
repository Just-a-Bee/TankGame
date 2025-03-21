#include "PlayerTank.h"
#include "Powerup.h"

void PlayerTank::beginOverlap(Actor* a) {

	// if collided with a powerup, use it
	Powerup* aPowerup = dynamic_cast<Powerup*>(a);
	if (aPowerup) {
		deactivatePowerup();
		getManager()->queueRemoveActor(aPowerup);
		currentPowerup = aPowerup;
		currentPowerup->activate(this);
	}
}

void PlayerTank::process() {
	FireTank::process();

	// Decrement powerup duration, if it has expired, delete it
	if (currentPowerup) {
		currentPowerup->duration -= GetFrameTime();
		if (currentPowerup->duration <= 0) {
			deactivatePowerup();
		}
	}
}

// Function to deactivate the current powerup
void PlayerTank::deactivatePowerup() {

	if (currentPowerup) {
		currentPowerup->deactivate(this);
		delete currentPowerup;
		currentPowerup = nullptr;
	}
}

PlayerTank::~PlayerTank() {
	if (currentPowerup) {
		delete currentPowerup;
	}

}
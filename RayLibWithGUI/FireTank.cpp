// Imlementation file for FireTank
// A Tank that can fire Bullets

#include "FireTank.h"


const float BULLET_DISTANCE = 2.2f; // distance bullets spawn from this


FireTank::FireTank() {
};

// Set and get functions
void FireTank::setCooldown(float c) {
	cooldown = c;
}
float FireTank::getCooldown() {
	return cooldown;
}
void FireTank::setCooldownMax(float c) {
	cooldownMax = c;
}
float FireTank::getCooldownMax() {
	return cooldownMax;
}
void FireTank::setBulletSpeed(float s) {
	bulletSpeed = s;
}
float FireTank::getBulletSpeed() {
	return bulletSpeed;
}


// Process function decrements cooldown
void FireTank::process() {
	cooldown -= GetFrameTime(); // decrement cooldown
	Tank::process(); // Call parent class process
}


// Function to fire a bullet
void FireTank::fire() {
	// Check if we're under cooldown
	if (cooldown <= 0) {
		cooldown = cooldownMax; // Reset cooldown


		Bullet* b = new Bullet;

		// Set the bullet's variables
		b->setPosition(Vector3Add(getPosition(), Vector3Scale(forwardVector(), BULLET_DISTANCE)));
		b->setRotation(getRotation());
		b->setSpeed(getBulletSpeed());
		b->setLifeTime(b->getLifeTimeMax());
		b->setTeam(getTeam());

		// Add bullet to actorManager
		getManager()->addActor(b);
	}

}
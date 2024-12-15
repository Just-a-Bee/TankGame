// Implementation file for bullet class
// Moves every frame, and checks if it collides with other objects

#include "Bullet.h"

// Default constructor
Bullet::Bullet() {
	setSize(1);
}

// Set and get functions
void Bullet::setSpeed(float s) {
	speed = s;
}
float Bullet::getSpeed() {
	return speed;
}
void Bullet::setLifeTimeMax(float t) {
	lifeTimeMax = t;
}
float Bullet::getLifeTimeMax() {
	return lifeTimeMax;
}
void Bullet::setLifeTime(float t) {
	lifeTime = t;
}
float Bullet::getLifeTime() {
	return lifeTime;
}

// Process function moves and checks collision
void Bullet::process() {

	Vector3 moveVector = Vector3Scale(forwardVector(), speed * GetFrameTime()); // vector bullet will move by
	setPosition(Vector3Add(getPosition(), moveVector)); // move
	
	// handle despawning
	lifeTime -= GetFrameTime();
	
	if (lifeTime <= 0) {
		queueRemove();
	}
}
// Draw functon, draw a cube at position
void Bullet::draw() {
	DrawCube(getPosition(), 1, 1, 1, getTeam()->secondaryColor);
}

// Function to collide with other actors
void Bullet::beginOverlap(Actor* a) {
	if (a->getTeam() != getTeam()) {
		a->takeDamage(1);
		queueRemove();
	}
}

// Take damage function erases self
void Bullet::takeDamage(float) {
	queueRemove();
}

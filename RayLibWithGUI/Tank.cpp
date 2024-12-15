// Implementation file for tank actor class


#include "Tank.h"
#include "TankController.h" // Include is here to avoid recursive inclusion

// Constants
const float BULLET_DISTANCE = 2.2f;


// Constructor function
Tank::Tank() {
	// Initialize model
	setSize(3);
	mesh = GenMeshCube(getSize(), getSize(), getSize());
	model = LoadModelFromMesh(mesh);
	
}


// Set and get functions
void Tank::setRotateSpeed(float s) {
	rotateSpeed = s;
}
float Tank::getRotateSpeed() {
	return rotateSpeed;
}
void Tank::setMoveSpeed(float s) {
	moveSpeed = s;
}
float Tank::getMoveSpeed() {
	return moveSpeed;
}
void Tank::setHealth(float h) {
	health = h;
}
float Tank::getHealth() {
	return health;
}
void Tank::setCollideDamage(float d) {
	collideDamage = d;
}
float Tank::getCollideDamage() {
	return collideDamage;
}
void Tank::setController(TankController* c) {
	controller = c;
	controller->setControlledTank(this);
}
TankController* Tank::getController() {
	return controller;
}


// Functions called every frame
void Tank::process() {
	controller->process();
}
// Draw function draws model
void Tank::draw() {
	DrawModelEx(model, getPosition(), Vector3(0, 1, 0), getRotation(), Vector3One(), getTeam()->primaryColor);
}


// Collision function damages target, target will damage this back, we dont need to worry about that
void Tank::beginOverlap(Actor* a) {
	if (a->getTeam() != getTeam())
		a->takeDamage(collideDamage);
}


// Other functions

// Function to move based on track directions
void Tank::move(float leftTrack, float rightTrack) {

	Vector3 previousPosition = getPosition();

	// Rotate based on track directions
	setRotation(getRotation() - leftTrack * rotateSpeed * GetFrameTime());
	setRotation(getRotation() + rightTrack * rotateSpeed * GetFrameTime());
	
	// Move forward based on track directions
	float moveDistance = (leftTrack + rightTrack) * moveSpeed * GetFrameTime();
	setPosition(Vector3Add(getPosition(), Vector3Scale(forwardVector(), moveDistance)));

	// If colliding with a wall or tank on the same team, go back to previous position
	for (Actor* a : getOverlappingActors()) {
		if (dynamic_cast<Wall*>(a)
			|| (dynamic_cast<Tank*>(a) && a->getTeam() == getTeam())) {
			setPosition(previousPosition);
		}
	}
}



// Function to take damage, reduces health, on 0 health tank is erased
void Tank::takeDamage(float damage) {
	health -= damage;
	if (health <= 0) {
		GameData::getInstance()->incrementScore(1);
		queueRemove();
	}
}


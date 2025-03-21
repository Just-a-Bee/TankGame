// Implementation file for tank actor class


#include "Tank.h"
#include "TankController.h" // Include is here to avoid recursive inclusion
#include "Powerup.h"

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
void Tank::setMaxHealth(float h) {
	maxHealth = h;
}
float Tank::getMaxHealth() {
	return maxHealth;
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


void Tank::onHitActor(Actor* a) {
	if (a->getTeam() != this->getTeam()) {
		a->takeDamage(collideDamage);
	}
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
}



// Function to take damage, reduces health, on 0 health tank is erased
void Tank::takeDamage(float damage) {
	health -= damage;
	if (health <= 0) {
		GameData::getInstance()->incrementScore(1);


		float dropRoll = ((float)rand() / RAND_MAX);
		std::cout << dropRoll << "\n";
		if (dropRoll > .9) {
			// Determine which powerup to drop
			Powerup* powerToSpawn;


			if (dropRoll > .99) {
				powerToSpawn = new MultiShot;
			}
			else if (dropRoll > .95) {
				powerToSpawn = new RapidFire;
			}
			else {
				powerToSpawn = new SpeedBoost;
			}

			// Create a powerup at this position
			powerToSpawn->setPosition(getPosition());
			getManager()->addActor(powerToSpawn);

		}


		queueRemove();
	}
}

// Destructor deletes pointer to controller
Tank::~Tank() {
	delete controller;
	UnloadMesh(mesh);
}

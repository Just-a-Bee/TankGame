// Imlementation file for actor, base class for all game objects

#include "Actor.h"

// Default Constructor
Actor::Actor() {}

// Setters and getters
ActorManager* Actor::getManager() {
	return manager;
}
void Actor::setManager(ActorManager* m) {
	manager = m;
}
Vector3 Actor::getPosition() {
	return position;
}
void Actor::setPosition(Vector3 p) {
	position = p;
}
float Actor::getRotation() {
	return rotation;
}
void Actor::setRotation(float r) {
	rotation = toValidAngle(r);
}
Team* Actor::getTeam() {
	return team;
}
void Actor::setTeam(Team* t) {
	team = t;
}


// Return value functions

// Returns the direction the actor is facing (based on rotation
Vector3 Actor::forwardVector() {
	float rotationRadians = DEG2RAD * rotation;
	return Vector3RotateByAxisAngle(Vector3(1, 0, 0), Vector3(0, 1, 0), rotationRadians);
}

// Virtual function returns the bounding box of the actor
BoundingBox Actor::bounds() {
	return BoundingBox{ Vector3{0,0,0}, Vector3{0,0,0} };
}

// Function to return a vector of actors that overlap this
std::vector<Actor*> Actor::getOverlappingActors() {
	
	std::vector<Actor*> overlaps;
	BoundingBox bounds = this->bounds();

	// Iterate over every actor (except for this) and check if it overlaps
	for (Actor* a : getManager()->getActors()) {
		if (a == this) {}
		else if (CheckCollisionBoxes(bounds, a->bounds()))
			overlaps.push_back(a);
	}

	return overlaps;
}

// Function to return if actor is within a specified actor manager
bool Actor::belongsToManager(ActorManager* m) {
	return (m == manager);
}
// Snap rotation to be in range (-180, 180]
float Actor::toValidAngle(float r) {
	
	while (r > 180)
		r -= 360;
	while (r <= -180)
		r += 360;
	return r;
}

// Other functions
// Virtual process function called every frame
void Actor::process() {}
//Update overlaps function checks if overlapping actors has changed, calls begin or end overlap for each change
void Actor::updateOverlaps() {
	std::vector<Actor*> overlaps = getOverlappingActors();

	std::sort(overlaps.begin(), overlaps.end());

	if (overlaps != previousOverlaps) {
		std::vector<Actor*> difference;
		// Get the new overlaps by finidng the difference from previous
		std::set_difference(overlaps.begin(), overlaps.end(),
			previousOverlaps.begin(), previousOverlaps.end(), std::back_inserter(difference));
		for (Actor* a : difference) {
			beginOverlap(a);
		}
		// Get the ended overlaps by finidng previous's difference from new
		std::set_difference(previousOverlaps.begin(), previousOverlaps.end(),
			overlaps.begin(), overlaps.end(), std::back_inserter(difference));
		for (Actor* a : difference) {
			endOverlap(a);
		}

	}

	previousOverlaps = overlaps;
}

// Virtual Draw function called every frame
void Actor::draw() {}

// Virtual collision functions
void Actor::beginOverlap(Actor* a) {};
void Actor::endOverlap(Actor* a) {};

// Virtual take damage function
void Actor::takeDamage(float damage) {}
// Function to queue removal of this actor
void Actor::queueRemove() {
	if (manager)
		manager->queueRemoveActor(this);
}
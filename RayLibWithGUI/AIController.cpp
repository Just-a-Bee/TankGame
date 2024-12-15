// Implementation file for AIController Class
// Controls an AITank to chase after and fire at player (if able to fire)

#include "AIController.h"
#include "AStar.h"

// Process function called every frame by controlledTank
void AIController::process() {

	// Check if we've reached the AStar move target
	if (!doPathfinding) {
		Vector3 pos = getControlledTank()->getPosition();
		float distance = Vector3Length(Vector3Subtract(pos, moveTarget));
		if (distance < 1.6)
			doPathfinding = true; // Move target reached, need to get a new one
	}

	// Find the move target
	if (doPathfinding)
		moveTarget = findMoveTarget();

	// Calculate how we need to turn to face target
	Vector3 vectorToTarget = Vector3Normalize(Vector3Subtract(moveTarget, getControlledTank()->getPosition())); // Calculate the direction to the player
	float targetRotation = (Vector2Angle(Vector2{ 1, 0 }, Vector2{ vectorToTarget.x, -vectorToTarget.z }) * RAD2DEG); // Calculate the angle we want to point at
	float turnAngle = getControlledTank()->toValidAngle(getControlledTank()->getRotation() - targetRotation); // Calculate the angle that must be turned by
	
	turnAndMove(turnAngle); // Move based on turnAngle

	// Do firing only if controlled tank can fire
	FireTank* controlledAsFireTank = dynamic_cast<FireTank*>(getControlledTank());
		if (controlledAsFireTank)
			controlledAsFireTank->fire();
}

// Function to turn and move based on a target angle
void AIController::turnAndMove(float turnAngle) {
	// If angle is very far off, just turn
	if (abs(turnAngle) > WIDE_TOLERANCE)
	{
		if (turnAngle >= 0)
			getControlledTank()->move(1, -1);
		else
			getControlledTank()->move(-1, 1);
	}
	// If angle is less far off, turn and move
	else if (abs(turnAngle) > NARROW_TOLERANCE) {
		if (turnAngle >= 0)
			getControlledTank()->move(1, 0);
		else
			getControlledTank()->move(0, 1);
	}
	// If angle is very close, move forward
	else
		getControlledTank()->move(1, 1);
}

// Function to find target Tank on enemy team
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

// Function to find the target position to move to
// If there is line of sight to the nearest target, move target is target.position
// Otherwise, uses AStar to move toward the target
// While moving to next AStar point, pathfinding is disabled to reduce the number of calls to the algorithm
Vector3 AIController::findMoveTarget() {
	Tank* target = findTarget(); // Find the target tank to move towards (currently only ever the player)


	// If there is no target, return
	if (!target) {
		return Vector3Zero();
	}


	// If we have line of sight to target, move to target
	Ray ray = { 0 };
	RayCollision collision = { 0 };
	ray.position = getControlledTank()->getPosition();
	ray.direction = Vector3Normalize(Vector3Subtract(target->getPosition(), getControlledTank()->getPosition()));

	Actor* nearestCollision = target;
	float nearestDistance = GetRayCollisionBox(ray, target->bounds()).distance;

	for (Actor* a : getControlledTank()->getManager()->getActors()) {
		// Check if any walls are in the way
		if (dynamic_cast<Wall*>(a)) {
			collision = GetRayCollisionBox(ray, a->bounds());

			if ((collision.hit) && (collision.distance < nearestDistance)) {
				nearestCollision = a;
				nearestDistance = collision.distance;
			}
				
		}
	}
	// If there were no walls between this and target, we have line of sight
	if (nearestCollision == target) {
		//std::cout << "Line of sight  found\n"; // Debug output
		return target->getPosition();
	}


	// Else, use aStar to approach target
	Vector3 startPos = getControlledTank()->getPosition();
	Vector3 endPos = findTarget()->getPosition();

	// Convert positions into map coordinates
	int startingX = startPos.x / 10;
	int startingY = startPos.z / 10;
	int endingX = endPos.x / 10;
	int endingY = endPos.z / 10;

	std::vector<std::vector<int>> walls = getControlledTank()->getManager()->getWallMap();
	
	// Call the AStarSearch, returns the next position to go to
	Pair nextPoint = AStar::AStarSearch(startingX, startingY, endingX, endingY, walls);
	
	// Block pathfinding while moving to target position
	doPathfinding = false;
	
	// Convert result into world coordinates
	return Vector3(nextPoint.first * 10 + 5, 0, nextPoint.second * 10 + 5);
	


}
// Implementation file for actor manager
// Contains a vector of actors and calls their process and draw functions every frame

#include "ActorManager.h"
#include "Actor.h" // Actor is included here to get around circular inclusion
#include "Wall.h" 
#include "FireTank.h";
#include "PlayerController.h"
#include "AIController.h"
#include "RushTank.h"
#include "Constants.h"

// Constructor function initializes actors
ActorManager::ActorManager() {

	spawnPlayer();
	
	// Initialize walls
	for (int i = 0; i < wallMap.size(); i++)
		for (int j = 0; j < wallMap[0].size(); j++)
			if (wallMap[i][j] == 1) {
				addActor(new Wall(i , j ));
			}

}


// Functions to interface with actorVec
// 
// Function to get vector of actors
std::vector<Actor*> ActorManager::getActors() {
	return actorVec;
}
// Function to add an actor, appended to the vector
void ActorManager::addActor(Actor* a) {
	a->setManager(this);
	actorVec.push_back(a);
}
// Function to an actor to the queue of actors to be removed
void ActorManager::queueRemoveActor(Actor* a) {
	removeQueue.push_back(a);
}
// Function to remove an actor, called after processing frame
void ActorManager::removeActor(Actor* a) {
	// Iterate over the vector, looking for the actor
	for (int i = 0; i < actorVec.size(); i++) {
		if (actorVec[i] == a) {
			actorVec.erase(actorVec.begin() + i);
			a->setManager(nullptr); // tell actor that manager no longer owns it
			
			// if a is an enemy, keep it in the enemy pool
			Tank* aTank = dynamic_cast<Tank*>(a);
			if (aTank && a != player) {
				enemyPool.push_back(aTank);
			}

			return;
		}
	}
}

void ActorManager::spawnPlayer() {
	player = new FireTank;
	player->setController(new PlayerController());
	player->setPosition(Vector3(15, 1.5f, 15));
	player->setTeam(&redTeam);
	addActor(player);
}
void ActorManager::spawnEnemy() {

	// Get our enemy from the pool of old enemies, or make a new one
	Tank* enemy = nullptr;
	if (enemyPool.size() > 0) {
		enemy = enemyPool[0];
		enemyPool.erase(enemyPool.begin());
	}
	else {
		enemy = new RushTank;
		enemy->setController(new AIController());
	}
		
	enemy->setHealth(enemy->getMaxHealth()); // reset health
	enemy->setTeam(&greenTeam);
	addActor(enemy);

	// Pick a random positions for the enemy until the spawn point is valid
	do {

		float randomAngle = ((float)rand() / RAND_MAX) * (2 * PI); // Calculate a random angle
		Vector3 enemyDistance = Vector3RotateByAxisAngle(Vector3(ENEMY_SPAWN_DISTANCE, 0, 0), Vector3(0, 1, 0), randomAngle);
		enemy->setPosition(Vector3Add(enemyDistance, player->getPosition()));
	} while (!isValidSpawn(enemy));
}
// Function to check if an enemy's spawnpoint is valid
bool ActorManager::isValidSpawn(Tank* t) {
	// Check spawn point is clear
	if (t->getOverlappingActors().size() > 0)
		return false;
	// Check spawn point is in bounds
	Vector3 position = t->getPosition();
	if (position.x > WORLD_MAX_X || position.x < WORLD_MIN_X)
		return false;
	if (position.z > WORLD_MAX_Z || position.z < WORLD_MIN_Z)
		return false;

	return true;
}



// Get function for wallMap
std::vector<std::vector<int>> ActorManager::getWallMap() {
	return wallMap;
}

Tank* ActorManager::getPlayer() {
	return player;
}


// Functions called every frame

// Call process for every actor in vector
void ActorManager::processFrame() {
	std::vector<Actor*> actors = actorVec; // make a copy of actorVec, so that it can be changed during process
	for (Actor* a : actors) {
			a->process();
	}
}
// Call update overlaps for every actor in vector
void ActorManager::updateOverlaps() {
	for (Actor* a : actorVec) {
			a->updateOverlaps();
	}
}
// Call remove every actor that shouldve been removed this frame
void ActorManager::removeActors() {
	for (Actor* a : removeQueue)
		if (a->getManager() == this) {
			removeActor(a);
		}
	removeQueue.clear();
}
// Call draw for every actor in vector, must happen after BeginDrawMode3D(Camera)
void ActorManager::drawFrame() {
	for (Actor* a : actorVec) {
		a->draw();
	}
}

// Destructor deletes all of the actors 
ActorManager::~ActorManager() {
	for (Actor* a : actorVec) {
		delete a;
	}
	for (Tank* t : enemyPool) {
		delete t;
	}
	delete player;
}

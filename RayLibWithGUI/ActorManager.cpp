// Implementation file for actor manager
// Contains a vector of actors and calls their process and draw functions every frame

#include "ActorManager.h"
#include "Actor.h" // Actor is included here to get around circular inclusion
#include "Wall.h" 
#include "FireTank.h";
#include "PlayerController.h"
#include "AIController.h"

// Constructor function initializes actors
ActorManager::ActorManager() {


	
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
			delete a;
			
			return;
		}
	}
}

// Get function for wallMap
std::vector<std::vector<int>> ActorManager::getWallMap() {
	return wallMap;
}



// Functions called every frame

// Call process for every actor in vector
void ActorManager::processFrame() {
	for (Actor* a : actorVec) {
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

// Destructor removes all of the actors 
ActorManager::~ActorManager() {
	for (Actor* a : actorVec) {
		removeActor(a);
	}
}

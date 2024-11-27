// Implementation file for actor manager
// Contains a vector of actors and calls their process and draw functions every frame

#include "ActorManager.h"
#include "Actor.h" // Actor is included here to get around recursive #includes

// Adding and removing actor functions

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
// Function to remove an actor
void ActorManager::removeActor(Actor* a) {
	// Iterate over the vector, looking for the actor
	for (int i = 0; i < actorVec.size(); i++) {
		if (actorVec[i] == a) {
			actorVec.erase(actorVec.begin() + i);
			a->setManager(nullptr); // tell actor that manager no longer owns it
			return;
		}
	}
}

int ActorManager::getScore() {
	return score;
}

void ActorManager::incrementScore() {
	score += 1;
}


// Functions called every frame

// Call process for every actor in vector
void ActorManager::processFrame() {
	std::vector<Actor*> actors = actorVec; // duplicate the vector in case it changes
	for (Actor* a : actors) {
		if (a->belongsToManager(this)) // check if a has been removed, if it has don't process it
			a->process();
	}
}
// Call update overlaps for every actor in vector
void ActorManager::updateOverlaps() {
	std::vector<Actor*> actors = actorVec; // duplicate the vector in case it changes
	for (Actor* a : actors) {
		if (a->belongsToManager(this)) // check if a has been removed, if it has don't update it
			a->updateOverlaps();
	}
}
// Call erase for each actor that an erase was queued for
void ActorManager::removeActors() {
	for (Actor* a : removeQueue)
		if (a->getManager() == this)
			removeActor(a);
	removeQueue.clear();
}
// Call draw for every actor in vector
void ActorManager::drawFrame() {
	for (Actor* a : actorVec) {
		a->draw();
	}
}


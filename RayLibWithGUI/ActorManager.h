// Class definition for actor manager
// Contains vector of all actors Calls process and draw functions for each actor

#include <vector>

class Actor; // tell it actors exist, Actor.h is included in implementation

#ifndef ACTORMANAGER_H
#define ACTORMANAGER_H

class ActorManager {
private:
	// Stores all actors
	std::vector<Actor*> actorVec;
	std::vector<Actor*> removeQueue;
	int score = 0;

public:
	// Functions to get, add, and remove actors
	std::vector<Actor*> getActors();
	void addActor(Actor* a);
	void queueRemoveActor(Actor* a);
	void removeActor(Actor* a);

	int getScore();
	void incrementScore();

	// Functions called every frame
	void processFrame();
	void updateOverlaps();
	void removeActors();
	void drawFrame();

};



#endif

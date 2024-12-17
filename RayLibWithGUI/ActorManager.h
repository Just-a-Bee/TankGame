// Class definition for actor manager
// Contains vector of all actors Calls process and draw functions for each actor

#include <vector>
#include "Team.h"


class Actor; // tell it actors exist, Actor.h is included in implementation
class Tank;

#ifndef ACTORMANAGER_H
#define ACTORMANAGER_H

class ActorManager {
private:


	// Stores all actors
	std::vector<Actor*> actorVec;
	std::vector<Actor*> removeQueue; // Queue of actors to be removed after processing frame

	Tank* player = nullptr;
	std::vector<Tank*> enemyPool; // Vector of unspawned enemies

	// Actors are given reference to a team, so they know who their allies are
	Team redTeam = Team(RED, MAROON);
	Team greenTeam = Team(GREEN, DARKGREEN);


	// Map of walls. Used to spawn the walls, and for AI pathfinding
	std::vector<std::vector<int>> wallMap = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,0,0,0,1},
	{1,0,0,0,0,1,0,0,0,1},
	{1,0,1,1,1,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
	};

public:
	// Constructor function
	ActorManager();

	// Functions to get, add, and remove actors
	std::vector<Actor*> getActors();
	void addActor(Actor* a);
	void queueRemoveActor(Actor* a);
	void removeActor(Actor* a);

	// More specific functions
	void spawnPlayer();
	void spawnEnemy();
	bool isValidSpawn(Tank*);

	// Set and get functions
	std::vector<std::vector<int>> getWallMap();
	Tank* getPlayer();

	// Functions called every frame
	void processFrame();
	void updateOverlaps();
	void removeActors();
	void drawFrame();

	~ActorManager();

};



#endif

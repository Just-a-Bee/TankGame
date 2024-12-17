// Specification file for actor class
// Base game object Class has process and draw functions called every frame, and interfaces with actor manager


#include <vector>
#include <algorithm>
#include "raylib.h"
#include "raymath.h"
#include "ActorManager.h"
#include "Team.h"

#include <iostream>

#ifndef ACTOR_H
#define ACTOR_H

class Actor {
private:
	Vector3 position = Vector3{ 0,0,0 };
	float size = 0;
	float rotation = 0;

	ActorManager* manager = nullptr; // Reference to actor manager, stores other actors and calls process and draw functions
	Team* team = nullptr; // Reference to actor's team
	std::vector<Actor*> previousOverlaps; // Stores a vector of overlapping actors on previous frame, used to find new overlapping actors

public:
	// Default Constructor
	Actor();

	// Setters and getters
	Vector3 getPosition();
	void setPosition(Vector3);
	float getSize();
	void setSize(float);
	float getRotation();
	void setRotation(float);

	ActorManager* getManager();
	void setManager(ActorManager* m);

	Team* getTeam();
	void setTeam(Team*);

	// Return functions
	Vector3 forwardVector();
	BoundingBox bounds();
	bool belongsToManager(ActorManager*);
	float toValidAngle(float);
	std::vector<Actor*> getOverlappingActors();

	// Called every frame
	virtual void process();
	void updateOverlaps();
	virtual void draw();
	
	// Collision functions
	virtual void beginOverlap(Actor*);
	virtual void endOverlap(Actor*);

	virtual void takeDamage(float);
	void queueRemove();

	virtual  ~Actor() {}

};

#endif

// Specification file for tank actor
// Drawn with a mesh, can move and fire


#include "Actor.h"
#include "Wall.h"
#include "GameData.h"
class TankController; // Declare class to avoid recursive inclusions

#ifndef TANK_H
#define TANK_H



class Tank : public Actor {
private:
	// 3D objects
	Mesh mesh;
	Model model;
	// Speed vars
	float rotateSpeed = 80;
	float moveSpeed = 12;
	// Health vars
	float health = 10;
	float collideDamage = 10;
	// Controller
	TankController* controller = nullptr;

public:
	// Constructor function
	Tank();

	// Set and get functions
	void setRotateSpeed(float);
	float getRotateSpeed();
	void setMoveSpeed(float);
	float getMoveSpeed();
	void setHealth(float);
	float getHealth();
	void setCollideDamage(float);
	float getCollideDamage();
	void setController(TankController*);
	TankController* getController();

	// Called every frame
	virtual void process();
	void draw();

	void beginOverlap(Actor* a);

	// Function to move based on track directions
	void move(float leftTrack, float rightTrack);

	// Damage function reduces health
	void takeDamage(float);


	
};



#endif
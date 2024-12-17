// Specification file for play state class, this is the state the actual game runs in
// Initializes game state, stores and moves the camera, handles spawning of enemy actors
// Each frame: processes changes for actors, then draws the actors and the hud

#include "State.h"
#include "Wall.h"
#include "PlayerController.h"
#include "AIController.h"
#include "GameData.h"
#include "Constants.h"

#ifndef PLAYSTATE_H
#define PLAYSTATE_H




class PlayState : public GameState
{

private:

	
	// Game objects
	ActorManager* actorManager = new ActorManager; // Actor manager contains all game Actors
	Camera3D camera; // Camera is used to draw the 3D environment

	// Game variables
	bool isPaused = false;
	float runtime = 0;
	float spawnTimer = .1;
	float spawnTimerMax = 1;
	float gameOverTime = 3;

	GameData* gameData = GameData::getInstance(); // Reference to the GameData singleton

	// Private functions
	Camera3D setupCamera();
	void moveCamera(Camera& camera, Tank* player);
	void drawHud();
	void togglePause();


public:
	// Enter and exit functions
	void enterState();
	void exitState();

	// Functions called every frame
	void nextFrame();
	GameState* shouldChangeTo();
	


};


#endif
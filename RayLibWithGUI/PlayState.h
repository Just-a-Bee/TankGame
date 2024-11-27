// Specification file for play state class
// Draws each frame of the game, spawns enemies, processes actors, handles collisions


#include "State.h"
#include "Wall.h"
#include "PlayerController.h"
#include "GameData.h"

#ifndef PLAYSTATE_H
#define PLAYSTATE_H

class PlayState : public GameState
{

private:

	const float CAMERA_DISTANCE = 3;
	const float CAMERA_HEIGHT = 55;

	const float ENEMY_SPAWN_DISTANCE = 30;

	ActorManager actorManager;
	Camera3D camera;

	Team redTeam = Team("Red", RED, MAROON);
	Team greenTeam = Team("Green", GREEN, DARKGREEN);

	Tank* player = nullptr;

	float runtime = 0;
	float spawnTimer = .1;
	float spawnTimerMax = 1;
	
	float gameOverTime = 3;


	Camera3D setupCamera();
	void moveCamera(Camera& camera, Tank* player);
	float randomFloat(float, float);
	void spawnEnemy();

public:
	
	

	void enterState();
	void nextFrame();
	GameState* shouldChangeTo();
	void exitState();


};


#endif
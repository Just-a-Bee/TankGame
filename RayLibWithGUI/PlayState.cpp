// Play state implementation

#include "PlayState.h"
#include "OverState.h" // Included here to prevent recursive inclusion


// Function called when the state is entered, initialize all game objects
void PlayState::enterState() {
	// Define the camera
	camera = setupCamera();

	// Set up actors and add them to manager
	player = new FireTank;
	player->setController(new PlayerController());
	player->setTeam(&redTeam);
	actorManager.addActor(player);

}



// Function called to render the next frame of the game
void PlayState::nextFrame() {

	// Increment runtime
	runtime += GetFrameTime();

	// Handle enemy spawning
	spawnTimer -= GetFrameTime();
	if (spawnTimer <= 0) {
		spawnTimer = spawnTimerMax;
		spawnEnemy();
	}

	// Update the actor data for the frame
	actorManager.processFrame();
	actorManager.updateOverlaps();
	actorManager.removeActors();

	moveCamera(camera, player); // Move the camera

	if (!player->belongsToManager(&actorManager))
		gameOverTime -= GetFrameTime();

	// Begin drawing in 3D
	BeginDrawing();
	ClearBackground(RAYWHITE);
	BeginMode3D(camera);

	// Draw the floor
	DrawGrid(100, 10);

	actorManager.drawFrame();

	// Stop drawing in 3D
	EndMode3D();

	char score[6];
	_itoa_s(actorManager.getScore(), score, 10);
	DrawText(score, 350, 40, 20, BLACK);

	// Do any 2D drawing

	EndDrawing();
}


// Function to spawn a new enemy
void PlayState::spawnEnemy() {
	Tank* enemy = new RushTank;
	enemy->setTeam(&greenTeam);


	// Pick a random position for the enemy
	Vector3 enemyDistance = Vector3RotateByAxisAngle(Vector3(ENEMY_SPAWN_DISTANCE, 0, 0), Vector3(0, 1, 0), randomFloat(0, 2 * PI));
	enemy->setPosition(Vector3Add(enemyDistance, player->getPosition()));

	enemy->setController(new AIController());
	actorManager.addActor(enemy);
}




// function to return a random float within a range
float PlayState::randomFloat(float min, float max) {
	return ((float)rand() / RAND_MAX) * (max - min) + min;
}

// Function to return the camera object with all values set
Camera3D PlayState::setupCamera() {
	Camera3D camera = { 0 };
	camera.position = Vector3Zero(); // Camera position
	camera.target = Vector3Zero();      // Camera looking at point
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
	return camera;
}

// Function to move the camera to follow player
void PlayState::moveCamera(Camera& camera, Tank* player) {
	Vector3 playerDir = player->forwardVector(); // Get the players facing direction
	camera.position = Vector3Add(player->getPosition(), Vector3Scale(playerDir, -CAMERA_DISTANCE)); // Place the camera behind the player by distance
	camera.position = Vector3Add(camera.position, Vector3(0, CAMERA_HEIGHT, 0)); // Offset the camera by CAMERA_HEIGHT
	camera.target = Vector3Add(player->getPosition(), Vector3(0, 1, 0)); // target a point just above the player
}

GameState* PlayState::shouldChangeTo() {
	if (gameOverTime <= 0) {
		return new OverState;
	}
	return nullptr;
}


// When we exit the state, save the high score
void PlayState::exitState() {
	GameData* data = GameData::getInstance();
	if (actorManager.getScore() > data->getHighScore())
		data->setHighScore(actorManager.getScore());

}
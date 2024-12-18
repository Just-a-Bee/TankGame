// Play state implementation

#include "PlayState.h"
#include "OverState.h" // Included here to prevent self inclusion




// Function called when the state is entered, initialize all game objects
void PlayState::enterState() {
	// Reset game data score
	gameData->setScore(0);
	// Define the camera
	camera = setupCamera();

}



// Function called to render the next frame of the game
void PlayState::nextFrame() {

	// If pause button is pressed, toggle if the game is paused
	if ((IsKeyPressed(KEY_P)) || (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT))) {
		togglePause();
	}

	// Process the game only when it isn't paused
	if (!isPaused) {
		// Increment runtime
		runtime += GetFrameTime();

		// Handle enemy spawning
		spawnTimer -= GetFrameTime();
		if (spawnTimer <= 0) {
			spawnTimer = spawnTimerMax;
			actorManager->spawnEnemy();
		}

		// Update the actor data for the frame
		actorManager->processFrame();
		actorManager->updateOverlaps();
		actorManager->removeActors();

		moveCamera(camera, actorManager->getPlayer()); // Move the camera

		// If the player has died
		if (!actorManager->getPlayer()->belongsToManager(actorManager))
			gameOverTime -= GetFrameTime();
	}
	
	// Always draw the frame

	// Begin drawing in 3D
	BeginDrawing();
	ClearBackground(RAYWHITE);
	BeginMode3D(camera);

	// Draw the floor
	DrawGrid(100, 10);

	actorManager->drawFrame();

	// Stop drawing in 3D
	EndMode3D();

	// Draw the HUD in 2D
	drawHud();

	EndDrawing();
}


// Function to draw the HUD for the game
void PlayState::drawHud() {
	// Draw Score
	DrawText(TextFormat("Score: %i", gameData->getScore()), 680, 360, 20, BLACK);
	
	// Draw health bar
	DrawText("Health:", 700, 380, 20, RED);
	int drawX = 750;
	Color barColor = RED;
	for (int i = 0; i < 10; i++) {
		if (i >= actorManager->getPlayer()->getHealth()) // If the bar we're drawing is > current health, draw it unfilled
			barColor = GRAY;
		DrawRectangle(drawX, 410, 15, 30, barColor);
		drawX -= 20;
	}

	if (isPaused) {
		DrawText("Press P to unpause", 350, 300, 20, BLACK);
	}

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

// If player has been dead for gameOverTime, return OverState
GameState* PlayState::shouldChangeTo() {
	if (gameOverTime <= 0) {
		return new OverState;
	}
	return nullptr;
}

// Function to toggle if the game is paused
void PlayState::togglePause() {
	isPaused = !isPaused;
}


// When we exit the state, save the high score
void PlayState::exitState() {
	if (gameData->getScore() > gameData->getHighScore())
		gameData->setHighScore(gameData->getScore());
	delete actorManager;
}
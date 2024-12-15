// Things to add
	
//Pre submission todo
	// Make maze bigger
	// Code cleanup
	// Move AStar into AIcontroller
	// Get rid of team? Or simplify it at least
	// Could just be an enum
	
// Future Todo
	// More enemies
	// Upgrades

// Things to talk about in the video
	// GameState uses the state pattern
	// Menu uses the command pattern
	// GameData uses the singleton pattern
	// Tanks' bullets use the object pool pattern
	

#include "raylib.h"

#include "TitleState.h"

// screen size
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;

// camera consts
const float CAMERA_DISTANCE = 3;
const float CAMERA_HEIGHT = 55;

int main(void) {

	// Open window
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Game");
	SetTargetFPS(60);

	// Declare the curretn state, start in MenuState
	GameState* currentState = new TitleState;
	currentState->enterState(); // Call the state's enter function

	// Main game loop, called every frame
	while (!WindowShouldClose()) {
		currentState->nextFrame(); // Tell current state to process and render the next frame
		GameState* changeState = currentState->shouldChangeTo(); // Ask if the state should be changed
		if (changeState) { // change to changeState is it has a value
			currentState->exitState();
			changeState->enterState();
			currentState = changeState;
		}
	}

	return 0;
}

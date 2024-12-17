// Main.cpp runs a state machine of GameStates
// Each frame the state's "nextFrame()" is called



// Future Todo
	// More enemies
	// Upgrades


#include "raylib.h"

#include "TitleState.h"
#include "Constants.h"
#include "GameData.h"

int main(void) {

	// Open window
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tank Game");
	SetTargetFPS(60);

	// Declare the current state, start in TitleState
	GameState* currentState = new TitleState;
	currentState->enterState(); // Call the state's enter function

	// Main game loop, called every frame
	while (!WindowShouldClose()) {
		currentState->nextFrame(); // Tell current state to process and render the next frame
		GameState* changeState = currentState->shouldChangeTo(); // Ask if the state should be changed
		if (changeState) { // Change to changeState if it has a value
			currentState->exitState();
			delete currentState;
			changeState->enterState();
			currentState = changeState;
		}
	}

	// Deallocate pointers
	delete currentState;
	delete GameData::getInstance(); // Singleton needs to be deleted

	return 0;
}

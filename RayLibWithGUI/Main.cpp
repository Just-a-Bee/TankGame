// Things to add

	//Upgrades
	//Make menuState into its own class, mainMenu and gameOver both inherit it
	//Make menu look good
	//AStar pathfinding for aicontroller
	//Move tankControllers to their own files probably
	//Make a consts file that classes can import?
	//Implement builder pattern for Tank construction?
	//	More enemies

// Things to talk about in the video
	// GameState uses the state pattern
	// Menu uses the command pattern
	// GameData uses the singleton pattern
	// Tanks' bullets use the object pool pattern
	
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define RAYGUI_IMPLEMENTATION

#include "raylib.h"                 //Main Raylib core library
#include "raymath.h"                //Raylib Math functions library
#include "rlgl.h"                   //RayLib OpenGL library

// Include classes
#include "MenuState.h"

#include <assert.h>

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
	GameState* currentState = new MenuState;
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

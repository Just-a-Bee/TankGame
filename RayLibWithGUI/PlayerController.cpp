// Implementation file for PlayerController Class
// Allows user input to control a Tank


#include "PlayerController.h"

// Called every frame by controlledTank
void PlayerController::process() {
	
	mode = updateInputMode(); // Update the input mode based on if keyboard or controller input is detected

	// Get the player inputs
	float leftTrack = 0;
	float rightTrack = 0;
	bool isFiring = false;
	if (mode == KEYBOARD) // Get input based on current mode
		getKeyboardInput(leftTrack, rightTrack, isFiring);
	else
		getGamepadInput(leftTrack, rightTrack, isFiring);

	// Call move, using player inputs
	getControlledTank()->move(leftTrack, rightTrack);

	// Do firing only if controlled tank can fire
	FireTank* controlledAsFireTank = dynamic_cast<FireTank*>(getControlledTank());
	if (controlledAsFireTank)
		if (isFiring)
			controlledAsFireTank->fire();
}

// Function to update the current input mode based on what input method is used
InputMode PlayerController::updateInputMode() {
	// Check if a keyboard input is pressed
	for (KeyboardKey k : keyboardInputs) {
		if (IsKeyDown(k))
			return KEYBOARD;
	}
	// Check if a gamepad input, or gamepad axis is pressed
	for (GamepadButton b : gamepadInputs) {
		if (IsGamepadButtonDown(gamepad, b))
			return GAMEPAD;
	}
	if ((GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) > stickDeadzone) ||
		(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y) > stickDeadzone))
		return GAMEPAD;
	// Else, return current mode
	return mode;
}

// Function to get input from the keyboard
void PlayerController::getKeyboardInput(float& leftTrack, float& rightTrack, bool& isFiring) {
	// Set left track
	leftTrack += IsKeyDown(KEY_Q) ? 1 : 0;
	leftTrack += IsKeyDown(KEY_A) ? -1 : 0;
	// Set right track
	rightTrack += IsKeyDown(KEY_E) ? 1 : 0;
	rightTrack += IsKeyDown(KEY_D) ? -1 : 0;

	// Set firing input
	if (IsKeyDown(KEY_W))
		isFiring = true;
}
// Function ot get input from gamepad
void PlayerController::getGamepadInput(float& leftTrack, float& rightTrack, bool& isFiring) {
	// Set tracks based on stick input
	leftTrack = -GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y);
	rightTrack = -GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y);

	// If movement is below deadzone, dont move
	leftTrack = (abs(leftTrack) < stickDeadzone) ? 0 : leftTrack;
	rightTrack = (abs(rightTrack) < stickDeadzone) ? 0 : rightTrack;

	// Set firing input
	if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_2) || IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_2))
		isFiring = true;

}
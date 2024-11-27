
#include "PlayerController.h"

// Child class overrides
void PlayerController::process() {

	mode = updateInputMode();
	float leftTrack = 0;
	float rightTrack = 0;
	bool isFiring = false;

	if (mode == KEYBOARD)
		getKeyboardInput(leftTrack, rightTrack, isFiring);
	else
		getGamepadInput(leftTrack, rightTrack, isFiring);

	// Call move
	getControlledTank()->move(leftTrack, rightTrack);

	// Do firing only if controlled tank can fire
	FireTank* controlledAsFireTank = dynamic_cast<FireTank*>(getControlledTank());
	if (controlledAsFireTank)
		if (isFiring)
			controlledAsFireTank->fire();
}

// Function to update the current input mode based on what input method is used
InputMode PlayerController::updateInputMode() {
	for (KeyboardKey k : keyboardInputs) {
		if (IsKeyDown(k))
			return KEYBOARD;
	}
	for (GamepadButton b : gamepadInputs) {
		if (IsGamepadButtonDown(gamepad, b))
			return GAMEPAD;
	}
	if ((GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) > stickDeadzone) ||
		(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y) > stickDeadzone))
		return GAMEPAD;
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

	if (IsKeyDown(KEY_W))
		isFiring = true;
}
void PlayerController::getGamepadInput(float& leftTrack, float& rightTrack, bool& isFiring) {
	// Set tracks based on stick input
	leftTrack = -GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y);
	rightTrack = -GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y);

	// If movement is below deadzone, dont move
	leftTrack = (abs(leftTrack) < stickDeadzone) ? 0 : leftTrack;
	rightTrack = (abs(rightTrack) < stickDeadzone) ? 0 : rightTrack;

	if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_2) || IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_2))
		isFiring = true;

}
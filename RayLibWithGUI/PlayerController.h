// Player controller moves the tank based on input

#include "TankController.h"

#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

enum InputMode {
	KEYBOARD = 0,
	GAMEPAD = 1
};

const float stickDeadzone = 0.1f;
const KeyboardKey keyboardInputs[] = { KEY_Q, KEY_A, KEY_E, KEY_D, KEY_W };
const GamepadButton gamepadInputs[] = { GAMEPAD_BUTTON_LEFT_TRIGGER_2, GAMEPAD_BUTTON_RIGHT_TRIGGER_2 };

class PlayerController : public TankController {
private:

	InputMode mode = KEYBOARD;
	int gamepad = 0;

	InputMode updateInputMode();
	void getKeyboardInput(float&, float&, bool&);
	void getGamepadInput(float&, float&, bool&);

public:
	void process();
};

#endif
// Menu State implementation

#include "MenuState.h"

// Set functions
void MenuState::setPlayPressed(bool b) {
	isPlayPressed = b;
}
void MenuState::setQuitPressed(bool b) {
	isQuitPressed = b;
}

// When menu state is entered, create buttons
void MenuState::enterState() {
	buttonVec.push_back(Button(new PlayCommand(this), Vector2{ 10, 10 }, Vector2{ 100,100 }, "Play"));
	buttonVec.push_back(Button(new QuitCommand(this), Vector2{ 200, 200 }, Vector2{ 100,100 }, "Quit"));
}
// Next frame function draws buttons and handles clicking
void MenuState::nextFrame() {

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		handleMouseClick();

	BeginDrawing();
	ClearBackground(RAYWHITE);


	for (Button b : buttonVec)
		b.draw();

	EndDrawing();
}

// When a mouse click happens, check if a button was clicked
void MenuState::handleMouseClick() {

	Vector2 mousePos = GetMousePosition();

	// Iterate over the buttons, determining which ones the mouse is over
	for (Button& b : buttonVec) {
		Vector2 buttonPos = b.getPosition();
		Vector2 buttonEnd = Vector2Add(buttonPos, b.getSize());
		// If mouse is past top left corner
		if ((mousePos.x - buttonPos.x > 0) && (mousePos.y - buttonPos.y > 0)) {
			// If mouse is before bottom right corner
			if ((mousePos.x - buttonEnd.x < 0) && (mousePos.y - buttonEnd.y < 0)) {

				// If mouse is clicked, depress the button
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					b.setDepressed(true);
				}
				// If mouse is released, and button is depressed, button has been released
				else if (b.isDepressed()) {
					b.press();
				}
			}
		}
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			b.setDepressed(false);
	}
}




// Should change to returns the play state if play was pressed
GameState* MenuState::shouldChangeTo() {
	if (isQuitPressed)
		CloseWindow();
	if (isPlayPressed)
		return new PlayState;
	else
		return nullptr;
}
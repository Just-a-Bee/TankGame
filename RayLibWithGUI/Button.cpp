
#include "Button.h"


// Constructor functions
Button::Button() {};
Button::Button(Command* c, Vector2 pos, Vector2 s, std::string n) {
	pressCommand = c;
	position = pos;
	size = s;
	name = n;
}

// Set and get vars
void Button::setPosition(Vector2 p) {
	position = p;
}
Vector2 Button::getPosition() {
	return position;
}
void Button::setSize(Vector2 s) {
	size = s;
}
Vector2 Button::getSize() {
	return size;
}
void Button::setDepressed(bool d) {
	depressed = d;
}
bool Button::isDepressed() {
	return depressed;
}

// Press function calls funcPtr
void Button::press() {
	pressCommand->execute();
}

// Draw function draws it on the screen
void Button::draw() {
	Color drawColor = GRAY;
	if (depressed)
		drawColor = DARKGRAY;
	DrawRectangle(position.x, position.y, size.x, size.y, drawColor);
	DrawRectangleLines(position.x, position.y, size.x, size.y, DARKGRAY);
	DrawText(name.c_str(), position.x + size.x / 2, position.y + size.y / 2, 10, BLACK); // Display text in center of button

}
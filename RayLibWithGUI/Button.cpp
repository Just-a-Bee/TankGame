
#include "Button.h"


// Constructor functions
Button::Button() {};
// ugh this constructor is massive
Button::Button(Command* c, Vector2 pos, Vector2 s, std::string t, Color col, Color darkCol, Color textCol, int fontSi) {
	pressCommand = c;
	position = pos;
	size = s;
	text = t;
	color = col;
	darkColor = darkCol;
	textColor = textCol;
	fontSize = fontSi;
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
	// If button is depressed, the body is drawn as dark
	Color drawColor = color;
	if (depressed)
		drawColor = darkColor;
	
	// Draw the body
	DrawRectangle(position.x, position.y, size.x, size.y, drawColor);
	DrawRectangleLines(position.x, position.y, size.x, size.y, darkColor);
	
	// Calculate position of text to display it centered
	Vector2 textPos = Vector2{ position.x + size.x / 2, position.y + size.y / 2 };
	textPos.x -= MeasureText(text.c_str(), fontSize)/2;
	textPos.y -= fontSize/2;
	DrawText(text.c_str(), textPos.x, textPos.y, fontSize, textColor);

}
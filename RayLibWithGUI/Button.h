// Specification file for button class
// Has a 2D position to be drawn on screen, and stores a pointer to a function
// When clicked it calls its function

#include "raylib.h"
#include <string>
#include "MenuCommands.h"


#ifndef BUTTON_H
#define BUTTON_H

class Button {
private:
	
	Command* pressCommand = nullptr;
	Vector2 position = Vector2{0,0};
	Vector2 size = Vector2{0,0};
	std::string text = "none";
	
	Color color = RED;
	Color darkColor = MAROON;
	Color textColor = BLACK;
	int fontSize = 10;

	bool depressed = false;

public:
	// Constructor functions
	Button();
	Button(Command*, Vector2, Vector2, std::string, Color, Color, Color, int);

	// Set and get functions
	void setPosition(Vector2);
	Vector2 getPosition();
	void setSize(Vector2);
	Vector2 getSize();
	void setDepressed(bool);
	bool isDepressed();

	// Function for when button is pressed
	void press();

	// Draw function draws it on the screen
	void draw();

};



#endif
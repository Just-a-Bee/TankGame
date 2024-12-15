// TitleState extends MenuState, has play and quit buttons, displays title screen of game


#include "MenuState.h"
#ifndef TITLESTATE_H
#define TITLESTATE_H

class TitleState : public MenuState {
public:

	// When the state is entered, initialize buttons
	void enterState() {
		addButton(Button(new PlayCommand(this), Vector2{ 330, 150 }, Vector2{ 140,80 }, "Play", GREEN, DARKGREEN, BLACK, 15));
		addButton(Button(new HowToCommand(this), Vector2{ 330, 250 }, Vector2{ 140,80 }, "How to Play", GRAY, DARKGRAY, BLACK, 15));
		addButton(Button(new QuitCommand(this), Vector2{ 330, 350 }, Vector2{ 140,80 }, "Quit", RED, MAROON, BLACK, 15));
	}

	// Draw BG function called before buttons are draw
	void drawBG() {
		// Draw the title of the game
		int titleTextX = 400;
		titleTextX -= MeasureText("TITLE", 20) / 2;
		DrawText("TITLE", titleTextX, 100, 20, BLACK);
	}

};

#endif
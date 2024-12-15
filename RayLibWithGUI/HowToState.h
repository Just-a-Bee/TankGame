// Specification file for HowToState
// Displays how to play information, and has a button to go back to TitleState

#include "MenuState.h"
#ifndef HOWTOSTATE_H
#define HOWTOSTATE_H

class HowToState : public MenuState {
public:

	// When the state is entered, initialize buttons
	void enterState() {
		addButton(Button(new TitleCommand(this), Vector2{ 330, 350 }, Vector2{ 140,80 }, "Back", GREEN, DARKGREEN, BLACK, 15));
	}

	// Draw BG function called before buttons are drawn
	void drawBG() {
		DrawRectangle(0, 0, 800, 450, Color(40, 40, 40, 180));
		DrawRectangle(30, 30, 740, 390, Color(230, 230, 230, 255));
		DrawText("How to Play:", 40, 40, 20, BLACK);
		DrawText("Maneuver your tank to avoid enemy tanks", 50, 70, 20, BLACK);
		DrawText(" - Control your left track with Q/A or the left stick", 50, 100, 20, BLACK);
		DrawText(" - Control your right track with E/D or the right stick", 50, 130, 20, BLACK);

		DrawText("Movment Tips:", 50, 160, 20, BLACK);
		DrawText(" - Move both tracks forward to go straight", 50, 190, 20, BLACK);
		DrawText(" - Move tracks in opposite directions to turn on the spot", 50, 220, 20, BLACK);
		DrawText(" - Moving one track will steer you in the opposite direction", 50, 250, 20, BLACK);
		DrawText("Fire with W or RT to destroy enemy tanks", 50, 280, 20, BLACK);

	}

};

#endif
// Specification file for game over state

#include "MenuState.h"
#include "GameData.h"

#ifndef OVERSTATE_H
#define OVERSTATE_H

class OverState : public MenuState {

public:
	void enterState() {
		addButton(Button(new PlayCommand(this), Vector2{ 330, 160 }, Vector2{ 140,80 }, "Play Again", GREEN, DARKGREEN, BLACK, 15));
		addButton(Button(new TitleCommand(this), Vector2{ 330, 260 }, Vector2{ 140,80 }, "Back to Title", YELLOW, ORANGE, BLACK, 15));
		addButton(Button(new QuitCommand(this), Vector2{ 330, 360 }, Vector2{ 140,80 }, "Quit", RED, MAROON, BLACK, 15));
	}
	void drawBG() {
		DrawText(TextFormat("You Scored: %i", GameData::getInstance()->getScore()), 330, 20, 30, BLACK);
		DrawText(TextFormat("High Score: %i", GameData::getInstance()->getHighScore()), 330, 100, 30, BLACK);
	}


};



#endif
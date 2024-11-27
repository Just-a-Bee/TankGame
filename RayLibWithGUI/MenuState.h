// Specification file for Menu State
// Instances buttons which use the command pattern to execute their behavior
// When play is pressed, changes to play
// When quit is pressed, quits the game


#include "State.h"
#include "PlayState.h"

#ifndef MENUSTATE_H
#define MENUSTATE_H

class MenuState : public GameState
{

private:
	//Boolean flags
	bool isPlayPressed = false;
	bool isQuitPressed = false;

	std::vector<Button> buttonVec; // Stores the buttons

public:

	// Set and get functions
	void setPlayPressed(bool);
	void setQuitPressed(bool);

	// Functions called from Main
	void enterState();
	void nextFrame();
	GameState* shouldChangeTo();

	// Function to handle mouse clicking on buttons
	void handleMouseClick();

};

#endif
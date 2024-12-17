// Specification file for Menu State
// Instances buttons which use the command pattern to execute their behavior
// When play is pressed, changes to play
// When quit is pressed, quits the game


#include "State.h"
#include "PlayState.h"

#ifndef MENUSTATE_H
#define MENUSTATE_H
// Specification file for menu state class
// Has a vector of Buttons to draw each frame, and handles mouse clicking on buttons
// Has a "returnState" pointer that is returned by shouldChangeTo()

class MenuState : public GameState
{

private:
	std::vector<Button> buttonVec; // Stores the buttons
	bool shouldClose = false;
	GameState* returnState = nullptr;

	// Function to handle mouse clicking on buttons
	void handleMouseClick();

public:
	// Set functions
	void addButton(Button);
	void setShouldClose(bool);
	void setReturnState(GameState*);


	// Functions called from Main
	virtual void enterState(); // Called when we enter the state
	void nextFrame();
	GameState* shouldChangeTo();
	void exitState(); // Called when we leave state

	virtual void drawBG() {}; // Draw bg function called in nextFrame, used to draw background of menu


	
};

#endif
// Class definition for the game state class
// A game state is called render the next frame, every frame depending on which one is active
// When the state should change, shouldChangeTo() returns the state that should become active

#include "Actor.h"
#include "FireTank.h"
#include "TankController.h"
#include "ActorManager.h"
#include "Team.h"
#include "RushTank.h"
#include "Button.h"
#include "MenuCommands.h"

#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState
{
public:

	virtual void enterState();
	virtual void nextFrame();
	virtual GameState* shouldChangeTo();
	virtual void exitState();

};

#endif


// Specification file for game over state

#include "MenuState.h"
#include "GameData.h"

#ifndef OVERSTATE_H
#define OVERSTATE_H

class OverState : public GameState {

public:
	void enterState();
	void nextFrame();
	GameState* shouldChangeTo();

};



#endif
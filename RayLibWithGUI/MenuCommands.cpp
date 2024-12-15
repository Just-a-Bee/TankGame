

#include "MenuCommands.h"
#include "MenuState.h"
#include "TitleState.h"
#include "HowToState.h"

void Command::setMenu(MenuState* m) {
	menu = m;
}
MenuState* Command::getMenu() {
	return menu;
}
void Command::execute() {};

void PlayCommand::execute() {
	getMenu()->setReturnState(new PlayState);
};

void TitleCommand::execute() {
	getMenu()->setReturnState(new TitleState);
}
void QuitCommand::execute() {
	getMenu()->setShouldClose(true);
}
void HowToCommand::execute() {
	getMenu()->setReturnState(new HowToState);
};
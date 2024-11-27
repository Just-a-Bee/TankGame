

#include "MenuCommands.h"
#include "MenuState.h"

void Command::setMenu(MenuState* m) {
	menu = m;
}
MenuState* Command::getMenu() {
	return menu;
}
void Command::execute() {};



void PlayCommand::execute() {
	getMenu()->setPlayPressed(true);
};
void QuitCommand::execute() {
	getMenu()->setQuitPressed(true);
}
void SettingsCommand::execute() {
	std::cout << "Settings pressed";
};
// Specification file for menu commands
// Comands include play game, settings, and quit
// These commands are held by the buttons, and call stuff within the menu


#ifndef COMMAND_H
#define COMMAND_H



class MenuState; // Declare menuState class to avoid self inclusion

class Command {
private:
	MenuState* menu = nullptr;
public:

	Command() {}
	Command(MenuState* m) {
		menu = m;
	}

	// Get function
	void setMenu(MenuState*);
	MenuState* getMenu();

	// Virtual execute function overridden by child classes
	virtual void execute();
};

class PlayCommand : public Command {
public:
	PlayCommand(MenuState* m) {
		setMenu(m);
	}
	void execute();
};

class TitleCommand : public Command {
public:
	TitleCommand(MenuState* m) {
		setMenu(m);
	}
	void execute();
};

class QuitCommand : public Command {
public: 
	QuitCommand(MenuState* m) : Command(m) {};
	void execute();
};

class HowToCommand : public Command {
public:
	HowToCommand(MenuState* m) : Command(m) {};
	void execute();
};
#endif
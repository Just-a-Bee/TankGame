// Specification for GameData Singleton class, stores info like settings and high scores

#include <iostream>
#include <fstream>

#ifndef GAMEDATA_H
#define GAMEDATA_H

class GameData {
private:
	const char* savePath = ".\saveData.txt"; // Path to save file

	GameData(); // Private constructor only called by getInstance()
	inline static GameData* instance = nullptr; // Static instance returned by getInstance()
	
	// Game data variables
	int score = 0;
	int highScore = 0;

	// Save and load functions
	void saveData();
	void loadData();

public:
	// Function to get access to the singleton
	static GameData* getInstance();

	// Set and get functions
	void setScore(int);
	void incrementScore(int);
	int getScore();
	void setHighScore(int);
	int getHighScore();
};

#endif


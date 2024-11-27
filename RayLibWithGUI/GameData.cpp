
#include "GameData.h"

// Private constructor function
GameData::GameData() {};


// Function to get access to the singleton
GameData* GameData::getInstance() {
	if (instance == nullptr) {
		instance = new GameData();
	}
	return instance;
}

// Set and get functions
void GameData::setHighScore(int s) {
	highScore = s;
}
int GameData::getHighScore() {
	return highScore;
}
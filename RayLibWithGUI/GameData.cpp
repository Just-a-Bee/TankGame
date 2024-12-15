//Implementation file for GameData Singleton class

#include "GameData.h"
#include <string>

// Private constructor function
GameData::GameData() {
	loadData();
};

// Function to save gamedata to the save file
void GameData::saveData() {
	std::ofstream saveFile(savePath);
	saveFile << highScore;
	saveFile.close();
}

// Function to load gamedata from the save file
void GameData::loadData() {
	std::ifstream loadFile(savePath);
	if (!loadFile.eof())
		loadFile >> highScore;
}

// Function to get access to the singleton
GameData* GameData::getInstance() {
	if (instance == nullptr) {
		instance = new GameData();
	}
	return instance;
}


void GameData::setScore(int s) {
	score = s;
}
void GameData::incrementScore(int s) {
	score += s;
}
int GameData::getScore() {
	return score;
}

// Set and get functions
void GameData::setHighScore(int s) {
	highScore = s;
	saveData(); // call save data to save the new high score
}
int GameData::getHighScore() {
	return highScore;
}

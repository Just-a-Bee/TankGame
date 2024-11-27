// Specification for gameData class, stores info like settings and high scores

#ifndef GAMEDATA_H
#define GAMEDATA_H

class GameData {
protected:

	GameData();

	inline static GameData* instance = nullptr;
	
	int highScore = 0;

public:

	// Function to get access to the singleton
	static GameData* getInstance();

	// Set and get functions
	void setHighScore(int);
	int getHighScore();

};



#endif
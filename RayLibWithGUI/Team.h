// Definition for a team struct

#include <string>
#include "raylib.h"

#ifndef TEAM
#define TEAM

struct Team {
	std::string name = "TEAM_NAME";
	Color primaryColor = GRAY;
	Color secondaryColor = DARKGRAY;
	// constructors
	Team() {}

	Team(std::string s, Color t, Color b) {
		name = s;
		primaryColor = t;
		secondaryColor = b;
	}





};

#endif TEAM
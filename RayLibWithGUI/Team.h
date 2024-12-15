// Definition for the Team struct

#include <string>
#include "raylib.h"

#ifndef TEAM
#define TEAM

struct Team {
	Color primaryColor = GRAY;
	Color secondaryColor = DARKGRAY;
	// constructors
	Team() {}

	Team(Color t, Color b) {
		primaryColor = t;
		secondaryColor = b;
	}
};

#endif TEAM
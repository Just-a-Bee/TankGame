// Specification file for wall class
// Wall has a bounding box, and is drawn as a big block in the way
// Tank actors have specific behavior for colliding with a wall, walls dont do anything on their own


#include "Actor.h"


#ifndef WALL_H
#define WALL_H

class Wall : public Actor {
private:
	const int SIZE = 10;
public:
	Wall();
	Wall(int, int);

	BoundingBox bounds();
	void draw();
};

#endif
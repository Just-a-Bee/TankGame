// Implementation file for wall

#include "Wall.h"


Wall::Wall() {};
// Constructor function to place wall at integer positions in the grid
Wall::Wall(int posX, int posY) {
	setPosition(Vector3{ static_cast<float>(posX) * 10 + 5 , 0, static_cast<float>(posY) * 10 + 5 });
}

BoundingBox Wall::bounds() {
	return BoundingBox(Vector3AddValue(getPosition(), -SIZE / 2), Vector3AddValue(getPosition(), SIZE / 2));
}

void Wall::draw() {
	DrawCube(getPosition(), SIZE, SIZE, SIZE, getTeam()->secondaryColor);
}
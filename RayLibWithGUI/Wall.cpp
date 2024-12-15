// Implementation file for wall

#include "Wall.h"


Wall::Wall() {};
// Constructor function to place wall at integer positions in the grid
Wall::Wall(int posX, int posY) {
	setSize(10);
	setPosition(Vector3{ static_cast<float>(posX) * 10 + 5 , 0, static_cast<float>(posY) * 10 + 5 });
}


void Wall::draw() {
	DrawCube(getPosition(), getSize(), getSize(), getSize(), GRAY);
	DrawCubeWires(getPosition(), getSize(), getSize(), getSize(), DARKGRAY);
}
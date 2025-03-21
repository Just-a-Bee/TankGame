// Header file to define powerups
// Each has its own effect that is called upon when it is picked up by player

#include "Actor.h"

#ifndef POWERUP_H
#define POWERUP_H

class PlayerTank;

class Powerup : public Actor {

public:
	float duration = 5;
	Texture2D icon; // Icon shown when powerup is active
	Color color = RED;

	Powerup() {
		Texture2D icon = LoadTexture("Assets/Rapidfire.png");
		setDoBlockingCollisions(false);
		setSize(2);
	}

	// Activate and deactivate functions called by PlayerTank 
	virtual void activate(PlayerTank* p) { std::cout << "Picked up"; };
	virtual void deactivate(PlayerTank* p) { std::cout << "Expired"; };

	void draw() override {
		DrawCube(getPosition(), 1, 1, 1, color);
	}

	~Powerup() {
		UnloadTexture(icon); // unload the icon
	}

};


class RapidFire : public Powerup {

	float originalCooldown = 0;

public:

	RapidFire() {
		color = GREEN;
		icon = LoadTexture("Assets/Rapidfire.png");
	}

	virtual void activate(PlayerTank* p) override;
	virtual void deactivate(PlayerTank* p) override;


};


class SpeedBoost : public Powerup {

	float originalSpeed = 0;
	float originalRotateSpeed = 0;

public:

	SpeedBoost() {
		color = BLUE;
		icon = LoadTexture("Assets/Speedup.png");
	}

	virtual void activate(PlayerTank* p) override;
	virtual void deactivate(PlayerTank* p) override;


};

class MultiShot : public Powerup {

	float originalShots = 0;
	float originalSpread = 0;

public:

	MultiShot() {
		color = RED;
		icon = LoadTexture("Assets/Multishot.png");
	}

	virtual void activate(PlayerTank* p) override;
	virtual void deactivate(PlayerTank* p) override;
};

#endif
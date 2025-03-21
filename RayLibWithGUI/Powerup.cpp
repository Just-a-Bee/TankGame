// Implementation for powerups
// Each has an activate() function that causes its effect
// deactivate() undoes its effect, called when duration expires

#include "Powerup.h"
#include "PlayerTank.h"


void RapidFire::activate(PlayerTank* p) {
	originalCooldown = p->getCooldownMax();
	p->setCooldownMax(.05);

}
void RapidFire::deactivate(PlayerTank* p) {
	p->setCooldownMax(originalCooldown);
}


void SpeedBoost::activate(PlayerTank* p) {
	originalSpeed = p->getMoveSpeed();
	originalRotateSpeed = p->getRotateSpeed();

	p->setMoveSpeed(22);
	p->setRotateSpeed(180);

}

void SpeedBoost::deactivate(PlayerTank* p) {
	p->setMoveSpeed(originalSpeed);
	p->setRotateSpeed(originalRotateSpeed);
}


void MultiShot::activate(PlayerTank* p) {
	originalShots = p->getShotCount();
	originalSpread = p->getShotSpread();

	p->setShotCount(3);
	p->setShotSpread(30);

}

void MultiShot::deactivate(PlayerTank* p) {
	p->setShotCount(originalShots);
	p->setShotSpread(originalSpread);
}

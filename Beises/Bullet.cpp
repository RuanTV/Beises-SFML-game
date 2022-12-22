#include "Bullet.h"

Bullet::Bullet(sf::RenderWindow* window) : Entity(window)
{
	speed = 0.0f;
}

void Bullet::setSpeed(float value)
{
	speed = value;
}

float Bullet::getSpeed() const
{
	return speed;
}

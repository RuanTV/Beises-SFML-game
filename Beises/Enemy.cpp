#include "Enemy.h"

Enemy::Enemy(sf::RenderWindow* window) : Entity(window)
{
	rotate = 0.0f;
	speed = 0.0f;
	kill = false;
}

void Enemy::setSpeed(float value)
{
	speed = value;
}

float Enemy::getSpeed() const
{
	return speed;
}

bool Enemy::getKill() const
{
	return kill;
}

void Enemy::setKill(bool value)
{
	this->kill = value;
}

void Enemy::lookAtPoint()
{
	this->shape.setRotation(0);

	if (this->shape.getPosition().y <= window->getSize().y)
	{
		if (this->shape.getPosition().x <= float(window->getSize().x / 2.0f))
		{
			rotate = float(AngleBetweenTwoVectors(direction, sf::Vector2f(0.0, -1.0)));
			shape.setRotation(rotate);
		}
		if (this->shape.getPosition().x > float(window->getSize().x / 2.0f))
		{
			rotate = float(AngleBetweenTwoVectors(direction, sf::Vector2f(0.0, 1.0)));
			shape.setRotation(rotate + 180);
		}
	}
	else
	{
		if (this->shape.getPosition().x <= float(window->getSize().x / 2.0f))
		{
			rotate = float(AngleBetweenTwoVectors(direction, sf::Vector2f(0.0, -1.0)));
			shape.setRotation(rotate);
		}
		if (this->shape.getPosition().x > float(window->getSize().x / 2.0f))
		{
			rotate = float(AngleBetweenTwoVectors(direction, sf::Vector2f(0.0, 1.0)));
			shape.setRotation(rotate + 180);
		}
	}
}



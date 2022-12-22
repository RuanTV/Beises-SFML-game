#include "Player.h"

#include "GameMath.h"

Player::Player(sf::RenderWindow* window) : Entity(window)
{
	rotate = 0.0;
	this->window = window;
}

void Player::lookAtMouse()
{
	direction.x = sf::Mouse::getPosition(*window).x - float(window->getSize().x / 2);
	direction.y = sf::Mouse::getPosition(*window).y - float(window->getSize().y / 2);
	direction.y *= -1.0;

	rotate = AngleBetweenTwoVectors(direction, sf::Vector2f(10.0, 0.0)); 

	if (direction.y >= 0)
	{
		shape.setRotation(float(-rotate + 90)); // +90: adjust
	}
	else
	{
		shape.setRotation(float(rotate - 270)); // -270: adjust
	}
}


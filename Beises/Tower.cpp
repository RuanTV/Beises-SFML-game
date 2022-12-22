#include "Tower.h"

#include "GameMath.h"

Tower::Tower(sf::RenderWindow* window) : Entity(window)
{
	this->hp = 0;
	this->rotate = 0.0;
	this->window = window;

	this->hpRect.setSize(sf::Vector2f(40.0f, 2.0f));
	this->hpRect.setFillColor(sf::Color(0, 255, 0, 255));

}

int Tower::getHp() const
{
	return hp;
}

void Tower::setHp(int value)
{
	this->hp = value;
}

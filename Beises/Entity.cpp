#include "Entity.h"

Entity::Entity(sf::RenderWindow* window)
{
	this->window = window;
}

Entity::~Entity()
{

}

void Entity::loadSprite(const char* path)
{
	texture.loadFromFile(path);
	shape.setTexture(texture);
}
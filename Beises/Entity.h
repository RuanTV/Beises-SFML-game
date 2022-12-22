#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Entity
{
public:

	Entity(sf::RenderWindow* window);
	~Entity();

	const sf::Vector2f& getDirection() const
	{
		return direction;
	}

	void loadSprite(const char* path);

	sf::Texture texture;

	sf::Sprite shape;

	//sf::RectangleShape shape;

	sf::Vector2f direction;

	sf::RenderWindow* window;
};


#endif


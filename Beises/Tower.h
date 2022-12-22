#ifndef _TOWER_H_
#define _TOWER_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Entity.h"

class Tower : public Entity
{
public:

	Tower(sf::RenderWindow* window);

	int getHp() const;

	void setHp(int value);

	sf::RectangleShape hpRect;

private:

	int hp;

	double rotate;

	sf::RenderWindow* window;

};

#endif


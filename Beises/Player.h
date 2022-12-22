#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Entity.h"

class Player : public Entity
{
public:

	Player(sf::RenderWindow* window);

	void lookAtMouse();

private:
	double rotate;
	sf::RenderWindow* window;

};

#endif
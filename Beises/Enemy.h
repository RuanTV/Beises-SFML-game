#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Entity.h"

#include "GameMath.h"
#include "Enemy.h"

class Enemy : public Entity
{
public:

	Enemy(sf::RenderWindow* window);

	float getSpeed() const;

	void setSpeed(float value);

	bool getKill() const;

	void setKill(bool value);

	void lookAtPoint();

private:
	float speed;
	float rotate;
	bool kill;
};


#endif



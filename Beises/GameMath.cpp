#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "GameMath.h"

double AngleBetweenTwoVectors(sf::Vector2f u, sf::Vector2f v)
{

	//v.y = 0.0;
	//v.x = 10.0;

	double result = 0.0f;

	double uv = (u.x * v.x) + (u.y * v.y);

	//std::cout << u.x << " " << u.y << "  |  " << v.x << " " << v.y << '\n';

	double mod_u = pow(u.x, 2) + pow(u.y, 2);
	double mod_v = pow(v.x, 2) + pow(v.y, 2);

	if (sqrt(mod_u * mod_v) != 0)
		result = std::acos(uv / sqrt((mod_u * mod_v)));

	// convert to degree

	result = (result * 180.0) / PI;


	return result;
}

sf::Vector2f NormalizeVector(sf::Vector2f u)
{
	float u_mod = float(sqrt(pow(u.x, 2) + pow(u.y, 2)));

	return sf::Vector2f(u.x / u_mod, u.y / u_mod);
}

double DistanceBetweenTwoPoints(sf::Vector2f a, sf::Vector2f b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
#ifndef _GAMEMATH_H_
#define _GAMEMATH_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

const double PI = 3.14159265;

double AngleBetweenTwoVectors(sf::Vector2f u, sf::Vector2f v);

sf::Vector2f NormalizeVector(sf::Vector2f u);

double DistanceBetweenTwoPoints(sf::Vector2f a, sf::Vector2f b);

#endif
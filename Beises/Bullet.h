#ifndef _BULLET_H_
#define _BULLET_H_

#include "Entity.h"

class Bullet : public Entity
{

public:

	Bullet(sf::RenderWindow* window);

	void setSpeed(float value);
	float getSpeed() const;

private:
	float speed;

};


#endif


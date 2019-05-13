#pragma once
#include "includes.h"
#include "movable.h"
class bullet : public movable
{
protected:
	std::string type;
	float speed;
	float damage;
	float angle;

public:
	Hitbox::odcinek tracer;
	void fly(double deltaTime);
	bullet(std::string type, sf::ConvexShape body, float speed, float damage, float angle, sf::Vector2f punkt);
	void draw(sf::RenderWindow&);
	bullet();
	~bullet();
};


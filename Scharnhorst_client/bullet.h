#pragma once
#include "includes.h"
#include "movable.h"
class Bullet : public movable
{
protected:
	std::string type;
	float speed;
	float damage;
	float angle;

public:
	Hitbox::odcinek tracer;
	void fly(double deltaTime);
	Bullet(std::string type, sf::ConvexShape body, float speed, float damage, float angle, sf::Vector2f punkt);
	void draw(sf::RenderWindow&);
	Bullet();
	~Bullet();
};


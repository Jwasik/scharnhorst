#pragma once
#include "includes.h"

#define M_PI 3.14159265358979323846

class physical
{
protected:
	sf::ConvexShape shape;


public:
	physical();
	physical(sf::Vector2f);
	void setPosition(sf::Vector2f);
	void setRotation(float);
	virtual void draw(sf::RenderWindow*);
	virtual sf::Vector2f getPosition();
	virtual float getRotation();


	~physical();

};


#pragma once
#include "physical.h"
class movable :	public physical //,public sf::Drawable
{
protected:
	float changeAngle(float, float);
public:
	movable();
	movable(sf::Vector2f);
	void move(sf::Vector2f);
	void rotate(float);
	~movable();
};


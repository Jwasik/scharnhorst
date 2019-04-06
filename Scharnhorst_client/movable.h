#pragma once
#include "physical.h"
class movable :	public physical //,public sf::Drawable
{
protected:
public:
	float changeAngle(float, float);
	float stopnieNaRadiany(float s);
	movable();
	movable(sf::Vector2f);
	void move(sf::Vector2f);
	void rotate(float);
	~movable();
};


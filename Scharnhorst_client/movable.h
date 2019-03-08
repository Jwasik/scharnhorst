#pragma once
#include "physical.h"
class movable :	public physical, public sf::Drawable
{
protected:
	float angle;//oznacza k¹t obrotu obiektu wzglêdem pó³nocy
public:
	movable();
	virtual void move(sf::Vector2f);
	virtual void setPosition(sf::Vector2f);
	virtual void rotate(float);
	virtual void setRotation(float);
	virtual float getRotation();
	~movable();
};


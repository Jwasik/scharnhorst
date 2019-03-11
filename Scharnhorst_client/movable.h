#pragma once
#include "physical.h"
class movable :	public physical, public sf::Drawable
{
protected:
public:
	movable(sf::Vector2f);
	virtual void move(sf::Vector2f);
	virtual void rotate(float);
	~movable();
};


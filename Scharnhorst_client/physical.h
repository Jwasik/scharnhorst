#pragma once
#include "includes.h"
class physical
{
protected:
	sf::Vector2f position;
	std::vector<std::shared_ptr<sf::Shape>> shapes;

public:
	physical();
	physical(sf::Vector2f);
	virtual void setPosition(sf::Vector2f);
	virtual void setRotation(float);
	~physical();
};


#include "pch.h"
#include "physical.h"


physical::physical()
{
	position = sf::Vector2f(0, 0);
}

physical::physical(sf::Vector2f position)
{
	this->position = position;
}

void physical::setPosition(sf::Vector2f)
{

}

void physical::setRotation(float)
{
}

physical::~physical()
{
}

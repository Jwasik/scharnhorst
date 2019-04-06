#include "pch.h"
#include "movable.h"

movable::movable()
{

}

movable::movable(sf::Vector2f position)
{
	physical::physical(position);
}

void movable::move(sf::Vector2f distance)
{
	physical::setPosition(sf::Vector2f(physical::getPosition().x + distance.x, physical::getPosition().y + distance.y));
}

float changeAngle(float a, float b)
{
	float tem = a + b;
	if (tem > 360)
	{
		tem = tem - 360;
	}
	else
		if (tem < 0)
		{
			tem = tem + 360;
		}
	return tem;
}
void movable::rotate(float alpha)
{
	physical::setRotation(changeAngle(alpha, physical::getRotation()));
}





movable::~movable()
{
}

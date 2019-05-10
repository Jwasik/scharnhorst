#include "pch.h"
#include "movable.h"
#define M_PI 3.14159265358979323846

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

float movable::changeAngle(float a, float b)
{
	float t = a + b;
	if (t > 360)
	{
		t = t - 360;
	}
	else
		if (t < 0)
		{
			t = t + 360;
		}
	return t;
}

float movable::changeAngle(float a, float b, float c)
{
	float t = a + b + c;
	if (t > 360)
	{
		t = t - 360;
	}
	else
		if (t < 0)
		{
			t = t + 360;
		}
	return t;
}

float movable::stopnieNaRadiany(float s)
{
	return (s / 180.0) * M_PI;
}

float movable::howManyDegreeFrom(float a, float b)
{
	float tem = b - a;
	if (tem < 0)
	{
		return tem + 360;
	}
	else
		return tem;
}

void movable::rotate(float alpha)
{
	physical::setRotation(changeAngle(alpha, physical::getRotation()));
}





movable::~movable()
{
}

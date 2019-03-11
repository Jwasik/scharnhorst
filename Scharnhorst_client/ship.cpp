#include "pch.h"
#include "ship.h"

#define PI 3.14159265

ship::ship()
{
	turnAcceleration = 0.5;
	enginePower = 1000;
	width = 10;
	length = 10;
	actualSpeed = 0;
	maxSpeed = 10;
	mass = 1000;
	calculateAccelerations()
}


ship::~ship()
{
}


void ship::accelerate(int direction, double dtime) //{-1, 0, 1}
{
	acceleration = (enginePower / mass)*(actualSpeed + maxSpeed)(actualSpeed - maxSpeed) * -1 / actualSpeed * actualSpeed;

	if (direction = -1)
	{
		actualSpeed = actualSpeed - dtime *(acceleration / 2/* <-- zabazpieczenie przed zapierdalaniem w ty³*/ + actualSpeed / 4);
	}
	else
		if (direction = 0)
		{
			actualSpeed = actualSpeed - dtime *actualSpeed * direction;
		}
		else
		actualSpeed = actualSpeed + dtime *acceleration*direction/4 ;

}

void ship::spin(bool direction, double dtime)
{
	turnAcceleration = maxTurnAcceleration * (actualSpeed + 0.5*maxTurnAcceleration)(actualSpeed - 1.5*maxTurnAcceleration)* -1 / actualSpeed * actualSpeed;

	movable::rotate(dtime*turnAcceleration);
}

void ship::swim(sf::RenderWindow *window, double dtime)
{
	float distance = actualSpeed * dtime;//tutaj ta delta czasu klatki [s // poproszê w sekundach]
	movable::move(sf::Vector2f(distance * sin(physical::getRotation()*PI / 180), - distance * cos(physical::getRotation()*PI / 180)));
	physical::draw(window);
}
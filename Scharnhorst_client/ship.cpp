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

void ship::calculateAccelerations()
{
	acceleration = (enginePower / mass)*(actualSpeed + maxSpeed)(actualSpeed - maxSpeed) * -1/ actualSpeed* actualSpeed;
	turnAcceleration = maxTurnAcceleration * (actualSpeed + 0.5*maxTurnAcceleration)(actualSpeed - 1.5*maxTurnAcceleration)* -1 / actualSpeed * actualSpeed;
}

void ship::accelerate(int direction) //{-1, 0, 1}
{
	if (direction = -1)
	{
		actualSpeed = actualSpeed - server::getDeltaTime()*(acceleration / 2/* <-- zabazpieczenie przed zapierdalaniem w ty³*/ + actualSpeed / 4);
	}
	else
		if (direction = 0)
		{
			actualSpeed = actualSpeed - server::getDeltaTime()*actualSpeed/4;
		}
		else
		actualSpeed = actualSpeed + server::getDeltaTime()*acceleration;

}

void ship::spin(bool direction)
{
	movable::rotate(server::getDeltaTime()*turnAcceleration);
}

void ship::swim(sf::RenderWindow *window)
{
	float distance = actualSpeed * server::getDeltaTime() ;//tutaj ta delta czasu klatki [s // poproszê w sekundach]
	movable::move(sf::Vector2f(distance * sin(physical::getRotation()*PI / 180), - distance * cos(physical::getRotation()*PI / 180)));
	physical::draw(window);
}
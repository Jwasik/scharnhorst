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
}


ship::~ship()
{
}


void ship::accelerate(int direction, double deltaTime) //{-1, 0, 1}
{
	acceleration = (this->enginePower / this->mass) * (this->actualSpeed + this->maxSpeed)*(this->actualSpeed - this->maxSpeed) * -1 / this->actualSpeed * this->actualSpeed;

	if (direction = -1)
	{
		actualSpeed = actualSpeed - deltaTime *(acceleration * 0.75f/* <-- zabazpieczenie przed zapierdalaniem w ty³*/ );
	}
	else if (direction = 0)
	{
			actualSpeed = actualSpeed - deltaTime *actualSpeed * direction;
	}
	else
	actualSpeed = actualSpeed + deltaTime *acceleration*direction/4 ;

}

void ship::spin(bool direction, double dtime)
{
	turnAcceleration = maxTurnAcceleration * (actualSpeed + 0.5*maxTurnAcceleration)*(actualSpeed - 1.5*maxTurnAcceleration)* -1 / actualSpeed * actualSpeed;
	this->rotate(dtime*turnAcceleration);
}

void ship::changeGear(bool change)
{
	if (change == 0 && gear > -1)
	{
		this->gear--;
	}
	else if(change == 1 && gear < 4)
	{
		this->gear++;
	}
	// w przeciwnym razie nic siê nie zmieni
}

void ship::swim(sf::RenderWindow &window, double deltaTime)
{
	float distance = actualSpeed * deltaTime;//tutaj ta delta czasu klatki [s // poproszê w sekundach]
	this->move(sf::Vector2f(distance * sin(this->getRotation()*PI / 180), - distance * cos(this->getRotation()*PI / 180)));
}
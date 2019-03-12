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
	force = enginePower / mass;
}


ship::~ship()
{
}

float ship::calculateAcceleration()
{
	acceleration = force*gear*0.25f * (this->actualSpeed + this->maxSpeed)*(this->actualSpeed - this->maxSpeed) * -1 / this->actualSpeed * this->actualSpeed;

	return acceleration;
}

void ship::accelerate( double deltaTime) //{-1, 0, 1}
{
	calculateAcceleration();
	actualSpeed = actualSpeed + deltaTime *acceleration - actualSpeed/4 /* <-- opór wody*/;
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
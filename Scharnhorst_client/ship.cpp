#include "pch.h"
#include "ship.h"

#define PI 3.14159265

ship::ship()
{
	gear = 0;
	maxTurnAcceleration = 1.5;
	enginePower = 500;
	width = 10;
	length = 10;
	actualSpeed = 0;
	maxSpeed = 10;
	mass = 100;
	force = enginePower / mass;
}


ship::~ship()
{
}

float ship::calculateAcceleration()
{
	acceleration = force*gear*0.25f * (this->actualSpeed + this->maxSpeed)*(this->actualSpeed - this->maxSpeed) * -1 / (this->maxSpeed * this->maxSpeed);

	return acceleration;
}

void ship::accelerate( double deltaTime) //{-1, 0, 1}
{
	calculateAcceleration();
	if (gear == 0)
	{
		actualSpeed = actualSpeed * 0.75f/* <-- opór wody*/;

	}
	else
	{
		if (gear == -1)
		{
			if(actualSpeed < 0)
				actualSpeed = actualSpeed + deltaTime * acceleration - (actualSpeed * 0.25f) /* <-- opór wody*/;

		}
	}
	actualSpeed = actualSpeed + deltaTime *acceleration;
}




void ship::spin(bool direction, double dtime)
{
	
	turnAcceleration = maxTurnAcceleration * (actualSpeed + 0.5*maxSpeed)*(actualSpeed - 1.5*maxSpeed)* -1 / (maxSpeed * maxSpeed);
	if (direction == 1)
	this->rotate(dtime*turnAcceleration);
	else
		this->rotate(-1 * dtime*turnAcceleration);
}

void ship::changeGear(bool change)
{
	if ((change == 0) && (gear > -1))
	{
		gear--;
	}
	else if((change == 1) && (gear < 4))
	{
		gear++;
	}
	// w przeciwnym razie nic siê nie zmieni
}

void ship::swim(sf::RenderWindow *window, double deltaTime)
{
	float distance = actualSpeed * deltaTime;//tutaj ta delta czasu klatki [s // poproszê w sekundach]
	this->move(sf::Vector2f(distance * sin(this->getRotation()*PI / 180), - distance * cos(this->getRotation()*PI / 180)));
	window->draw(shape);
}
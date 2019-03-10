#include "pch.h"
#include "ship.h"


ship::ship()
{
	turnAcceleration = 0.5;
	enginePower = 1000;
	width = 10;
	length = 10;
	actualSpeed = 0;
	maxSpeed = 10;
	mass = 1000;
	parametersToAcceleration()
}


ship::~ship()
{
}

void ship::calculateAcceleration()
{
	acceleration = (enginePower / mass)*(actualSpeed + maxSpeed)(actualSpeed - maxSpeed) * -1/ actualSpeed* actualSpeed;
}
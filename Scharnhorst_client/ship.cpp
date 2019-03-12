#include "pch.h"
#include "ship.h"

#define PI 3.14159265

std::string Ship::getType()
{
	return this->type;
}

Ship::Ship()
{
	shape.setPointCount(3);
	shape.setPoint(0, sf::Vector2f(32, 0));
	shape.setPoint(1, sf::Vector2f(0, 64));
	shape.setPoint(2, sf::Vector2f(64, 64));
	shape.setOrigin(sf::Vector2f(32,32));
	shape.move(shape.getOrigin());

	this->type = "NONE";
	this->gear = 0;
	this->maxTurnAcceleration = 1.5;
	this->enginePower = 500;
	this->width = 10;
	this->length = 10;
	this->actualSpeed = 0;
	this->maxSpeed = 10;
	this->mass = 100;
	this->force = enginePower / mass;
}


Ship::~Ship()
{
}

float Ship::calculateAcceleration()
{
	acceleration = force*gear*0.25f * (this->actualSpeed + this->maxSpeed)*(this->actualSpeed - this->maxSpeed) * -1 / (this->maxSpeed * this->maxSpeed);

	return acceleration;
}

void Ship::accelerate( double deltaTime) //{-1, 0, 1}
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
			if(actualSpeed < 0)	actualSpeed = actualSpeed + deltaTime * acceleration - (actualSpeed * 0.25f) /* <-- opór wody*/;
		}
	}
	actualSpeed = actualSpeed + deltaTime *acceleration;
}




void Ship::spin(bool direction, double dtime)
{
	
	turnAcceleration = maxTurnAcceleration * (actualSpeed + 0.5*maxSpeed)*(actualSpeed - 1.5*maxSpeed)* -1 / (maxSpeed * maxSpeed);
	if (direction == 1)this->rotate(dtime*turnAcceleration);
	else this->rotate(-1 * dtime*turnAcceleration);
}

void Ship::changeGear(bool change)
{
	if ((change == 0) && (gear > -1))
	{
		gear--;
		std::cout << "Actual gear: " << gear << std::endl;
	}
	else if((change == 1) && (gear < 4))
	{
		gear++;
		std::cout << "Actual gear: " << gear << std::endl;//W warunkach ¿eby nie pokazywa³o za ka¿dym klikniêciem, tylko przy zmianie
	}
	// w przeciwnym razie nic siê nie zmieni
}

void Ship::draw(sf::RenderWindow &window)
{
	window.draw(this->shape);
}

void Ship::swim(double deltaTime)
{
	this->accelerate(deltaTime);
	float distance = actualSpeed * deltaTime;//tutaj ta delta czasu klatki [s // poproszê w sekundach]
	this->move(sf::Vector2f(distance * sin(this->getRotation()*PI / 180), - distance * cos(this->getRotation()*PI / 180)));
}
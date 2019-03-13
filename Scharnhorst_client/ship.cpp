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
	this->maxTurnAcceleration = 8;
	this->enginePower = 11768000;
	this->width = 10;
	this->length = 10;
	this->actualSpeed = 0;
	this->maxSpeed = 16.25;
	this->mass = 38900000;
	this->acceleration = enginePower / mass;

	shipStaticPressure = acceleration/(maxSpeed*maxSpeed);

}


Ship::~Ship()
{
}

float Ship::calculateAcceleration()
{
	waterRezistance = shipStaticPressure * actualSpeed*actualSpeed;



	/*float temmaxSpeed = maxSpeed;

	/*if (gear > 0)
		 temmaxSpeed = maxSpeed * gear*0.25f;
	

	 acceleration = force*gear*0.25f * (this->actualSpeed  + temmaxSpeed)*(this->actualSpeed - temmaxSpeed) * -1 / (temmaxSpeed * temmaxSpeed);

		 

	return acceleration;*/
	return waterRezistance;
}

void Ship::accelerate( double deltaTime) //{-1, 0, 1}
{
	calculateAcceleration();

	if (actualSpeed > 0)
	{
		actualSpeed -= waterRezistance * deltaTime;
	}
	else
	{
		actualSpeed += waterRezistance*deltaTime;
	}

	if (gear != 0)
	{
		actualSpeed += acceleration * gear*0.25 * deltaTime;
	}


	/*if (gear == 0)
	{
		/*if (actualSpeed == 0)return;
		if (abs(actualSpeed) - waterRezistance * deltaTime < waterRezistance*deltaTime)actualSpeed = 0;*/
		/*if (actualSpeed > 0)
		{
			actualSpeed = actualSpeed - waterRezistance*deltaTime;
		}
		else
		{
			actualSpeed = actualSpeed + waterRezistance*deltaTime;
		}

	}
	else
	{
		if (gear > 0)
		{
			if (actualSpeed >= 0)
			{
				actualSpeed = actualSpeed + (force - waterRezistance)*deltaTime;
			}
			else
			{
				actualSpeed = actualSpeed + (force + waterRezistance)*deltaTime;
			}
		}
		else
		{
			if (actualSpeed >= 0)
			{
				actualSpeed = actualSpeed - (force - waterRezistance)*deltaTime;
			}
			else
			{
				actualSpeed = actualSpeed - (force + waterRezistance)*deltaTime;
			}
		}

	}
	
	/*if (gear == 0)
	{
		actualSpeed -= actualSpeed * 0.5f * deltaTime/* <-- opór wody;
	}
	else
	{

			if(actualSpeed > 0&&gear == -1)	actualSpeed = actualSpeed + deltaTime * acceleration - actualSpeed * 0.1f * deltaTime;

	}
	actualSpeed = actualSpeed + deltaTime * acceleration;*/
}




void Ship::spin(bool direction, double dtime)
{
	turnAcceleration = maxTurnAcceleration * (-(actualSpeed / maxSpeed * 1.5 - 0.85)*(actualSpeed / maxSpeed * 1.5 - 0.85) + 1);
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
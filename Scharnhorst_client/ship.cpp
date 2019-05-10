#include "pch.h"
#include "ship.h"

#define PI 3.14159265

std::string Ship::getType()
{
	return this->type;
}

Ship::Ship()
{

	shape.setPointCount(7);
	shape.setPoint(0, sf::Vector2f(48, 0));
	shape.setPoint(1, sf::Vector2f(16, 64));
	shape.setPoint(2, sf::Vector2f(0, 192));
	shape.setPoint(3, sf::Vector2f(16, 336));
	shape.setPoint(4, sf::Vector2f(80, 336));
	shape.setPoint(5, sf::Vector2f(96, 192));
	shape.setPoint(6, sf::Vector2f(80, 64));
	shape.setOrigin(sf::Vector2f(48, 168));
	shape.move(shape.getOrigin());
	shape.move(sf::Vector2f(128, 512));
	deleteOrigin();

	turrets.push_back(std::make_shared<turret>(turret("test", sf::Vector2f(128, 512), 100, 0)));
	turrets.push_back(std::make_shared<turret>(turret("test", sf::Vector2f(128, 512), 20, 0)));
	turrets.push_back(std::make_shared<turret>(turret("test", sf::Vector2f(128, 512), -40, 0)));
	turrets.push_back(std::make_shared<turret>(turret("test", sf::Vector2f(128, 512), -100, 0)));


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

	shipStaticPressure = acceleration / (maxSpeed*maxSpeed);

}


Ship::~Ship()
{
}

float Ship::calculateAcceleration()
{
	waterRezistance = shipStaticPressure * actualSpeed*actualSpeed;
	return waterRezistance;
}

void Ship::accelerate(double deltaTime) //{-1, 0, 1}
{
	calculateAcceleration();

	if (actualSpeed > 0)
	{
		actualSpeed -= waterRezistance * deltaTime;
	}
	else
	{
		actualSpeed += waterRezistance * deltaTime;
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
	turnAcceleration = maxTurnAcceleration * sin(PI*0.6*(actualSpeed / maxSpeed));
	//turnAcceleration = maxTurnAcceleration * (-(actualSpeed / maxSpeed * 1.5 - 0.85)*(actualSpeed / maxSpeed * 1.5 - 0.85) + 1);
	if (direction == 1)this->rotate(dtime*turnAcceleration);
	else this->rotate(-1 * dtime*turnAcceleration);
}

void Ship::changeGear(bool change)
{
	if ((change == 0) && (gear > -1))
	{
		gear--;
	}
	else if ((change == 1) && (gear < 4))
	{
		gear++;
	}

	// w przeciwnym razie nic siê nie zmieni
}


void Ship::setCannonRotation(float angle)
{
	for (int i = 0; i < turrets.size(); i++)
	{

		turrets[i]->shape.setRotation(angle);

	}
}

float Ship::getCannonRotation()
{
	return turrets[0]->turretAngle;
}

void Ship::swim(double deltaTime)
{
	this->accelerate(deltaTime);
	float distance = actualSpeed * deltaTime;//tutaj ta delta czasu klatki [s // poproszê w sekundach]
	this->move(sf::Vector2f(distance * sin(this->getRotation()*PI / 180), -distance * cos(this->getRotation()*PI / 180)));

	std::cout << "gear: " << gear << std::endl;
	std::cout << "speed: " << actualSpeed << std::endl;

}

void Ship::setTurrets(float mouseAngle, float dTime)
{
	for (int i = 0; i < turrets.size(); i++)
	{
		turrets[i]->updatePosition(this->shape.getRotation(), mouseAngle, this->shape.getPosition(), dTime);

	}
}

void Ship::draw(sf::RenderWindow& window)
{

	this->physical::draw(window);
	for (int i = 0; i < turrets.size(); i++)
	{

		window.draw(turrets[i]->shape);
	}

}

#include "pch.h"
#include "ship.h"
#include <fstream>

#define PI 3.14159265

std::string Ship::getType()
{
	return this->type;
}

void Ship::setName(std::string name)
{
	this->name = name;
}

std::string Ship::getName()
{
	return this->name;
}

Ship::Ship()
{
	shape.move(shape.getOrigin());
	shape.move(sf::Vector2f(128, 512));
	shape.setFillColor(sf::Color(50,50,50));
	deleteOrigin();
	//----------------------------------------------------

	this->type = "NONE";
	this->gear = 0;
	this->maxTurnAcceleration = 3;
	this->enginePower = 117680000;
	this->width = 10;
	this->length = 10;
	this->actualSpeed = 0;
	this->maxSpeed = 16.25;
	this->mass = 38900000;
	this->acceleration = enginePower / mass;

	shipStaticPressure = acceleration / (maxSpeed*maxSpeed);
}

Ship::Ship(std::string &name, float parameters[6], sf::ConvexShape shape)
{
	this->shape = shape;

	/*hitboxes[0].setFillColor(sf::Color::Red);
	hitboxes[0].setSize(sf::Vector2f(260,30));
	hitboxes[0].setOrigin(sf::Vector2f(130,15));*/

	auto temporaryOrigin = this->shape.getOrigin();
	this->hitbox[0] = odcinek(sf::Vector2f(0, 0/*temporaryOrigin.y*/), sf::Vector2f(/*temporaryOrigin.x * 2*/0, 0/*temporaryOrigin.y*/));
	this->hitbox[1] = odcinek(sf::Vector2f(/*temporaryOrigin.y*/0, 0), sf::Vector2f(/*temporaryOrigin.x*/0, 0/*temporaryOrigin.y * 2*/));

	this->shape.move(shape.getOrigin());
	this->shape.move(sf::Vector2f(128, 512));
	this->shape.setFillColor(sf::Color(50, 50, 50));
	this->deleteOrigin();

	this->type = name;
	this->gear = 0;
	this->maxTurnAcceleration = 55;//parameters[0];
	this->enginePower = 1000000;//parameters[1];
	this->width = parameters[2];
	this->length = parameters[3];
	this->maxSpeed = parameters[4]*8;
	this->mass = parameters[5];
	this->actualSpeed = 0;
	this->acceleration = (enginePower / mass)*20;

	this->shipStaticPressure = acceleration / (maxSpeed*maxSpeed);
	//this->bodyProjection.setPointCount(4);
	/*for (int i = 0; i < 4; i++)
	{
		bodyProjection.setPoint(i, sf::Vector2f(0, 0));
	}*/
	createBodyprojection();
}


Ship::~Ship()
{
}

Ship::Ship(const Ship &newShip)
{
	this->hitbox[0] = newShip.hitbox[0];
	this->hitbox[1] = newShip.hitbox[1];



	this->shape = newShip.shape;
	this->width = newShip.width;
	this->length = newShip.length;
	this->maxSpeed = newShip.length;
	this->maxTurnAcceleration = newShip.maxTurnAcceleration;
	this->turnAcceleration = newShip.turnAcceleration;
	this->mass = newShip.mass;
	this->enginePower = newShip.enginePower;
	this->force = newShip.force;
	this->waterRezistance = newShip.waterRezistance;
	this->shipStaticPressure = newShip.shipStaticPressure;
	this->gear = 0;
	this->acceleration = newShip.acceleration;
	this->actualSpeed = 0;
	this->type = newShip.type;
	this->name = newShip.name;
	for (auto & turret : newShip.turrets)
	{
		this->turrets.push_back(std::make_shared<Turret>(*turret));
	}
	createBodyprojection();
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

	//std::cout << actualSpeed << std::endl;
}




void Ship::spin(bool direction, double dtime)
{
	turnAcceleration = maxTurnAcceleration * sin(PI*0.6*(actualSpeed / maxSpeed));
	if (direction == 1)
	{
		this->rotate(dtime*turnAcceleration);
		hitbox[0].rotate(dtime*turnAcceleration);
		hitbox[1].rotate(dtime*turnAcceleration);

	}
	else
	{
		this->rotate(-1 * dtime*turnAcceleration);
		hitbox[0].rotate(-1 * dtime*turnAcceleration);
		hitbox[1].rotate(-1 * dtime*turnAcceleration);

	}

	
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
	for (auto & turret : turrets)
	{
		turret->setRotation(angle);
	}
}

float Ship::getCannonRotation()
{
	if(turrets[0] != nullptr)return turrets[0]->getTurretAngle();
	return 0;
}

void Ship::addPoint(unsigned short number,sf::Vector2f &point)
{
	this->shape.setPoint(number,point);
}

void Ship::addTurret(std::shared_ptr<Turret> turret,sf::Vector2f positionFromShip)
{
	this->turrets.push_back(std::make_shared<Turret>(*turret));
	this->turrets.back()->setTurretPosition(positionFromShip);
}

void Ship::swim(double deltaTime)
{
	this->accelerate(deltaTime);
	float distance = actualSpeed * deltaTime;//tutaj ta delta czasu klatki [s // poproszê w sekundach]
	this->move(sf::Vector2f(distance * sin(this->getRotation()*PI / 180), -distance * cos(this->getRotation()*PI / 180)));
	this->hitbox[0].setPosition(shape.getPosition());
	this->hitbox[1].setPosition(shape.getPosition());

	this->hitbox[0].updateVisual();
	this->hitbox[1].updateVisual();

}

void Ship::setTurrets(float &mouseAngle, double &dTime)
{
	auto shipPosition = this->getPosition();
	for (auto & turret : turrets)
	{
		turret->updatePosition(this->shape.getRotation(), mouseAngle, shipPosition, dTime);
	}
}

void Ship::draw(sf::RenderWindow& window)
{
	this->physical::draw(window);
	for (auto turret : turrets)
	{
		turret->draw(window);
	}
	window.draw(hitbox[0].line);
	window.draw(hitbox[1].line);///do testów(usuñ)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

}

void Ship::shoot(std::shared_ptr<std::vector<jw::bulletInfo>> bulletsGotFromTurret)
{
	auto angle = this->shape.getRotation();
	for (auto & turret : turrets)
	{
		turret->shoot(bulletsGotFromTurret,angle);
	}
}


void Ship::createBodyprojection()
{
	int pointCount;
	pointCount = shape.getPointCount();
	for (int i = 0; i < pointCount; i++)
	{
		if (this->shape.getPoint(i).y < hitbox[0].punkt1.y)
		{
			hitbox[0].punkt1 = shape.getPoint(i);
			continue;
		}
		if (this->shape.getPoint(i).x > hitbox[1].punkt1.x)
		{
			hitbox[1].punkt1 = shape.getPoint(i);

			continue;
		}
		if (this->shape.getPoint(i).y > this->hitbox[0].punkt2.y)
		{
			hitbox[0].punkt2 = shape.getPoint(i);

			continue;
		}
		if (this->shape.getPoint(i).x < this->hitbox[1].punkt2.x)
		{

			this->hitbox[1].punkt2 = this->shape.getPoint(i);



			continue;
		}
	}
	


	/*for (int i = 0; i < pointCount; i++)
	{
		std::cout << shape.getPoint(i).x << " " << shape.getPoint(i).y << std::endl;
	}*/

}




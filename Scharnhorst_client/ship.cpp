#include "pch.h"
#include "ship.h"

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

	//----------------------------------------------------
	std::vector<sf::Vector2f> scharnhorstPoints;
	scharnhorstPoints.push_back(sf::Vector2f(111, 0));
	scharnhorstPoints.push_back(sf::Vector2f(136, 80));
	scharnhorstPoints.push_back(sf::Vector2f(136, 88));
	scharnhorstPoints.push_back(sf::Vector2f(136, 101));
	scharnhorstPoints.push_back(sf::Vector2f(143, 113));
	scharnhorstPoints.push_back(sf::Vector2f(150, 145));
	scharnhorstPoints.push_back(sf::Vector2f(170, 260));
	scharnhorstPoints.push_back(sf::Vector2f(178, 322));
	scharnhorstPoints.push_back(sf::Vector2f(179, 367));
	scharnhorstPoints.push_back(sf::Vector2f(189, 424));
	scharnhorstPoints.push_back(sf::Vector2f(198, 492));
	scharnhorstPoints.push_back(sf::Vector2f(209, 614));
	scharnhorstPoints.push_back(sf::Vector2f(212, 669));
	scharnhorstPoints.push_back(sf::Vector2f(216, 767));
	scharnhorstPoints.push_back(sf::Vector2f(219, 868));
	scharnhorstPoints.push_back(sf::Vector2f(216, 1020));
	scharnhorstPoints.push_back(sf::Vector2f(211, 1114));
	scharnhorstPoints.push_back(sf::Vector2f(205, 1176));
	scharnhorstPoints.push_back(sf::Vector2f(201, 1214));
	scharnhorstPoints.push_back(sf::Vector2f(198, 1241));
	scharnhorstPoints.push_back(sf::Vector2f(194, 1275));
	scharnhorstPoints.push_back(sf::Vector2f(190, 1305));
	scharnhorstPoints.push_back(sf::Vector2f(185, 1339));
	scharnhorstPoints.push_back(sf::Vector2f(180, 1367));
	scharnhorstPoints.push_back(sf::Vector2f(174, 1396));
	scharnhorstPoints.push_back(sf::Vector2f(174, 1422));
	scharnhorstPoints.push_back(sf::Vector2f(169, 1455));
	scharnhorstPoints.push_back(sf::Vector2f(163, 1483));
	scharnhorstPoints.push_back(sf::Vector2f(155, 1523));
	scharnhorstPoints.push_back(sf::Vector2f(142, 1580));
	scharnhorstPoints.push_back(sf::Vector2f(135, 1605));
	scharnhorstPoints.push_back(sf::Vector2f(127, 1634));
	scharnhorstPoints.push_back(sf::Vector2f(125, 1639));
	scharnhorstPoints.push_back(sf::Vector2f(123, 1643));
	scharnhorstPoints.push_back(sf::Vector2f(120, 1647));
	scharnhorstPoints.push_back(sf::Vector2f(115, 1649));
	scharnhorstPoints.push_back(sf::Vector2f(111, 1649));
	for (auto x : scharnhorstPoints)
	{
		x.x *= 2.1621;
		x.y *= 1.1345;
	}
	auto size = scharnhorstPoints.size();
	for (unsigned int i = size-1; i >0; i--)
	{
		scharnhorstPoints.push_back(sf::Vector2f(111-(scharnhorstPoints[i].x-111), scharnhorstPoints[i].y));
	}
	shape.setPointCount(72);
	for (unsigned int i = 0; i < 72; i++)
	{
		shape.setPoint(i,scharnhorstPoints[i]);
	}


	shape.setOrigin(109,936);
	shape.move(shape.getOrigin());
	shape.move(sf::Vector2f(128, 512));
	shape.setFillColor(sf::Color(50,50,50));
	deleteOrigin();
	//----------------------------------------------------

	this->type = "NONE";
	this->gear = 0;
	this->maxTurnAcceleration = 1000;
	this->enginePower = 117680000;
	this->width = 10;
	this->length = 10;
	this->actualSpeed = 0;
	this->maxSpeed = 16.25;
	this->mass = 38900000;
	this->acceleration = enginePower / mass;

	shipStaticPressure = acceleration / (maxSpeed*maxSpeed);
}

Ship::Ship(std::string &name, float parameters[6], unsigned short point_count)
{
	shape.setPointCount(point_count);

	this->type = name;
	this->gear = 0;
	this->maxTurnAcceleration = parameters[0];
	this->enginePower = parameters[1];
	this->width = parameters[2];
	this->length = parameters[3];
	this->actualSpeed = parameters[4];
	this->maxSpeed = parameters[5];
	this->mass = parameters[6];
	this->acceleration = enginePower / mass;

	shape.setOrigin(sf::Vector2f(width/2,length/2));
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
}




void Ship::spin(bool direction, double dtime)
{
	turnAcceleration = maxTurnAcceleration * sin(PI*0.6*(actualSpeed / maxSpeed));
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
}

void Ship::shoot(std::shared_ptr<std::vector<jw::bulletInfo>> bulletsGotFromTurret)
{
	for (auto & turret : turrets)
	{
		turret->shoot(bulletsGotFromTurret);
	}
}




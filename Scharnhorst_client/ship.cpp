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

	this->type = "NONE";
	this->gear = 0;
	this->maxTurnAcceleration = 8;
	this->enginePower = 117680000;
	this->width = 10;
	this->length = 10;
	this->actualSpeed = 0;
	this->maxSpeed = 16.25;
	this->mass = 38900000;
	this->acceleration = enginePower / mass;

	shipStaticPressure = acceleration / (maxSpeed*maxSpeed);

	std::vector<std::shared_ptr<barrel>> temvb;


	barrel temb;
	sf::ConvexShape temc;
	temc.setPointCount(4);
	temc.setPoint(0, sf::Vector2f(-5, -80));
	temc.setPoint(1, sf::Vector2f(5, -80));
	temc.setPoint(2, sf::Vector2f(5, 0));
	temc.setPoint(3, sf::Vector2f(-5, 0));
	temc.setFillColor(sf::Color(90,0,40));

	temvb.push_back(std::make_shared<barrel>(barrel(sf::Vector2f(-10, -10), temc)));
	temvb.push_back(std::make_shared<barrel>(barrel(sf::Vector2f(10, -10), temc)));

		turrets.push_back(std::make_shared<Turret>(Turret("test", this->shape.getPosition(), 100, 0, temvb)));

		temvb.pop_back();
		temvb.pop_back();

		temvb.push_back(std::make_shared<barrel>(barrel(sf::Vector2f(-10, -10), temc)));
		temvb.push_back(std::make_shared<barrel>(barrel(sf::Vector2f(10, -10), temc)));
	

	turrets.push_back(std::make_shared<Turret>(Turret("test", this->shape.getPosition(), 20, 0, temvb)));
	temvb.pop_back();
	temvb.pop_back();

	temvb.push_back(std::make_shared<barrel>(barrel(sf::Vector2f(-10, -10), temc)));
	temvb.push_back(std::make_shared<barrel>(barrel(sf::Vector2f(10, -10), temc)));
	turrets.push_back(std::make_shared<Turret>(Turret("test", this->shape.getPosition(), -40, 0, temvb)));
	temvb.pop_back();
	temvb.pop_back();

	temvb.push_back(std::make_shared<barrel>(barrel(sf::Vector2f(-10, -10), temc)));
	temvb.push_back(std::make_shared<barrel>(barrel(sf::Vector2f(10, -10), temc)));
	turrets.push_back(std::make_shared<Turret>(Turret("test", this->shape.getPosition(), -100, 0, temvb)));



	

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
	for (int i = 0; i < turrets.size(); i++)
	{

		turrets[i]->shape.setRotation(angle);

	}
}

float Ship::getCannonRotation()
{
	return turrets[0]->TurretAngle;
}

void Ship::addPoint(unsigned short number,sf::Vector2f &point)
{
	this->shape.setPoint(number,point);
}

void Ship::addTurret(std::shared_ptr<Turret> &turret)
{
	this->turrets.push_back(turret);
}

void Ship::swim(double deltaTime)
{
 	for (auto aut : bullets)
	{

		aut->fly(deltaTime);
	}

	this->accelerate(deltaTime);
	float distance = actualSpeed * deltaTime;//tutaj ta delta czasu klatki [s // poproszê w sekundach]
	this->move(sf::Vector2f(distance * sin(this->getRotation()*PI / 180), -distance * cos(this->getRotation()*PI / 180)));

	std::cout << "gear: " << gear << std::endl;
	std::cout << "speed: " << actualSpeed << std::endl;

}

void Ship::setturrets(float mouseAngle, float dTime)
{

	for (int i = 0; i < turrets.size(); i++)
	{
		turrets[i]->updatePosition(this->shape.getRotation(), mouseAngle, this->shape.getPosition(), dTime);

	}
	
}

void Ship::draw(sf::RenderWindow& window)
{

	this->physical::draw(window);
	
	for (auto aut : bullets)
	{
		aut->draw(window);
	}

	for (auto a : turrets)
	{

		a->draw(window);

	}


	

}

void Ship::SHOOT()
{
	std::vector<std::shared_ptr<bullet>> tem;

	for (auto aut : turrets)
	{
		tem = aut->SHOOT();
		/*for (std::shared_ptr<bullet> a : tem)
		{
			cout << aut->shape.getPosition().x << " " << aut->shape.getPosition().y << endl;

		}
		cout << endl;*/
		bullets + tem;

	}

}




#include "pch.h"
#include "turret.h"


void Turret::setRestrictedArea(float restrictedArea[2])
{
	this->restrictedArea[0] = restrictedArea[0];
	this->restrictedArea[1] = restrictedArea[1];

		if (restrictedArea[0] > restrictedArea[1])
		{
			middleOfLockedArea = ((restrictedArea[0] + restrictedArea[1] + 360) / 2);
			middleOfLockedArea = middleOfLockedArea % 360;
		}
		else
		{
			middleOfLockedArea = ((restrictedArea[0] + restrictedArea[1]) / 2);
		}


		this->turretAngle = changeAngle(middleOfLockedArea, 180);
		//std::cout << turretAngle << std::endl;

}

unsigned int Turret::getLoadPercent()
{
	auto time = this->timeFromShoot.getElapsedTime().asSeconds();
	if (time > this->barrels.front()->reloadTime)return 100;
	return unsigned int((time/ this->barrels.front()->reloadTime)*100);
	
}

Turret::Turret()
{
	shape.setPointCount(3);
	shape.setPoint(0, sf::Vector2f(-40, 0));
	shape.setPoint(1, sf::Vector2f(40, 0));
	shape.setPoint(2, sf::Vector2f(0, -50));
	type = "";
	shipOrigin = sf::Vector2f(0, 0);
	distanceFromShipOrigin = 40;
	angleFromShipOrigin = 0;
	restrictedArea[0] = 0;
	restrictedArea[1] = 10;
		if (restrictedArea[0] > restrictedArea[1])
		{
			middleOfLockedArea = ((restrictedArea[0] + restrictedArea[1] + 360) / 2);
			middleOfLockedArea = middleOfLockedArea % 360;
		}
		else
		{
			middleOfLockedArea = ((restrictedArea[0] + restrictedArea[1]) / 2);
		}
}

Turret::Turret(const Turret & turret)
{
	this->shape = turret.shape;

	this->type = turret.type;
	this->name = turret.name;
	this->shipOrigin = turret.shipOrigin;
	this->position = turret.position;

	for (const auto & barrel : turret.barrels)
	{
		this->barrels.push_back(std::make_shared<Barrel>(*barrel));
	}

	this->rotationSpeed = turret.rotationSpeed;
	this->distanceFromShipOrigin = turret.distanceFromShipOrigin;
	this->angleFromShipOrigin = turret.angleFromShipOrigin;
	this->shipAngle = turret.shipAngle;
	this->restrictedArea[0] = turret.restrictedArea[0];
	this->restrictedArea[1] = turret.restrictedArea[1];
	//this->arestrictedArea[0] = turret.arestrictedArea[0];
	//this->arestrictedArea[1] = turret.arestrictedArea[1];
	this->turretAngle = turret.turretAngle;
	this->middleOfLockedArea = turret.middleOfLockedArea;


}

Turret::Turret(std::string ntype, float ndistanceFromShipOrigin, float nangleFromShipOrigin, std::vector<std::shared_ptr<Barrel>> nbarrels) : type(ntype), distanceFromShipOrigin(ndistanceFromShipOrigin),
angleFromShipOrigin(nangleFromShipOrigin), barrels(nbarrels)
{
	shipOrigin = sf::Vector2f(100, 100);
	shape.setPointCount(3);
	shape.setPoint(0, sf::Vector2f(0, -50));
	shape.setPoint(1, sf::Vector2f(-20, 0));
	shape.setPoint(2, sf::Vector2f(20, 0));
	shape.setFillColor(sf::Color(255, 0, 0));

	deleteOrigin();
	turretAngle = 0;
	rotationSpeed = 10;


		if (restrictedArea[0] > restrictedArea[1])
		{
			middleOfLockedArea = ((restrictedArea[0] + restrictedArea[1] + 360) / 2);
			middleOfLockedArea = middleOfLockedArea % 360;
		}
		else
		{

			middleOfLockedArea = ((restrictedArea[0] + restrictedArea[1]) / 2);
		}


}

Turret::Turret(std::string ntype, std::string nname, sf::ConvexShape turretBody, float parameters[3]) : type(ntype), name(nname)
{
	this->shape = turretBody;

	shipOrigin = sf::Vector2f(100,100);

	this->deleteOrigin();
	turretAngle = 0;
	this->rotationSpeed = parameters[0];
	this->restrictedArea[0] = parameters[1];
	this->restrictedArea[1] = parameters[2];



		if (restrictedArea[0] > restrictedArea[1])
		{
			middleOfLockedArea = ((restrictedArea[0] + restrictedArea[1] + 360) / 2);
			middleOfLockedArea = middleOfLockedArea % 360;
		}
		else
		{
			middleOfLockedArea = ((restrictedArea[0] + restrictedArea[1]) / 2);
		}




}

void Turret::updatePosition(float nshipAngle, float mouseAngle, sf::Vector2f nshipOrigin, float dTime)
{
	if (restrictedArea[0] == restrictedArea[1])
	{
		middleOfLockedArea = turretAngle + 180;
		middleOfLockedArea = middleOfLockedArea % 360;
	}
	//arestrictedArea[0] = changeAngle(restrictedArea[0], shipAngle);
	//arestrictedArea[1] = changeAngle(restrictedArea[1], shipAngle);
	//std::cout << restrictedArea[0] << ' ' << restrictedArea[1] << ' ' << changeAngle(turretAngle, shipAngle);
	
	float howManyDegreeToTurret = howManyDegreeFrom(changeAngle(middleOfLockedArea, shipAngle), changeAngle(turretAngle, shipAngle));
	float howManyDegreeToMouse = howManyDegreeFrom(changeAngle(middleOfLockedArea, shipAngle), mouseAngle);


	this->shipOrigin = nshipOrigin;
	this->shipAngle = nshipAngle;
	position = sf::Vector2f(distanceFromShipOrigin*sin(stopnieNaRadiany(changeAngle(shipAngle, angleFromShipOrigin))), -distanceFromShipOrigin * cos(stopnieNaRadiany(changeAngle(shipAngle, angleFromShipOrigin)))) + shipOrigin;
	this->shape.setPosition(position);


		if (howManyDegreeToTurret < howManyDegreeToMouse)
		{
			if ((howManyDegreeToMouse - howManyDegreeToTurret) < rotationSpeed*dTime)
			{
				//Dopisz skok do limitu obrotu
			}
			else
			{

				turretAngle = movable::changeAngle(turretAngle, rotationSpeed * dTime);
				if(restrictedArea[0] != restrictedArea[1])
				if (howManyDegreeFrom(restrictedArea[0], restrictedArea[1]) >= howManyDegreeFrom(restrictedArea[0], turretAngle))
				{
					//std::cout << ' ' << 1;
					turretAngle = movable::changeAngle(turretAngle, -1 * rotationSpeed * dTime);
				}
			}
		}
		else
		{
			if ((howManyDegreeToTurret - howManyDegreeToMouse) < rotationSpeed*dTime)
			{
				//nic nie robi bo jeden tik obrotu przekroczy� by porz�dan� pozycj�
				//to musisz przeskoczy� do tej pozycji
			}
			else
			{
				turretAngle = movable::changeAngle(turretAngle, -1 * rotationSpeed * dTime);
				if (restrictedArea[0] != restrictedArea[1])
				if (howManyDegreeFrom(restrictedArea[0], restrictedArea[1]) >= howManyDegreeFrom(restrictedArea[0], turretAngle))
				{
					//std::cout << ' ' << 2;

					turretAngle = movable::changeAngle(turretAngle, rotationSpeed * dTime);
				}
			}
		}
		//std::cout << std::endl;
	shape.setRotation(changeAngle(turretAngle, shipAngle));
	
	for (auto &barrel : barrels)
	{
		barrel->updatePosition(changeAngle(turretAngle, shipAngle), position);
	}
}

Barrel::Barrel()
{
}

Barrel::Barrel(std::string nname, sf::Vector2f npunkt) :name(nname)
{
	this->punkt = zamienNaPunktNaOkregu(npunkt, sf::Vector2f(0, 0));
}

Barrel::Barrel(std::string name, sf::Vector2f punkt, sf::ConvexShape shape, Bullet mainBulletType, unsigned int barrelSize, float reloadTime,float range):name(name),barrelSize(barrelSize),reloadTime(reloadTime), range(range)
{
	this->mainBulletType = std::make_shared<Bullet>(mainBulletType);
	this->shape = shape;
	this->punkt = zamienNaPunktNaOkregu(punkt, sf::Vector2f(0,0));
}

void Barrel::updatePosition(float TurretAngle, sf::Vector2f nTurretOrigin)
{
	this->shape.setPosition(sf::Vector2f(punkt.r*sin(stopnieNaRadiany(changeAngle(TurretAngle, punkt.a))), -punkt.r * cos(stopnieNaRadiany(changeAngle(TurretAngle, punkt.a)))) + nTurretOrigin);
	this->shape.setRotation(TurretAngle);
}

void Turret::updateRestrictedAreaBy(float moveRestricted)
{
	restrictedArea[0] += moveRestricted;
	restrictedArea[1] += moveRestricted;
	middleOfLockedArea += moveRestricted;

}
float Turret::getShipAngle()
{
	return shipAngle;
}
Turret::~Turret()
{
}

void Turret::draw(sf::RenderWindow& window)
{
	
	for (auto barrel : barrels)
	{
		window.draw(barrel->shape);
	}
	window.draw(shape);
}

float Turret::getAngleByWater()
{
	return this->shape.getRotation();
}

float Turret::getTurretAngle()
{
	return this->turretAngle;
}

std::vector<std::shared_ptr<sf::Vector2f>> Turret::getBarrelsPositionsByWater()
{
	std::vector<std::shared_ptr<sf::Vector2f>> tem;
	for (auto barrel : barrels)
	{
		tem.push_back(std::make_shared<sf::Vector2f>(barrel->shape.getPosition()));
	}
	return tem;
}

void Turret::shoot(std::shared_ptr<std::vector<jw::bulletInfo>> shootedBullets,float &shipAngle)
{
	if (timeFromShoot.getElapsedTime().asSeconds() < barrels.front()->reloadTime)return;
	for (auto & barrel : barrels)
	{
		(*shootedBullets).push_back(jw::bulletInfo{barrel->mainBulletType->getType(), barrel->getPosition(), float(fmod(this->turretAngle+shipAngle,360)), 0 });
	}
	timeFromShoot.restart();
}

void Turret::addPoint(int number, sf::Vector2f point)
{
	shape.setPoint(number, point);
}

void Turret::addBarrel(Barrel barrel, sf::Vector2f barrelPositionFromTurret)
{
	barrel.punkt = movable::zamienNaPunktNaOkregu(barrelPositionFromTurret-barrel.getOrigin(), sf::Vector2f(0,0));
	barrels.push_back(std::make_shared<Barrel>(barrel));
}

void Turret::setTurretPosition(sf::Vector2f turretPositionFromShip)
{
	punktNaOkregu temp= zamienNaPunktNaOkregu(turretPositionFromShip, sf::Vector2f(0,0));
	angleFromShipOrigin = temp.a;
	distanceFromShipOrigin = temp.r;
	/*
	distanceFromShipOrigin = sqrt(pow(turretPositionFromShip.x, 2) + pow(turretPositionFromShip.y, 2));

	angleFromShipOrigin =  (atan(turretPositionFromShip.y / turretPositionFromShip.x) / M_PI * 180);

	if (turretPositionFromShip.x >= 0 && turretPositionFromShip.y < 0)//ustala �e k�t 0 stopni jest skierowany w g�r�
	{
		angleFromShipOrigin += 90;
	}
	else if (turretPositionFromShip.x > 0 && turretPositionFromShip.y >= 0)
	{
		angleFromShipOrigin += 90;
	}
	else if (turretPositionFromShip.x <= 0 && turretPositionFromShip.y > 0)
	{
		angleFromShipOrigin += 270;
	}
	else
	{
		angleFromShipOrigin += 270;
	}*/
}

void Turret::setRotation(float angle)
{
	this->turretAngle = angle;
}

void Turret::updateHudTurret(std::vector<sf::Text>& content, unsigned int i)
{
	content[i].setString(std::to_string(this->barrels.front()->barrelSize) + "mm\n" + std::to_string(this->getLoadPercent()) + '%');
}

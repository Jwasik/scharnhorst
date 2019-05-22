#include "pch.h"
#include "turret.h"


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
	restrictedArea[1] = 0;
}

Turret::Turret(std::string ntype, sf::Vector2f nshipOrigin, float ndistanceFromShipOrigin, float nangleFromShipOrigin, std::vector<std::shared_ptr<Barrel>> nbarrels) : type(ntype), shipOrigin(nshipOrigin), distanceFromShipOrigin(ndistanceFromShipOrigin),
angleFromShipOrigin(nangleFromShipOrigin), barrels(nbarrels)
{
	shape.setPointCount(3);
	shape.setPoint(0, sf::Vector2f(0, -50));
	shape.setPoint(1, sf::Vector2f(-20, 0));
	shape.setPoint(2, sf::Vector2f(20, 0));
	shape.setFillColor(sf::Color(255, 0, 0));

	deleteOrigin();
	TurretAngle = 0;
	rotationSpeed = 10;
	restrictedArea[0] = 100;
	restrictedArea[1] = 260;

	if (restrictedArea[0] != restrictedArea[1])
		if (restrictedArea[0] > restrictedArea[1])
		{
			middleOfLockedArea = ((restrictedArea[0] + restrictedArea[1] + 360) / 2);
			middleOfLockedArea = middleOfLockedArea % 360;
		}
		else
		{
			middleOfLockedArea = ((restrictedArea[0] + restrictedArea[1]) / 2);
		}
	else middleOfLockedArea = 0;
}

void Turret::updatePosition(float nshipAngle, float mousAngle, sf::Vector2f nshipOrigin, float dTime)
{
	arestrictedArea[0] = changeAngle(restrictedArea[0], shipAngle);
	arestrictedArea[1] = changeAngle(restrictedArea[1], shipAngle);
	
	float howManyDegreeToTurret = howManyDegreeFrom(changeAngle(middleOfLockedArea, shipAngle), changeAngle(TurretAngle, shipAngle));
	float howManyDegreeToMouse = howManyDegreeFrom(changeAngle(middleOfLockedArea, shipAngle), mousAngle);


	shipOrigin = nshipOrigin;
	shipAngle = nshipAngle;
	position = sf::Vector2f(distanceFromShipOrigin*sin(stopnieNaRadiany(changeAngle(shipAngle, angleFromShipOrigin))), -distanceFromShipOrigin * cos(stopnieNaRadiany(changeAngle(shipAngle, angleFromShipOrigin)))) + shipOrigin;
	shape.setPosition(position);


		if (howManyDegreeToTurret < howManyDegreeToMouse)
		{
			if ((howManyDegreeToMouse - howManyDegreeToTurret) < rotationSpeed*dTime)
			{
				//nic nie robi bo jeden tik obrotu przekroczy³ by porz¹dan¹ pozycjê
				//to musisz przeskoczyæ do tej pozycji
			}
			else
			{
				TurretAngle = movable::changeAngle(TurretAngle, rotationSpeed * dTime);
				if (howManyDegreeFrom(arestrictedArea[0], arestrictedArea[1]) > howManyDegreeFrom(arestrictedArea[0], changeAngle(TurretAngle, shipAngle)))
				{
					TurretAngle = movable::changeAngle(TurretAngle, -1 * rotationSpeed * dTime);
				}
			}
		}
		else
		{
			if ((howManyDegreeToTurret - howManyDegreeToMouse) < rotationSpeed*dTime)
			{
				//nic nie robi bo jeden tik obrotu przekroczy³ by porz¹dan¹ pozycjê
				//to musisz przeskoczyæ do tej pozycji
			}
			else
			{
				TurretAngle = movable::changeAngle(TurretAngle, -1 * rotationSpeed * dTime);
				if (howManyDegreeFrom(arestrictedArea[0], arestrictedArea[1]) > howManyDegreeFrom(arestrictedArea[0], changeAngle(TurretAngle, shipAngle)))
				{
					TurretAngle = movable::changeAngle(TurretAngle, rotationSpeed * dTime);
				}
			}
		}
	shape.setRotation(changeAngle(TurretAngle, shipAngle));
	for (auto a : barrels)
	{
		a->updatePosition(changeAngle(TurretAngle, shipAngle), position);
	}
}

Barrel::Barrel()
{
}

Barrel::Barrel(sf::Vector2f npunkt, sf::ConvexShape nshape)
{
	this->shape = nshape;
	this->punkt = zamienNaPunktNaOkregu(npunkt, sf::Vector2f(0,0));
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

std::vector<std::shared_ptr<sf::Vector2f>> Turret::getBarrelsPositionsByWater()
{
	std::vector<std::shared_ptr<sf::Vector2f>> tem;
	for (auto barrel : barrels)
	{
		tem.push_back(std::make_shared<sf::Vector2f>(barrel->shape.getPosition()));
	}
	return tem;
	//Ja bym to wywali³ bo tylko zwraca pozycjê któr¹ mogê sobie sam wyci¹gn¹æ
}

void Turret::shoot(std::shared_ptr<std::vector<jw::bulletInfo>> shootedBullets)
{
	for (auto & barrel : barrels)
	{
		(*shootedBullets).push_back(jw::bulletInfo{ this->type, barrel->shape.getPosition(), this->TurretAngle, "noone" });
	}

}

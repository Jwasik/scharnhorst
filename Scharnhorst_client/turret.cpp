#include "pch.h"
#include "turret.h"


turret::turret()
{
	shape.setPointCount(3);
	shape.setPoint(0, sf::Vector2f(-40, 0));
	shape.setPoint(1, sf::Vector2f(40, 0));
	shape.setPoint(2, sf::Vector2f(0, -50));
	type = "";
	shipOrigin = sf::Vector2f(0, 0);
	distanceFromShipOrigin = 40;
	angleFromShipOrigin = 0;
	lockedArea[0] = 0;
	lockedArea[1] = 0;



}

turret::turret(std::string ntype, sf::Vector2f nshipOrigin, float ndistanceFromShipOrigin, float nangleFromShipOrigin) : type(ntype), shipOrigin(nshipOrigin), distanceFromShipOrigin(ndistanceFromShipOrigin),
angleFromShipOrigin(nangleFromShipOrigin)
{
	shape.setPointCount(3);
	shape.setPoint(0, sf::Vector2f(0, -50));
	shape.setPoint(1, sf::Vector2f(-20, 0));
	shape.setPoint(2, sf::Vector2f(20, 0));
	shape.setFillColor(sf::Color(255, 0, 0));

	deleteOrigin();
	turretAngle = 0;
	rotationSpeed = 30;
	lockedArea[0] = 100;
	lockedArea[1] = 260;

	if (lockedArea[0] != lockedArea[1])
		if (lockedArea[0] > lockedArea[1])
		{
			middleOfLockedArea = ((lockedArea[0] + lockedArea[1] + 360) / 2);
			middleOfLockedArea = middleOfLockedArea % 360;
		}
		else
		{
			middleOfLockedArea = ((lockedArea[0] + lockedArea[1]) / 2);
		}
	else
		middleOfLockedArea = 0;



}

void turret::updatePosition(float nshipAngle, float mousAngle, sf::Vector2f nshipOrigin, float dTime)
{
	this->shape.setRotation(mousAngle);
	
	float howManyDegreeToTurret = howManyDegreeFrom(middleOfLockedArea, turretAngle);
	float howManyDegreeToMouse = howManyDegreeFrom(middleOfLockedArea, mousAngle);
	std::cout  << std::endl;



	shipOrigin = nshipOrigin;
	shipAngle = nshipAngle;
	position = sf::Vector2f(distanceFromShipOrigin*sin(stopnieNaRadiany(shipAngle)), -distanceFromShipOrigin * cos(stopnieNaRadiany(shipAngle))) + shipOrigin;
	shape.setPosition(position);

	if (turretAngle != mousAngle)
	{
		if (howManyDegreeToTurret < howManyDegreeToMouse)
		{
			if ((howManyDegreeToMouse - howManyDegreeToTurret) < rotationSpeed*dTime)
			{
			}
			else
			{
				turretAngle = movable::changeAngle(turretAngle, rotationSpeed * dTime);
				if (turretAngle > lockedArea[0] && turretAngle < lockedArea[1])
				{
					turretAngle = movable::changeAngle(turretAngle, -1*rotationSpeed * dTime);
				}
				shape.setRotation(turretAngle);

			}

		}
		else
		{
			if ((howManyDegreeToTurret - howManyDegreeToMouse) < rotationSpeed*dTime)
			{
			}
			else
			{
				turretAngle = movable::changeAngle(turretAngle, -1 * rotationSpeed * dTime);
				if (turretAngle > lockedArea[0] && turretAngle < lockedArea[1])
				{
					turretAngle = movable::changeAngle(turretAngle, rotationSpeed * dTime);
				}

				shape.setRotation(turretAngle);

			}
		}
	}

	


}


turret::~turret()
{
}

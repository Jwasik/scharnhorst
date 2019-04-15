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
	rotationSpeed = 3;
	lockedArea[0] = 0;
	lockedArea[1] = 0;

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



}

void turret::updatePosition(float nshipAngle, float mousAngle, sf::Vector2f nshipOrigin, float dTime)
{
	float howManyDegreeToTurret = howManyDegreeFrom(middleOfLockedArea, turretAngle);
	float howManyDegreeToMouse = howManyDegreeFrom(middleOfLockedArea, mousAngle);

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
				shape.setRotation(mousAngle);
			}
			else
				shape.setRotation(turretAngle + rotationSpeed * dTime);

		}
		else
		{
			if ((howManyDegreeToTurret - howManyDegreeToMouse) < rotationSpeed*dTime)
			{
				shape.setRotation(mousAngle);
			}
			else
				shape.setRotation(turretAngle - rotationSpeed * dTime);
		}
	}




}


turret::~turret()
{
}

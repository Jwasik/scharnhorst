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
	restrictedArea[0] = 0;
	restrictedArea[1] = 0;



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
	else
		middleOfLockedArea = 0;



}

void turret::updatePosition(float nshipAngle, float mousAngle, sf::Vector2f nshipOrigin, float dTime)
{
	arestrictedArea[0] = changeAngle(restrictedArea[0], shipAngle);
	arestrictedArea[1] = changeAngle(restrictedArea[1], shipAngle);
	
	float howManyDegreeToTurret = howManyDegreeFrom(changeAngle(middleOfLockedArea, shipAngle), changeAngle(turretAngle, shipAngle));
	float howManyDegreeToMouse = howManyDegreeFrom(changeAngle(middleOfLockedArea, shipAngle), mousAngle);
	std::cout  << std::endl;


	shipOrigin = nshipOrigin;
	shipAngle = nshipAngle;
	position = sf::Vector2f(distanceFromShipOrigin*sin(stopnieNaRadiany(shipAngle)), -distanceFromShipOrigin * cos(stopnieNaRadiany(shipAngle))) + shipOrigin;
	shape.setPosition(position);


		if (howManyDegreeToTurret < howManyDegreeToMouse)
		{
			if ((howManyDegreeToMouse - howManyDegreeToTurret) < rotationSpeed*dTime)
			{
			}
			else
			{
				turretAngle = movable::changeAngle(turretAngle, rotationSpeed * dTime);
				if (howManyDegreeFrom(arestrictedArea[0], arestrictedArea[1]) > howManyDegreeFrom(arestrictedArea[0], changeAngle(turretAngle, shipAngle)))
				{
					turretAngle = movable::changeAngle(turretAngle, -1*rotationSpeed * dTime);
				}
				

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
				if (howManyDegreeFrom(arestrictedArea[0], arestrictedArea[1]) > howManyDegreeFrom(arestrictedArea[0], changeAngle(turretAngle, shipAngle)))
				{
					turretAngle = movable::changeAngle(turretAngle, rotationSpeed * dTime);
				}

				

			}
		}

	shape.setRotation(changeAngle(turretAngle, shipAngle));

	


}

void turret::updateRestrictedAreaBy(float moveRestricted)
{
	restrictedArea[0] += moveRestricted;
	restrictedArea[1] += moveRestricted;
	middleOfLockedArea += moveRestricted;

}

turret::~turret()
{
}

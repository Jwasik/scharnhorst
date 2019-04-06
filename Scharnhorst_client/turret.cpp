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

turret::turret(std::string ntype, sf::Vector2f nshipOrigin, float ndistanceFromShipOrigin, float nangleFromShipOrigin, float nlockedArea[],
	std::vector<sf::Vector2f> nbarrelPoints) : type(ntype), shipOrigin(nshipOrigin), distanceFromShipOrigin(ndistanceFromShipOrigin),
	angleFromShipOrigin(nangleFromShipOrigin), barrelPoints(nbarrelPoints)
{
	lockedArea[0] = nlockedArea[0];
	lockedArea[1] = nlockedArea[1];

}

void turret::updatePosition(float nshipAngle, float nturretAngle, sf::Vector2f nshipOrigin)
{
	shipOrigin = nshipOrigin;
	shipAngle = nshipAngle;
	turretAngle = nturretAngle;
	float angleSum = changeAngle(shipAngle, angleFromShipOrigin);
	position = sf::Vector2f(distanceFromShipOrigin*sin(angleSum), distanceFromShipOrigin*cos(angleSum)) + shipOrigin;


}


turret::~turret()
{
}

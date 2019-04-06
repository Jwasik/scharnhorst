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
	lockedArea[0] = 0;
	lockedArea[1] = 0;
	

}

void turret::updatePosition(float nshipAngle, float nturretAngle, sf::Vector2f nshipOrigin)
{
	shipOrigin = nshipOrigin;
	shipAngle = nshipAngle;
	turretAngle = nturretAngle;
	position = sf::Vector2f(distanceFromShipOrigin*sin(stopnieNaRadiany(shipAngle)), -distanceFromShipOrigin*cos(stopnieNaRadiany(shipAngle))) + shipOrigin;
	shape.setPosition(position);
	shape.setRotation(turretAngle);

}


turret::~turret()
{
}

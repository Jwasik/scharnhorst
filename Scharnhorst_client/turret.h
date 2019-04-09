#pragma once
#include "includes.h"
#include "movable.h"
class turret : public movable
{
	
protected:
	std::string type;
	float rotationSpeed; //w stopniach
	sf::Vector2f shipOrigin;
	float distanceFromShipOrigin;
	float angleFromShipOrigin;
	float lockedArea[2];//k¹rowy obszar w którym turret nie mo¿e przebywaæ (mniejszy k¹t, wiêkszy k¹t) 
	int middleOfLockedArea;
	std::vector<sf::Vector2f> barrelPoints; //Miejsca oznaczaj¹ce koñcu luf dzia³, gdzie powinny siê pojawiæ pociski
	sf::Vector2f position;


	float shipAngle;
	float turretAngle;



public:
	void updatePosition(float nshipAngle, float nturretAngle, sf::Vector2f nshipOrigin);
	turret();
	turret(std::string ntype, sf::Vector2f nshipOrigin, float ndistanceFromShipOrigin, float nangleFromShipOrigin);
	~turret();
};


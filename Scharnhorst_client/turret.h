#pragma once
#include "includes.h"
#include "movable.h"
class turret : public movable
{

protected:



	std::string type;
	float rotationSpeed; //w stopniach/sekundê
	sf::Vector2f shipOrigin;
	float distanceFromShipOrigin;
	float angleFromShipOrigin;
	float shipAngle;
	float restrictedArea[2];//k¹rowy obszar w którym turret nie mo¿e przebywaæ (mniejszy k¹t, wiêkszy k¹t) 
	float arestrictedArea[2];
	int middleOfLockedArea;
	std::vector<std::shared_ptr<sf::Vector2f>> barrels; //Miejsca oznaczaj¹ce koñcu luf dzia³, gdzie powinny siê pojawiæ pociski
	sf::Vector2f position;




public:
	float turretAngle;

	void updatePosition(float nshipAngle, float nturretAngle, sf::Vector2f nshipOrigin, float dTime);
	turret();
	turret(std::string ntype, sf::Vector2f nshipOrigin, float ndistanceFromShipOrigin, float nangleFromShipOrigin);
	~turret();
	void updateRestrictedAreaBy(float moveRestricted);
	float getShipAngle();
};


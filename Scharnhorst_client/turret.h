#pragma once
#include "includes.h"
#include "movable.h"
class turret : public movable
{
	
protected:
	std::string type;
	sf::Vector2f shipOrigin;
	float distanceFromShipOrigin;
	float angleFromShipOrigin;
	float lockedArea[2];//k¹rowy obszar w którym turret nie mo¿e przebywaæ (mniejszy k¹t, wiêkszy k¹t) 
	std::vector<sf::Vector2f> barrelPoints; //Miejsca oznaczaj¹ce koñcu luf dzia³, gdzie powinny siê pojawiæ pociski
	sf::Vector2f position;


	float shipAngle;
	float turretAngle;



public:
	void updatePosition(float, float, sf::Vector2f);
	turret();
	turret(std::string , sf::Vector2f , float , float , float[], std::vector<sf::Vector2f> );
	~turret();
};


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
	float lockedArea[2];//k�rowy obszar w kt�rym turret nie mo�e przebywa� (mniejszy k�t, wi�kszy k�t) 
	int middleOfLockedArea;
	std::vector<sf::Vector2f> barrelPoints; //Miejsca oznaczaj�ce ko�cu luf dzia�, gdzie powinny si� pojawi� pociski
	sf::Vector2f position;


	float shipAngle;
	float turretAngle;



public:
	void updatePosition(float nshipAngle, float nturretAngle, sf::Vector2f nshipOrigin);
	turret();
	turret(std::string ntype, sf::Vector2f nshipOrigin, float ndistanceFromShipOrigin, float nangleFromShipOrigin);
	~turret();
};


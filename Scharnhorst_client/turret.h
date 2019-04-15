#pragma once
#include "includes.h"
#include "movable.h"
class turret : public movable
{

protected:



	std::string type;
	float rotationSpeed; //w stopniach/sekund�
	sf::Vector2f shipOrigin;
	float distanceFromShipOrigin;
	float angleFromShipOrigin;
	float lockedArea[2];//k�rowy obszar w kt�rym turret nie mo�e przebywa� (mniejszy k�t, wi�kszy k�t) 
	int middleOfLockedArea;
	std::vector<std::shared_ptr<sf::Vector2f>> barrels; //Miejsca oznaczaj�ce ko�cu luf dzia�, gdzie powinny si� pojawi� pociski
	sf::Vector2f position;


	float shipAngle;



public:
	float turretAngle;

	void updatePosition(float nshipAngle, float nturretAngle, sf::Vector2f nshipOrigin, float dTime);
	turret();
	turret(std::string ntype, sf::Vector2f nshipOrigin, float ndistanceFromShipOrigin, float nangleFromShipOrigin);
	~turret();
};


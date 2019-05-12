#pragma once
#include "includes.h"
#include "movable.h"

struct barrel : public movable
{
public:
	Hitbox::punktNaOkregu punkt;

	barrel();
	barrel(sf::Vector2f point, sf::ConvexShape shape);
	void updatePosition(float turretAngle, sf::Vector2f turretOrigin);

};

class turret : public movable
{

protected:



	std::string type;
	float rotationSpeed; //w stopniach/sekund�
	sf::Vector2f shipOrigin;
	float distanceFromShipOrigin;
	float angleFromShipOrigin;
	float shipAngle;
	float restrictedArea[2];//k�rowy obszar w kt�rym turret nie mo�e przebywa� (mniejszy k�t, wi�kszy k�t) 
	float arestrictedArea[2];
	int middleOfLockedArea;
	sf::Vector2f position;


	vector< std::shared_ptr<barrel>> barrels; //Miejsca oznaczaj�ce ko�cu luf dzia�, gdzie powinny si� pojawi� pociski


public:


	float turretAngle;
	void draw(sf::RenderWindow& window);
	void updatePosition(float nshipAngle, float nturretAngle, sf::Vector2f nshipOrigin, float dTime);
	turret();
	turret(std::string ntype, sf::Vector2f nshipOrigin, float ndistanceFromShipOrigin, float nangleFromShipOrigin, vector<shared_ptr<barrel>> nbarrels);
	~turret();
	void updateRestrictedAreaBy(float moveRestricted);
	float getShipAngle();
};


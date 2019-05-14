#pragma once
#include "includes.h"
#include "movable.h"

struct barrel : public movable
{
public:
	Hitbox::punktNaOkregu punkt;

	barrel();
	barrel(sf::Vector2f point, sf::ConvexShape shape);
	void updatePosition(float TurretAngle, sf::Vector2f TurretOrigin);
};

class Turret : public movable
{
protected:

	std::string type;
	float rotationSpeed; //w stopniach/sekund�
	sf::Vector2f shipOrigin;
	float distanceFromShipOrigin;
	float angleFromShipOrigin;
	float shipAngle;
	float restrictedArea[2];//k�rowy obszar w kt�rym Turret nie mo�e przebywa� (mniejszy k�t, wi�kszy k�t) 
	float arestrictedArea[2];
	int middleOfLockedArea;
	sf::Vector2f position;

	std::vector< std::shared_ptr<barrel>> barrels; //Miejsca oznaczaj�ce ko�cu luf dzia�, gdzie powinny si� pojawi� pociski

public:

	float TurretAngle;
	void draw(sf::RenderWindow& window);
	void updatePosition(float nshipAngle, float nTurretAngle, sf::Vector2f nshipOrigin, float dTime);
	Turret();
	Turret(std::string ntype, sf::Vector2f nshipOrigin, float ndistanceFromShipOrigin, float nangleFromShipOrigin, std::vector<std::shared_ptr<barrel>> nbarrels);
	~Turret();
	void updateRestrictedAreaBy(float moveRestricted);
	float getShipAngle();
	float getAngleByWater();
	std::vector<std::shared_ptr<sf::Vector2f>> getBarrelsPositionsByWater();

	std::vector<std::shared_ptr<bullet>> SHOOT();

};


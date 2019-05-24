#pragma once
#include "includes.h"
#include "movable.h"

struct Barrel : public movable
{
public:
	std::string name;
	Hitbox::punktNaOkregu punkt; //po chuj to jak barrel nie ma hitboxa? - punktNaOkr�gu pozwala przemieszczac punkt na okr�gu a barrel takim punktem jest, o �rodku turret, tak samo jak turret takim jest o �rodku statek 
	Barrel();
	Barrel(std::string name, sf::Vector2f point);
	Barrel(std::string name, sf::Vector2f point, sf::ConvexShape shape);
	void updatePosition(float TurretAngle, sf::Vector2f TurretOrigin);
};

class Turret : public movable
{
protected:

	std::string type;
	std::string name;
	
	float rotationSpeed; //w stopniach/sekund�
	
	sf::Vector2f shipOrigin;
	float distanceFromShipOrigin;
	float angleFromShipOrigin;
	float shipAngle;
	float restrictedArea[2];//k�rowy obszar w kt�rym Turret nie mo�e przebywa� (mniejszy k�t, wi�kszy k�t) 
	float arestrictedArea[2];
	int middleOfLockedArea;
	sf::Vector2f position;



public:
	std::vector< std::shared_ptr<Barrel>> barrels; //Miejsca oznaczaj�ce ko�cu luf dzia�, gdzie powinny si� pojawi� pociski

	float TurretAngle;
	void draw(sf::RenderWindow& window);
	void updatePosition(float nshipAngle, float nTurretAngle, sf::Vector2f nshipOrigin, float dTime);
	Turret();
	Turret(std::string ntype, float ndistanceFromShipOrigin, float nangleFromShipOrigin, std::vector<std::shared_ptr<Barrel>> nbarrels);
	Turret(std::string ntype, std::string nname, sf::Vector2f turretPositionFromShip, unsigned short pointCount, float parameters[3]);
	~Turret();
	void updateRestrictedAreaBy(float moveRestricted);
	float getShipAngle();
	float getAngleByWater();
	std::vector<std::shared_ptr<sf::Vector2f>> getBarrelsPositionsByWater();
	void shoot(std::shared_ptr<std::vector<jw::bulletInfo>>);
	void addPoint(int number, sf::Vector2f point);
};


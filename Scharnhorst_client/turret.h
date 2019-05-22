#pragma once
#include "includes.h"
#include "movable.h"

struct Barrel : public movable
{
public:
	Hitbox::punktNaOkregu punkt; //po chuj to jak barrel nie ma hitboxa?
	Barrel();
	Barrel(sf::Vector2f point, sf::ConvexShape shape);
	void updatePosition(float TurretAngle, sf::Vector2f TurretOrigin);
};

class Turret : public movable
{
protected:

	std::string type;
	float rotationSpeed; //w stopniach/sekundê
	sf::Vector2f shipOrigin;
	float distanceFromShipOrigin;
	float angleFromShipOrigin;
	float shipAngle;
	float restrictedArea[2];//k¹rowy obszar w którym Turret nie mo¿e przebywaæ (mniejszy k¹t, wiêkszy k¹t) 
	float arestrictedArea[2];
	int middleOfLockedArea;
	sf::Vector2f position;

	std::vector< std::shared_ptr<Barrel>> barrels; //Miejsca oznaczaj¹ce koñcu luf dzia³, gdzie powinny siê pojawiæ pociski

public:

	float TurretAngle;
	void draw(sf::RenderWindow& window);
	void updatePosition(float nshipAngle, float nTurretAngle, sf::Vector2f nshipOrigin, float dTime);
	Turret();
	Turret(std::string ntype, sf::Vector2f nshipOrigin, float ndistanceFromShipOrigin, float nangleFromShipOrigin, std::vector<std::shared_ptr<Barrel>> nbarrels);
	Turret(std::string ntype, sf::Vector2f nshipOrigin, float ndistanceFromShipOrigin, float nangleFromShipOrigin);
	~Turret();
	void updateRestrictedAreaBy(float moveRestricted);
	float getShipAngle();
	float getAngleByWater();
	std::vector<std::shared_ptr<sf::Vector2f>> getBarrelsPositionsByWater();
	void shoot(std::shared_ptr<std::vector<jw::bulletInfo>>);

};


#pragma once
#include "includes.h"
#include "movable.h"

struct Barrel : public movable
{

public:
	unsigned int barrelSize;
	std::shared_ptr<Bullet> mainBulletType;
	std::string name;
	Hitbox::punktNaOkregu punkt;
	Barrel();
	Barrel(std::string name, sf::Vector2f point);
	Barrel(std::string name, sf::Vector2f point, sf::ConvexShape shape, Bullet, unsigned int);
	void updatePosition(float TurretAngle, sf::Vector2f TurretOrigin);
};

class Turret : public movable
{
protected:

	std::string type;
	std::string name;
	
	float rotationSpeed; //w stopniach/sekundê
	
	sf::Vector2f shipOrigin;
	float distanceFromShipOrigin;
	float angleFromShipOrigin;
	float shipAngle;
	float restrictedArea[2];//k¹rowy obszar w którym Turret nie mo¿e przebywaæ (mniejszy k¹t, wiêkszy k¹t) 
	float arestrictedArea[2];
	int middleOfLockedArea;
	sf::Vector2f position;



public:
	std::vector< std::shared_ptr<Barrel>> barrels; //Miejsca oznaczaj¹ce koñcu luf dzia³, gdzie powinny siê pojawiæ pociski

	float TurretAngle;
	void draw(sf::RenderWindow& window);
	void updatePosition(float nshipAngle, float nTurretAngle, sf::Vector2f nshipOrigin, float dTime);
	Turret();
	Turret(std::string ntype, float ndistanceFromShipOrigin, float nangleFromShipOrigin, std::vector<std::shared_ptr<Barrel>> nbarrels);
	Turret(std::string ntype, std::string nname, sf::ConvexShape turretBody, float parameters[3]);
	~Turret();
	void updateRestrictedAreaBy(float moveRestricted);
	float getShipAngle();
	float getAngleByWater();
	std::vector<std::shared_ptr<sf::Vector2f>> getBarrelsPositionsByWater();
	void shoot(std::shared_ptr<std::vector<jw::bulletInfo>>);
	void addPoint(int number, sf::Vector2f point);
	void addBarrel(Barrel);
	void setTurretPosition(sf::Vector2f);
};


#pragma once
#include "includes.h"
#include "movable.h"

struct Barrel : public movable
{

public:
	unsigned int barrelSize;
	float length;//D�ugo�� lufy
	float range;//zasi�g strza�u
	std::shared_ptr<Bullet> mainBulletType;
	std::string name;
	punktNaOkregu punkt;
	Barrel();
	Barrel(std::string name, sf::Vector2f point);
	Barrel(std::string name, sf::Vector2f point, sf::ConvexShape shape, Bullet, unsigned int,float,float);
	void updatePosition(float TurretAngle, sf::Vector2f TurretOrigin);
	float reloadTime;
};

class Turret : public movable
{
public:
	sf::Clock timeFromShoot;

	

	sf::Vector2f shipOrigin;
	sf::Vector2f position;
	std::vector< std::shared_ptr<Barrel>> barrels; //Miejsca oznaczaj�ce ko�cu luf dzia�, gdzie powinny si� pojawi� pociski

	float rotationSpeed; //w stopniach/sekund�
	float distanceFromShipOrigin;
	float angleFromShipOrigin;
	float shipAngle;
	float restrictedArea[2];//k�towy obszar w kt�rym Turret nie mo�e przebywa� (mniejszy k�t, wi�kszy k�t) 
	//float arestrictedArea[2];
	float turretAngle;
	int middleOfLockedArea;

	unsigned int getLoadPercent();


public:
	std::string type;
	std::string name;
	Turret();
	Turret(const Turret & Turret);
	Turret(std::string ntype, float ndistanceFromShipOrigin, float nangleFromShipOrigin, std::vector<std::shared_ptr<Barrel>> nbarrels);
	Turret(std::string ntype, std::string nname, sf::ConvexShape turretBody, float parameters[3]);
	~Turret();

	void draw(sf::RenderWindow& window); 
	void updatePosition(float nshipAngle, float nTurretAngle, sf::Vector2f nshipOrigin, float dTime);
	
	std::vector<std::shared_ptr<sf::Vector2f>> getBarrelsPositionsByWater();
	void updateRestrictedAreaBy(float moveRestricted);
	float getShipAngle();
	float getAngleByWater();
	float getTurretAngle();
	void shoot(std::shared_ptr<std::vector<jw::bulletInfo>>, float&);
	void addPoint(int number, sf::Vector2f point);
	void addBarrel(Barrel, sf::Vector2f);
	void setTurretPosition(sf::Vector2f);
	void setRestrictedArea(float[2]);
	void setRotation(float);
	void updateHudTurret(std::vector<sf::Text>&,unsigned int);
};


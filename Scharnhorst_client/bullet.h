#pragma once
#include "includes.h"
#include "movable.h"
class Bullet : public movable
{
protected:
	unsigned int bulletId;
	unsigned int ownerId;
	std::string type;
	float speed;
	float damage;
	float angle;
	float caliber;
	sf::Vector2f movementVector;//przechowuje wektor przesuniêcia z altualn¹ prêdkoœci¹ i k¹tem w czasie 1 sekundy

public:
	odcinek tracer;

	Bullet();
	Bullet(const Bullet&);
	Bullet(std::string type, sf::ConvexShape body, float speed, float damage, float angle,int caliber ,sf::Vector2f punkt);
	Bullet(std::string,sf::ConvexShape, float, float, int);

	void calculateMovementVector();
	void fly(double deltaTime);	
	void draw(sf::RenderWindow&);
	void setBulletInfo(const jw::bulletInfo&);
	int getCaliber();
	void setCaliber(int);
	void setId(unsigned int);
	unsigned int getId();
	void setOwnerId(unsigned int);
	unsigned int getOwnerId();

	std::string getType();
	
	~Bullet();
};


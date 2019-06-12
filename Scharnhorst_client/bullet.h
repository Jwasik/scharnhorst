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
	float distanceToEnd;
	float range;
	sf::Vector2f movementVector;//przechowuje wektor przesuni�cia z altualn� pr�dko�ci� i k�tem w czasie 1 sekundy

public:
	odcinek tracer;

	Bullet();
	Bullet(const Bullet&);
	Bullet(std::string type, sf::ConvexShape body, float speed, float damage, float angle, int caliber, sf::Vector2f punkt);
	Bullet(std::string, sf::ConvexShape, float, float, int);

	void calculateMovementVector();
	void fly(double deltaTime);
	void draw(sf::RenderWindow&);
	void setBulletInfo(const jw::bulletInfo&);
	void setCaliber(int);
	void setId(unsigned int);
	void setOwnerId(unsigned int);
	void setRange(float);
	bool done();
	unsigned int getOwnerId();
	unsigned int getId();
	int getCaliber();

	std::string getType();

	~Bullet();
};


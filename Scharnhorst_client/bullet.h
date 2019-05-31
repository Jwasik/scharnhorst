#pragma once
#include "includes.h"
#include "movable.h"
class Bullet : public movable
{
protected:
	std::string type;
	float speed;
	float damage;
	float angle;
	float caliber;
	sf::Vector2f movementVector;//przechowuje wektor przesuni�cia z altualn� pr�dko�ci� i k�tem w czasie 1 sekundy

public:
	Hitbox::odcinek tracer;

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
	std::string getType();
	
	~Bullet();
};


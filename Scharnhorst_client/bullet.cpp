#include "pch.h"
#include "bullet.h"

void Bullet::fly(double deltaTime)
{
	float distance = speed * deltaTime;
	this->tracer = Hitbox::odcinek(this->tracer.b, this->tracer.b + sf::Vector2f(distance * sin(stopnieNaRadiany(angle)), -distance * cos(stopnieNaRadiany(angle))));
	this->shape.setPosition(tracer.b);

}

void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(this->tracer.line);
	window.draw(this->shape);
}

Bullet::Bullet(std::string ntype, sf::ConvexShape nbody, float nspeed, float ndamage, float nangle, sf::Vector2f punkt) : type(ntype), speed(nspeed), damage(ndamage), angle(nangle)
{
	this->shape = nbody;
	this->tracer.b = punkt;
	this->shape.setRotation(angle);
	this->shape.setPosition(tracer.b);
}

Bullet::Bullet(sf::ConvexShape body, float speed, float damage)
{
	this->shape = body;
	this->speed = speed;
	this->damage = damage;
}

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

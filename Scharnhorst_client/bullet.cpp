#include "pch.h"
#include "bullet.h"

void bullet::fly(double deltaTime)
{
	float distance = speed * deltaTime;
	this->tracer = Hitbox::odcinek(this->tracer.b, this->tracer.b + sf::Vector2f(distance * sin(stopnieNaRadiany(angle)), -distance * cos(stopnieNaRadiany(angle))));
	this->shape.setPosition(tracer.b);

}

void bullet::draw(sf::RenderWindow& window)
{
	window.draw(this->tracer.line);
	window.draw(this->shape);

}

bullet::bullet(std::string ntype, sf::ConvexShape nbody, float nspeed, float ndamage, float nangle, sf::Vector2f punkt) : type(ntype), speed(nspeed), damage(ndamage), angle(nangle)
{
	this->shape = nbody;
	this->tracer.b = punkt;
	this->shape.setRotation(angle);
	this->shape.setPosition(tracer.b);


}

bullet::bullet()
{
}


bullet::~bullet()
{
}

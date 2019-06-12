#include "pch.h"
#include "bullet.h"

void Bullet::calculateMovementVector()
{
	movementVector.x = sin(stopnieNaRadiany(this->angle));
	movementVector.y = cos(stopnieNaRadiany(this->angle));
}

bool Bullet::fly(double deltaTime)
{
	float distance = speed * deltaTime*8;
	distanceToEnd -= distance;

	this->shape.setPosition(this->shape.getPosition() + sf::Vector2f(distance * movementVector.x, -distance * movementVector.y));

	this->tracer.punkt1 = this->tracer.punkt2;
	this->tracer.punkt2 = this->shape.getPosition();
	tracer.updateVisual();
}

void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(this->tracer.line);
	window.draw(this->shape);
}

void Bullet::setBulletInfo(const jw::bulletInfo &info)
{
	this->type = info.name;
	this->setPosition(info.position);
	this->angle = info.angle;
	this->shape.setRotation(info.angle);
	this->tracer.punkt1 = info.position;
	this->tracer.punkt2 = info.position;
	this->bulletId = info.bulletId;
	this->ownerId = info.ownerId;
}

int Bullet::getCaliber()
{
	return this->caliber;
}

void Bullet::setCaliber(int caliber)
{
	this->caliber = caliber;
}

void Bullet::setId(unsigned int id)
{
	this->bulletId = id;
}

unsigned int Bullet::getId()
{
	return this->bulletId;
}

void Bullet::setOwnerId(unsigned int id)
{
	this->ownerId = id;
}

unsigned int Bullet::getOwnerId()
{
	return this->ownerId;
}

std::string Bullet::getType()
{
	return this->type;
}

Bullet::Bullet(std::string type, sf::ConvexShape body, float speed, float damage, float angle, int caliber ,sf::Vector2f punkt, float ndistanceToEnd) : type(type), speed(speed), damage(damage), angle(angle), caliber(caliber), distanceToEnd(ndistanceToEnd)
{
	this->shape = body;
	this->tracer.punkt2 = punkt;
	this->shape.setRotation(angle);
	this->shape.setPosition(tracer.punkt2);
	this->calculateMovementVector();
}

Bullet::Bullet(std::string type,sf::ConvexShape body, float speed, float damage, int caliber) : type(type), speed(speed), damage(damage), caliber(caliber)
{
	this->shape = body;
	this->calculateMovementVector();
}

Bullet::Bullet()
{
}

Bullet::Bullet(const Bullet &origin)
{
	this->type = origin.type;
	this->speed = origin.speed;
	this->damage = origin.damage;
	this->caliber = origin.caliber;
	this->angle = origin.angle;
	this->shape = origin.shape;
	this->tracer = origin.tracer;
	this->calculateMovementVector();
}

void Bullet::setRange(float range)
{
	this->range = range*8;
	this->distanceToEnd = range*8;
}

bool Bullet::done()
{
	if (distanceToEnd <= 0)return true;
	return false;
}

Bullet::~Bullet()
{
}


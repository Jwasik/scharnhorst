#pragma once
#include "pch.h"
#include "shallow.h"

shallow::shallow()
{
	/*std::shared_ptr <std::vector<std::shared_ptr<sf::Vector2f>>> tpoints = std::make_shared<std::vector<std::shared_ptr<sf::Vector2f>>>();

	tpoints->push_back(std::make_shared<sf::Vector2f>(sf::Vector2f(-300, -300)));
	tpoints->push_back(std::make_shared<sf::Vector2f>(sf::Vector2f(300, -300)));
	tpoints->push_back(std::make_shared<sf::Vector2f>(sf::Vector2f(300, 300)));
	tpoints->push_back(std::make_shared<sf::Vector2f>(sf::Vector2f(-300, 300)));
	this->unmovable::unmovable(tpoints);

	this->body = hitbox(&shape);
	this->setFillColor(sf::Color( 200, 0, 200));*/
}

shallow::shallow(std::shared_ptr <std::vector<std::shared_ptr<sf::Vector2f>>> points) : unmovable(points)
{
	this->body = hitbox(&shape);
}

bool shallow::touching(odcinek *line)
{
	std::cout << "xd" << std::endl;
	return this->body.intersects(line);
}

void shallow::setPosition(sf::Vector2f nposition)
{
	this->shape.setPosition(nposition);
	this->body.setPosition(nposition);
}

void shallow::updateHitbox()
{
	this->body = hitbox(&shape);
}

void shallow::updateShape()
{
	this->unmovable::updateShape();
	this->updateHitbox();

}

void shallow::action(odcinek *line)
{
	this->touching(line);
}
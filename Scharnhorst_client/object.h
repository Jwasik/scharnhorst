
#pragma once
#include "movable.h"

class object : public movable 
{
private:
	Hitbox body;

public:
	std::vector<std::shared_ptr<sf::Vector2f>> points;
	object();
	object(std::shared_ptr <std::vector<std::shared_ptr<sf::Vector2f>>> points);
	void setFillColor(sf::Color color);
	void setPointCount(int count);
	void changePoint(int count, std::shared_ptr<sf::Vector2f > position);
	void updateShape();
};


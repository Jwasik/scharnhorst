
#pragma once
#include "movable.h"

class nemovable : public movable 
{
private:
	//Hitbox body;

public:
	std::vector<std::shared_ptr<sf::Vector2f>> points;
	nemovable();
	nemovable(std::shared_ptr <std::vector<std::shared_ptr<sf::Vector2f>>> points);
	void setFillColor(sf::Color color);//phusical
	void setPointCount(int count);//phusical
	void changePoint(int count, std::shared_ptr<sf::Vector2f > position);//phusical//po co to wogle?
	void updateShape();
};


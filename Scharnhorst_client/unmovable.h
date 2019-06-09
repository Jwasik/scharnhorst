#include "pch.h"
#pragma once
#include "movable.h"

class unmovable : public movable
{
private:


public:
	std::vector<std::shared_ptr<sf::Vector2f>> points; //wszystkie punkty convexshapeu

	unmovable();
	unmovable(std::shared_ptr <std::vector<std::shared_ptr<sf::Vector2f>>> points);
	void setFillColor(sf::Color color);//phusical
	void setPointCount(int count);//phusical
	void changePoint(int count, std::shared_ptr<sf::Vector2f > position);//phusical//po co to wogle?
	virtual void updateShape();
	virtual void action() = 0;



};


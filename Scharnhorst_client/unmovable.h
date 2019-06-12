#include "pch.h"
#pragma once
#include "movable.h"

class unmovable : public movable
{
private:

public:
	std::string type;

	std::vector<std::shared_ptr<sf::Vector2f>> points; //wszystkie punkty convexshapeu

	unmovable();
	unmovable(std::shared_ptr <std::vector<std::shared_ptr<sf::Vector2f>>> points);
	void setFillColor(sf::Color color);//phusical
	void setPointCount(int count);//phusical
	void changePoint(int count, std::shared_ptr<sf::Vector2f > position);//phusical//po co to wogle?
	virtual void updateShape();
	virtual bool touch(odcinek *line) = 0;
	virtual void drawHitbox(sf::RenderWindow &window) = 0;
	virtual std::string returnType() = 0;
	void addPoint(std::shared_ptr<sf::Vector2f> position);


};


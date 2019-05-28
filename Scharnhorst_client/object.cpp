#include "pch.h"
#include "nemovable.h"

nemovable::nemovable()
{
}

nemovable::nemovable(std::shared_ptr <std::vector<std::shared_ptr<sf::Vector2f>>> npoints) : points(*npoints)
{	
	updateShape();
}

void nemovable::setFillColor(sf::Color color)
{
	this->shape.setFillColor(color);
}

void nemovable::setPointCount(int count)
{
	this->shape.setPointCount(count);
}

void nemovable::changePoint(int count, std::shared_ptr<sf::Vector2f> position)
{
	this->shape.setPoint(count, *position);
}

void nemovable::updateShape()
{
	unsigned int counter = 0;
	setPointCount(points.size());
	for (auto point : points)
	{
		changePoint(counter, point);
		counter++;
	}
	body = Hitbox(this->shape);
}
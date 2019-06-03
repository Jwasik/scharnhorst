#include "pch.h"
#include "unmovable.h"

unmovable::unmovable()
{
}

unmovable::unmovable(std::shared_ptr <std::vector<std::shared_ptr<sf::Vector2f>>> npoints) : points(*npoints)
{
	updateShape();
}

void unmovable::setFillColor(sf::Color color)
{
	this->shape.setFillColor(color);
}

void unmovable::setPointCount(int count)
{
	this->shape.setPointCount(count);
}

void unmovable::changePoint(int count, std::shared_ptr<sf::Vector2f> position)
{
	this->shape.setPoint(count, *position);
}

void unmovable::updateShape()
{
	unsigned int counter = 0;
	setPointCount(points.size());
	for (auto point : points)
	{
		changePoint(counter, point);
		counter++;
	}
	//body = Hitbox(this->shape);
}
#include "pch.h"
#include "object.h"

object::object()
{
}

object::object(std::vector<std::shared_ptr<sf::Vector2f>> npoints) : points(npoints)
{	
	updateShape();
}

void object::setFillColor(sf::Color color)
{
	this->shape.setFillColor(color);
}

void object::setPointCount(int count)
{
	this->shape.setPointCount(count);
}

void object::changePoint(int count, std::shared_ptr<sf::Vector2f> position)
{
	this->shape.setPoint(count, *position);
}

void object::updateShape()
{
	int counter = 0;
	setPointCount(points.size());
	for (auto point : points)
	{
		changePoint(counter, point);
		counter++;
	}
	body = Hitbox(this->shape);
}
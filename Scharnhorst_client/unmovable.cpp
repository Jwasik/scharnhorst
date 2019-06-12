#include "pch.h"
#include "unmovable.h"

unmovable::unmovable()
{
}

unmovable::unmovable(std::shared_ptr <std::vector<std::shared_ptr<sf::Vector2f>>> npoints) : points(*npoints)
{
	this->unmovable::updateShape();
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
	//this->points.push_back(position);


}

void unmovable::addPoint(std::shared_ptr<sf::Vector2f> position)
{
	this->points.push_back(position);
	setPointCount(this->shape.getPointCount() + 1);
	this->unmovable::updateShape();

}

void unmovable::updateShape()
{
	unsigned int counter = 0;
	this->setPointCount(points.size());
	for (auto point : points)
	{
		this->changePoint(counter, point);
		counter++;
	}
}
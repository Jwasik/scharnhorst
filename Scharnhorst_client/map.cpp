#include "pch.h"
#include "map.h"

map::map()
{
	;
}

void map::addIsland(std::shared_ptr<unmovable> newIsle)
{
	this->islands.push_back(newIsle);

}

void map::draw(sf::RenderWindow &window)
{
	for (auto isle : this->islands)
	{
		isle->physical::draw(window);
	}
}
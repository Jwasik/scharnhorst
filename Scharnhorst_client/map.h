#include "pch.h"
#pragma once
#include "unmovable.h"

class map
{
public:
	map();

	std::vector<std::shared_ptr<unmovable>> islands;

	void addIsland(std::shared_ptr<unmovable>);
	void draw(sf::RenderWindow &window);

};
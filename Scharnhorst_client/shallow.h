#pragma once
#include "unmovable.h"
#include "Hitbox.h"


class shallow : public unmovable
{
public:
	hitbox body;


public:
	bool touching(odcinek *line);
	shallow();
	shallow(std::shared_ptr <std::vector<std::shared_ptr<sf::Vector2f>>> points);
	void setPosition(sf::Vector2f position);

};
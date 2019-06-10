#pragma once
#include "unmovable.h"
#include "Hitbox.h"



class shallow : public unmovable
{
public:
	hitbox body;


public:
	shallow();
	shallow(std::shared_ptr <std::vector<std::shared_ptr<sf::Vector2f>>> points, bool stopsBullets, std::map<std::string, sf::Texture>* textures);
	void setPosition(sf::Vector2f position);
	void updateHitbox();
	void updateShape();
	bool touch(odcinek *line);
	void drawHitbox(sf::RenderWindow &window);
};
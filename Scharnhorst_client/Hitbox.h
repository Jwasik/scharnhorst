#pragma once


class hitbox : public odcinek
{
public:
	std::vector<odcinek> odcinki;

public:
	//kolizja z odcinkiem

	hitbox(sf::ConvexShape *shape);
	hitbox();
	bool intersects(odcinek *line);
	void setPosition(sf::Vector2f position);
	void updateVisual();

};
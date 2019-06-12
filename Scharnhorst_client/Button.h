#pragma once
#include "includes.h"
class Button 
{
protected:
	sf::RectangleShape shape;
	sf::Text text;
	std::shared_ptr<sf::Font> font;

	void updateTextPosition();
public:
	Button();
	Button(std::string, std::shared_ptr<sf::Font>);
	~Button();

	void setPosition(sf::Vector2f);
	void move(sf::Vector2f);
	void draw(sf::RenderWindow&);
	void setActive();
	void setText(std::string);
	void setUnActive();
	void setMarked();
	void setUnMarked();
	sf::FloatRect getGlobalBounds();
};


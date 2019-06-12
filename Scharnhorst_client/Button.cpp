#include "pch.h"
#include "Button.h"


void Button::updateTextPosition()
{
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
	textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(shape.getPosition()));
}

Button::Button()
{

}

Button::Button(std::string text, std::shared_ptr<sf::Font> font) : font(font)
{
	this->text.setFont((*this->font));
	this->text.setString(text);
	this->text.setFillColor(sf::Color::Red);

	this->text.setCharacterSize(20);
	this->shape.setSize(sf::Vector2f(400,100));
	this->shape.setOrigin(200,50);
	this->shape.setFillColor(sf::Color(49, 27, 17));
	this->shape.setOutlineThickness(1);
	this->shape.setOutlineColor(sf::Color(22, 27, 17));

	this->updateTextPosition();
}


Button::~Button()
{
}

void Button::setPosition(sf::Vector2f vec)
{
	this->shape.move(vec);
	this->updateTextPosition();
}

void Button::move(sf::Vector2f vec)
{
	this->shape.move(vec);
	this->text.move(vec);
}

void Button::draw(sf::RenderWindow &window)
{
	window.draw(this->shape);
	window.draw(this->text);
}

void Button::setActive()
{
	this->text.setFillColor(sf::Color::White);
	this->shape.setFillColor(sf::Color(70, 70, 70));
	this->shape.setOutlineThickness(1);
}

void Button::setText(std::string text)
{
	this->text.setString(text);
}

void Button::setUnActive()
{
	this->text.setFillColor(sf::Color::Red);
	this->shape.setFillColor(sf::Color(40, 40, 40));
	this->shape.setOutlineThickness(1);
}

sf::FloatRect Button::getGlobalBounds()
{
	return this->shape.getGlobalBounds();
}

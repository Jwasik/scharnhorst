#pragma once
#include "pch.h"
#include "shallow.h"

shallow::shallow()
{
	/*std::shared_ptr <std::vector<std::shared_ptr<sf::Vector2f>>> tpoints = std::make_shared<std::vector<std::shared_ptr<sf::Vector2f>>>();

	tpoints->push_back(std::make_shared<sf::Vector2f>(sf::Vector2f(-300, -300)));
	tpoints->push_back(std::make_shared<sf::Vector2f>(sf::Vector2f(300, -300)));
	tpoints->push_back(std::make_shared<sf::Vector2f>(sf::Vector2f(300, 300)));
	tpoints->push_back(std::make_shared<sf::Vector2f>(sf::Vector2f(-300, 300)));
	this->unmovable::unmovable(tpoints);

	this->body = hitbox(&shape);
	this->setFillColor(sf::Color( 200, 0, 200));*/
}

shallow::shallow(std::shared_ptr <std::vector<std::shared_ptr<sf::Vector2f>>> points, bool stopsBullets, std::map<std::string, sf::Texture>* textures) : unmovable(points)
{
	this->body = hitbox(&shape);
	if (stopsBullets == 1)
	{
	}
	else
	{
		//shape.setFillColor(sf::Color(0, 0, 100));
		
		shape.setTexture(&(*textures)["shallow1"]);
		this->type = "shallow";

	}

}


void shallow::setPosition(sf::Vector2f nposition)
{
	this->shape.setPosition(nposition);
	this->body.setPosition(nposition);
}

void shallow::updateHitbox()
{
	this->body = hitbox(&shape);
}

void shallow::updateShape()
{
	this->unmovable::updateShape();
	this->updateHitbox();

}

bool shallow::touch(odcinek *line)
{
	return this -> body.intersects(line);
}





void shallow::drawHitbox(sf::RenderWindow &window)
{
	this->draw(window);
	this->body.updateVisual();
	for (auto odcinek : this->body.odcinki)
	{
		window.draw(odcinek.line);
	}
}

std::string shallow::returnType()
{
	return type;
}


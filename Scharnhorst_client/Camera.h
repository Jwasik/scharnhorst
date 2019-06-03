#pragma once

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>




class Camera
{
private:
	sf::Vector2f ScreenDimensions;
	sf::Vector2f lean;
	sf::Vector2f MiceFromMiddle;
	sf::Vector2f Center;
	float zoom;
	

public:
	sf::View view;
	sf::Vector2f MicePosition;
	float angle;

	Camera();
	Camera(sf::Vector2f);
	void calculateMiceFromMiddle(sf::RenderWindow*);
	void setCenter(sf::Vector2f);
	void changePosition();
	void leanToMice(float);
	void leanTo(sf::Vector2f);
	void calculateMicePosition();
	void setZoom(float);
	void addZoom(float);
	void set(sf::RenderWindow*);
	void setDimensions(sf::Vector2f);
	void calculateAngle();
	void calculateView(sf::RenderWindow &window, float howLean);
	void setView(sf::RenderWindow &window);
	std::shared_ptr<sf::View> getView();
	sf::FloatRect getViewBounds();

};
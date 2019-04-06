#pragma once
#include "pch.h"
#include <SFML/Graphics.hpp>
#include <iostream>




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
	void calculateAngle();
};
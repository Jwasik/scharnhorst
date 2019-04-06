#include "pch.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Camera.h"
#define PI 3.14159265
Camera::Camera() {};
Camera::Camera(sf::Vector2f dimensions)
{
	Center = sf::Vector2f(0, 0);
	MicePosition = sf::Vector2f(0, 0);
	lean = sf::Vector2f(0, 0);
	zoom = 1;
	MiceFromMiddle = sf::Vector2f(0, 0);
	ScreenDimensions = dimensions;
	view.reset(sf::FloatRect(0, 0, dimensions.x, dimensions.y));
	angle = 0;
}

void Camera::calculateMiceFromMiddle(sf::RenderWindow *window)
{
	MiceFromMiddle = sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y) - sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2);
}

void Camera::setCenter(sf::Vector2f position)
{
	Center = position;
}

void Camera::changePosition()
{
	view.setCenter(Center + lean);
}

void Camera::leanToMice(float degree)
{
	lean = sf::Vector2f(MiceFromMiddle.x / degree / zoom, MiceFromMiddle.y / degree / zoom);
}

void Camera::leanTo(sf::Vector2f how)
{
	lean = how;
}

void Camera::calculateMicePosition()
{
	MicePosition = Center + sf::Vector2f(MiceFromMiddle.x / zoom, MiceFromMiddle.y / zoom) + lean;
}

void Camera::setZoom(float z)
{
	zoom = z;
	view.setSize(ScreenDimensions / zoom);
}

void Camera::addZoom(float delta)
{
	zoom = zoom + zoom * delta;
	view.setSize(ScreenDimensions / zoom);
}

void Camera::set(sf::RenderWindow *window)
{
	window->setView(view);
}

void Camera::calculateAngle()
{
	angle = (atan(MiceFromMiddle.y / MiceFromMiddle.x) / PI * 180);//k¹t pomiêdzi pionowym promieniem a promieniem do punktu MiceFromMiddle.x, MiceFromMiddle.y

	if (MiceFromMiddle.x >= 0 && MiceFromMiddle.y < 0)//ustala ¿e k¹t 0 stopni jest skierowany w górê 
	{
		angle = 90 + angle;
	}
	else
		if (MiceFromMiddle.x > 0 && MiceFromMiddle.y >= 0)
		{
			angle = angle + 90;
		}
		else
			if (MiceFromMiddle.x <= 0 && MiceFromMiddle.y > 0)
			{
				angle = 90 + angle + 180;
			}
			else
			{
				angle = angle + 270;
			}
}
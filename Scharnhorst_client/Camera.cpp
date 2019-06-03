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

void Camera::leanToMice(float howMuch)
{
	lean = sf::Vector2f(MiceFromMiddle.x / howMuch / zoom, MiceFromMiddle.y / howMuch / zoom);
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

void Camera::setDimensions(sf::Vector2f dimensions)
{
	this->ScreenDimensions = dimensions;
}

void Camera::calculateAngle()
{

	angle = (atan(MiceFromMiddle.y / MiceFromMiddle.x) / PI * 180);//k�t pomi�dzi pionowym promieniem a promieniem do punktu MiceFromMiddle.x, MiceFromMiddle.y

	if (MiceFromMiddle.x >= 0 && MiceFromMiddle.y < 0)//ustala �e k�t 0 stopni jest skierowany w g�r� 
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

void Camera::calculateView(sf::RenderWindow &window, float howLean)
{
	this->calculateMiceFromMiddle(&window);
	this->calculateAngle();
	this->leanToMice(howLean);
	this->calculateMicePosition();
}

void Camera::setView(sf::RenderWindow &window)
{
	this->changePosition();
	this->set(&window);
}

std::shared_ptr<sf::View> Camera::getView()
{
	std::shared_ptr<sf::View> ptr = std::make_shared<sf::View>(this->view);
	return ptr;
}

sf::FloatRect Camera::getViewBounds()
{
	sf::FloatRect rt;
	rt.left = this->view.getCenter().x - this->view.getSize().x / 2.f;
	rt.top = this->view.getCenter().y - this->view.getSize().y / 2.f;
	rt.width = this->view.getSize().x;
	rt.height = this->view.getSize().y;
	return rt;
}

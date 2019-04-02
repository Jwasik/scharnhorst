#include "pch.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Camera.h"

Camera::Camera(sf::Vector2f dimensions)
{
	Center = sf::Vector2f(0, 0);
	MicePosition = sf::Vector2f(0, 0);
	lean = sf::Vector2f(0, 0);
	zoom = 1;
	MiceFromMiddle = sf::Vector2f(0, 0);
	ScreenDimensions = dimensions;
	view.reset(sf::FloatRect(0, 0, dimensions.x, dimensions.y));
}

void Camera::calculateMiceFromMiddle(sf::RenderWindow *window)
{
	MiceFromMiddle = sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y) - sf::Vector2f(1920 / 2, 1080 / 2);
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
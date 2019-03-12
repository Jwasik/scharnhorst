#include "pch.h"
#include "includes.h"
#include "localGame.h"
#include <windows.h>

const float maxFPS = 80;
float frameTime = 1000 / maxFPS; //czas klatki w ms

int main()
{
	/*
	LocalGame gameClient;
	std::string address;

	while (!gameClient.joinServer());
	gameClient.printAdresses();

	gameClient.gameLoop();
	*/
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
	
	ship s;

	sf::ConvexShape pol;
		pol.setPointCount(4);
	pol.setPoint(0, sf::Vector2f(250, -250));
	pol.setPoint(1, sf::Vector2f(250, 250));
	pol.setPoint(2, sf::Vector2f(-250, 250));
	pol.setPoint(3, sf::Vector2f(-250, -250));
	pol.setPosition(500, 500);
	pol.setRotation(0);
	s.shape = pol;
	while (window.isOpen())
	{
		s.accelerate(0.1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			s.changeGear(1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			s.changeGear(0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			s.spin(0, 0.1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			s.spin(1, 0.1);
		}
		s.swim(&window, 0.1);



		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}






		window.display();
		window.clear();
		std::cout << s.shape.getRotation() << std::endl;
		Sleep(10);
	}
	return 0;
}
#include "pch.h"
#include "includes.h"
#include "localGame.h"
#include "Button.h"
#include <windows.h>


const float maxFPS = 80;
float frameTime = 1000 / maxFPS; //czas klatki w ms


int main()
{
	std::string selectedMenu = "main";
	bool mouseClicked = 0;
	bool keyboardClicked = 0;

	struct gameInformation
	{
		sf::VideoMode resolution = sf::VideoMode(1024, 768); // jak zmieniasz zmień równierz kamera w localGame.cpp

	}gameInfo;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;


	std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(gameInfo.resolution, "Scharnhorst", sf::Style::Default, settings);
	window->setFramerateLimit(65);
	std::shared_ptr<sf::Font> menuFont = std::make_shared<sf::Font>();
	menuFont->loadFromFile("gamedata/fonts/PressStart2P.ttf");

	Button multiPlayerButton("Multiplayer", menuFont);
	Button ipTextField("Type IP and port", menuFont);


	sf::View menuView = window->getView();

	window->setView(menuView);
	multiPlayerButton.setPosition(sf::Vector2f(menuView.getSize().x / 2, menuView.getSize().y / 2));
	ipTextField.setPosition(sf::Vector2f(menuView.getSize().x / 2, menuView.getSize().y / 2));
	

	sf::RectangleShape background(sf::Vector2f(window->getSize()));
	background.setFillColor(sf::Color(147, 92, 0));
	sf::Vector2i mousePosition;

	std::string typedIp = "";
	while (1)
	{
		mousePosition = sf::Mouse::getPosition(*window);

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Resized)
			{
				menuView.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
			}
			if (event.type == sf::Event::Closed)window->close();

			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128)
				{
					char typed = static_cast<char>(event.text.unicode);
					if ((int)typed == 8)
					{
						if(typedIp.length()>0)typedIp.pop_back();
					}
					else typedIp += typed;
					ipTextField.setText(typedIp);
				}
			}
			
		}
		if (selectedMenu == "main")
		{
			if (multiPlayerButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
			{
				multiPlayerButton.setActive();
			}
			else
			{
				multiPlayerButton.setUnActive();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				
				if (mouseClicked == 0)
				{
					mouseClicked = 1;
					if (multiPlayerButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
					{
						selectedMenu = "multi";
					}
				}
			}
			else mouseClicked = 0;
		}
		else if (selectedMenu == "multi")
		{
			
		}

		window->clear();

		window->draw(background);
		if(selectedMenu == "main")multiPlayerButton.draw(*window);
		if(selectedMenu == "multi")ipTextField.draw(*window);

		window->display();
	}
	/*try 
	{
		std::string playerName, shipType;
		std::cout << "type your name" << std::endl;
		std::getline(std::cin,playerName);
		std::cout << "choose your ship" << std::endl;
		std::getline(std::cin, shipType);


		LocalGame gameClient(playerName, shipType);
		std::string address;

		while (!gameClient.joinServer());
		gameClient.printAdresses();

		gameClient.gameLoop();
	}
	catch (std::string error)
	{
		std::cout << "exception occured" << std::endl;
		std::cout << error << std::endl;
	}*/
	return 0;
}
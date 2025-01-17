#include "pch.h"
#include "includes.h"
#include "localGame.h"
#include "Button.h"
#include <windows.h>


const float maxFPS = 80;
float frameTime = 1000 / maxFPS; //czas klatki w ms


int main()
{
	sf::Music music;
	music.openFromFile("gamedata/music/menu.flac");
	music.play();

	std::string selectedMenu = "main";
	bool mouseClicked = 0;
	bool keyboardClicked = 0;

	struct gameInformation
	{
		sf::VideoMode resolution = sf::VideoMode(1024, 768); // jak zmieniasz zmień równierz kamera w localGame.cpp

	}gameInfo;

	sf::ContextSettings settings;
	//settings.antialiasingLevel = 4;


	std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(gameInfo.resolution, "Scharnhorst", sf::Style::Default, settings);
	window->setFramerateLimit(65);
	std::shared_ptr<sf::Font> menuFont = std::make_shared<sf::Font>();
	menuFont->loadFromFile("gamedata/fonts/PressStart2P.ttf");

	Button multiPlayerButton("Multiplayer", menuFont);
	Button ipTextField("Type IP and port", menuFont);
	Button exitButton("Exit", menuFont);
	Button backButton("Back", menuFont);
	Button scharnhorstButton("Scharnhorst", menuFont);
	Button krasnyjKawkazButton("Krasnyj Kawkaz", menuFont);
	Button oregonButton("Oregon", menuFont);
	Button nameTextField("Type your name", menuFont);
	Button backButton2("Back", menuFont);


	sf::View menuView = window->getView();

	window->setView(menuView);
	multiPlayerButton.setPosition(sf::Vector2f(menuView.getSize().x / 2, menuView.getSize().y / 2));
	ipTextField.setPosition(sf::Vector2f(menuView.getSize().x / 2, menuView.getSize().y / 2));
	exitButton.setPosition(sf::Vector2f(menuView.getSize().x / 2, menuView.getSize().y / 2+100));
	backButton.setPosition(sf::Vector2f(menuView.getSize().x / 2, menuView.getSize().y / 2+ 100));
	backButton2.setPosition(sf::Vector2f(menuView.getSize().x / 2, menuView.getSize().y / 2+ 300));

	nameTextField.setPosition(sf::Vector2f(menuView.getSize().x / 2, menuView.getSize().y / 2-150));
	scharnhorstButton.setPosition(sf::Vector2f(menuView.getSize().x / 2-225, menuView.getSize().y / 2+ 100));
	krasnyjKawkazButton.setPosition(sf::Vector2f(menuView.getSize().x / 2+225, menuView.getSize().y / 2+ 100));
	oregonButton.setPosition(sf::Vector2f(menuView.getSize().x / 2, menuView.getSize().y / 2+ 200));
	
	sf::Texture scharnhorstTexture;
	scharnhorstTexture.loadFromFile("gamedata/scharnhorst.jpg");
	sf::RectangleShape background(sf::Vector2f(window->getSize()));
	//background.setFillColor(sf::Color(147, 92, 0));
	background.setTexture(&scharnhorstTexture);
	sf::Vector2i mousePosition;

	std::string typedIp = "";
	std::string name = "";
	std::string ship = "1936A";

	LocalGame gameClient(window);

	while (window->isOpen())
	{
		mousePosition = window->mapCoordsToPixel(sf::Vector2f(sf::Mouse::getPosition(*window)),menuView);

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
					if(selectedMenu == "multi")
					{
						char typed = static_cast<char>(event.text.unicode);
						if ((int)typed == 8)
						{
							if (typedIp.length() > 0)typedIp.pop_back();
						}
						else if ((int)typed == 13)
						{
							nameTextField.setText("Type your name");
							selectedMenu = "name";
							break;
						}
						else typedIp += typed;
						ipTextField.setText(typedIp);
					}		
					if (selectedMenu == "name")
					{
						char typed = static_cast<char>(event.text.unicode);
						if ((int)typed == 8)
						{
							if (name.length() > 0)name.pop_back();
						}
						else if ((int)typed == 13)
						{
							gameClient.setPlayerName(name);
							gameClient.setPlayerShip(ship);
							if (gameClient.joinServer(typedIp))
							{
								music.pause();
								gameClient.gameLoop();
								music.play();
							}
							else selectedMenu = "multi";
						}
						else name += typed;
						nameTextField.setText(name);
					}
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
			if (exitButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
			{
				exitButton.setActive();
			}
			else
			{
				exitButton.setUnActive();
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
					if (exitButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
					{
						return 0;
					}
				}
			}
			else mouseClicked = 0;
		}
		else if (selectedMenu == "multi")
		{
			if (backButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
			{
				backButton.setActive();
			}
			else
			{
				backButton.setUnActive();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

				if (mouseClicked == 0)
				{
					mouseClicked = 1;
					if (backButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
					{
						selectedMenu = "main";
					}
				}
			}
			else mouseClicked = 0;
		}
		else if (selectedMenu == "name")
		{
			if (scharnhorstButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))scharnhorstButton.setActive();
			else scharnhorstButton.setUnActive();
			if (krasnyjKawkazButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))krasnyjKawkazButton.setActive();
			else krasnyjKawkazButton.setUnActive();
			if (oregonButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))oregonButton.setActive();
			else oregonButton.setUnActive();
			if (backButton2.getGlobalBounds().contains(sf::Vector2f(mousePosition)))backButton2.setActive();
			else backButton2.setUnActive();

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (mouseClicked == 0)
				{
					mouseClicked = 1;
					if (backButton2.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
					{
						selectedMenu = "multi";
					}
					if (scharnhorstButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
					{
						ship = "Scharnhorst";
						scharnhorstButton.setMarked();
						krasnyjKawkazButton.setUnMarked();
						oregonButton.setUnMarked();
					}
					else if (krasnyjKawkazButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
					{
						ship = "Krasnyj Kawkaz";
						scharnhorstButton.setUnMarked();
						krasnyjKawkazButton.setMarked();
						oregonButton.setUnMarked();
					}
					else if (oregonButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
					{
						ship = "Oregon";
						scharnhorstButton.setUnMarked();
						krasnyjKawkazButton.setUnMarked();
						oregonButton.setMarked();
					}
				}
			}
			else mouseClicked = 0;
		}

		window->clear();

		window->draw(background);
		if (selectedMenu == "main")
		{
			multiPlayerButton.draw(*window);
			exitButton.draw(*window);
		}
		if (selectedMenu == "multi")
		{
			ipTextField.draw(*window);
			backButton.draw(*window);
		}
		if (selectedMenu == "name")
		{
			nameTextField.draw(*window);
			scharnhorstButton.draw(*window);
			krasnyjKawkazButton.draw(*window);
			oregonButton.draw(*window);
			backButton2.draw(*window);
		}

		window->display();
	}
	return 0;
}
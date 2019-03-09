#pragma once
#include "includes.h"

class LocalGame
{
private:
	struct serverInformation
	{
		unsigned short serverUdpPort=0;
		std::string serverAddress="";
		unsigned short playerCount = 0;
		unsigned short playerId = 0;
	}serverInfo;
	struct gameInformation
	{
		sf::VideoMode resolution = sf::VideoMode(800U,600U);

	}gameInfo;
	std::shared_ptr<sf::RenderWindow> window;

	sf::TcpSocket orderSocket;
	sf::UdpSocket inSocket, outSocket;
public:
	bool connectToServer(const std::string&);

	LocalGame();
	~LocalGame();
	void gameLoop();
	void playerEvent(); // funkcja przechwytuje stworzenie pocisku, zmiany kursu itp

	void sendPlayerPosition(); //wysy³a pozycje gracza
	void sendAction(); //wysy³a informacje o strzale
	void sendMessage(); //wysy³a wiadomoœæ TCP

	void receivePlayerPosition(); //odbiera pozycje graczy od serwera
	void receiveAction(); //odbiera informacje o strzale
	void recieveMessage(); //odbiera wiadomoœci TCP


	bool joinServer();
	void printAdresses();
};


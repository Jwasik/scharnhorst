#pragma once
#include "includes.h"
#include "player.h"
#include <string>

class LocalGame
{
	std::string playerName;
	float stalaCzasowa = 1;
private:
	struct serverInformation
	{
		unsigned short serverUdpPort=0;
		sf::IpAddress serverAddress;
		unsigned short playerCount = 0;
	}serverInfo;
	struct gameInformation
	{
		sf::VideoMode resolution = sf::VideoMode(800U,600U);

	}gameInfo;

	std::shared_ptr<sf::RenderWindow> window;

	std::shared_ptr<Player> player;
	std::vector<std::shared_ptr<Player>> otherPlayers;
	sf::TcpSocket orderSocket;
	sf::UdpSocket inSocket, outSocket;
public:
	bool connectToServer(const std::string&);
	bool isWClicked=0;
	bool isSClicked=0;

	LocalGame();
	~LocalGame();
	void gameLoop();
	void playerEvent(const double&); // funkcja przechwytuje stworzenie pocisku, zmiany kursu itp

	std::shared_ptr<Player> getPlayerById(unsigned int);

	void sendPlayerPosition(); //wysy³a pozycje i dane gracza
	void sendAction(); //wysy³a informacje o strzale
	void sendMessage(); //wysy³a wiadomoœæ TCP

	void receiveNewPlayer(sf::Packet);
	void receivePlayerPosition(sf::Packet); //odbiera pozycje graczy od serwera
	void receiveAction(sf::Packet); //odbiera informacje o strzale
	void recieveMessage(); //odbiera wiadomoœci TCP


	bool joinServer();
	void printAdresses();
};


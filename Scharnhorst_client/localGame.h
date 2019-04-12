#pragma once
#include "includes.h"
#include "player.h"
#include <string>
#include "Camera.h"


class LocalGame
{
	Camera kamera;
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
		sf::VideoMode resolution = sf::VideoMode(800U,600U); // jak zmieniasz zmie� r�wnierz kamera w localGame.cpp

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

	void sendPlayerPosition(); //wysy�a pozycje i dane gracza
	void sendAction(); //wysy�a informacje o strzale
	void sendMessage(); //wysy�a wiadomo�� TCP


	void receiveAction(); //odbiera pakiety TCP
	void recieveMessages(); //obs�uguje odbieranie wiadomo�ci UDP
	//receiveMessage wywo�uje receivePlayersPositions
	void receivePlayersPositions(); //odbiera pozycje graczy od serwera


	bool joinServer();
	void printAdresses();
};


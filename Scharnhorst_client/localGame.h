#pragma once
#include "includes.h"
#include "player.h"
#include "turret.h"
#include <string>
#include <fstream>


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
		sf::VideoMode resolution = sf::VideoMode(800U,600U); // jak zmieniasz zmieñ równierz kamera w localGame.cpp

	}gameInfo;

	bool inView(sf::Vector2f);

	std::shared_ptr<sf::RenderWindow> window;

	std::shared_ptr<Player> player;
	std::vector<std::shared_ptr<Player>> otherPlayers;
	std::vector<std::vector<sf::RectangleShape>> backgroundMap;

	std::vector<std::pair<std::string,Bullet>> bulletData;
	std::vector<std::pair<std::string,Barrel>> barrelData;
	std::vector<std::pair<std::string,Turret>> turretData;

	std::map<std::string,sf::Texture> textures;
	sf::TcpSocket orderSocket;
	sf::UdpSocket inSocket, outSocket;

	bool loadBullets();
	bool loadBarrels();
	bool loadTurrets();
	bool loadShips();

	Bullet findBullet(std::string);
	Barrel findBarrel(std::string);
	Turret findTurret(std::string);

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
	void loadMap();
	bool loadGameFiles();

	void receiveAction(); //odbiera pakiety TCP
	void recieveMessages(); //obs³uguje odbieranie wiadomoœci UDP
	//receiveMessage wywo³uje receivePlayersPositions
	void receivePlayersPositions(); //odbiera pozycje graczy od serwera


	bool joinServer();
	void printAdresses();

};
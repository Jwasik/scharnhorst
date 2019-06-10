#pragma once
#include "includes.h"
#include "player.h"
#include "turret.h"
#include "bullet.h"
#include "ship.h"
#include <string>
#include <fstream>
#include <SFML/Audio.hpp>
#include "map.h"


class LocalGame
{
private:
	bool endFlag = false;

	Camera kamera;
	std::string playerName;
	float stalaCzasowa = 1;


	struct serverInformation
	{
		unsigned short serverUdpPort=0;
		sf::IpAddress serverAddress;
		unsigned short playerCount = 0;
	}serverInfo;
	struct gameInformation
	{
		sf::VideoMode resolution = sf::VideoMode(1024,768); // jak zmieniasz zmieñ równierz kamera w localGame.cpp

	}gameInfo;

	bool inView(sf::Vector2f);

	std::shared_ptr<sf::RenderWindow> window;

	std::shared_ptr<Player> player;
	std::vector<std::shared_ptr<Player>> otherPlayers;
	std::vector<std::shared_ptr<Ship>> wreckages;
	std::vector<Bullet> bullets;//œwiadomie zrobi³em bez wskaŸnika, zapytaj siê potem dlaczego
	std::vector<std::vector<sf::RectangleShape>> backgroundMap;
	std::vector<std::shared_ptr<map>> maps;
	std::shared_ptr<map> actualMap;


	std::map<std::string, std::shared_ptr<sf::SoundBuffer>> soundBuffers;
	std::vector<std::shared_ptr<sf::Sound>> sounds;

	std::vector<std::pair<std::string,Bullet>> bulletData;
	std::vector<std::pair<std::string,Barrel>> barrelData;
	std::vector<std::pair<std::string,Turret>> turretData;
	std::vector<std::pair<std::string,Ship>> shipData;

	std::map<std::string,sf::Texture> textures;
	sf::TcpSocket TCPsocket;
	sf::UdpSocket inSocket, outSocket;

	bool loadBullets();
	bool loadBarrels();
	bool loadTurrets();
	bool loadSounds();
	bool loadShips();

	Bullet findBullet(std::string);
	Barrel findBarrel(std::string);
	Turret findTurret(std::string);
	Ship findShip(std::string);
	std::shared_ptr<sf::SoundBuffer> findSoundBuffer(int);

	sf::Clock connectionClock;//Przechowuje czas od ostatniej interakcji z serwerem

	std::string shipType;

	void eraseBullet(unsigned int);
	void calculatePlayerList(std::vector<sf::Text>&);
	void generateWreckage(std::shared_ptr<Player>);

public:
	bool connectToServer(const std::string&);
	bool isWClicked=0; 
	bool isSClicked=0;

	LocalGame();
	LocalGame(std::string,std::string);
	~LocalGame();
	void gameLoop();
	void playerEvent(const double&); // funkcja przechwytuje stworzenie pocisku, zmiany kursu itp

	std::shared_ptr<Player> getPlayerById(unsigned int);

	void sendPlayerPosition(); //wysy³a pozycje i dane gracza
	void loadMap();
	bool loadGameFiles();
	void displayIslands();
	//void swimButBewereOfIslands(std::shared_ptr<Player> player, std::shared_ptr<map> map );

	void receiveTCP(); //odbiera pakiety TCP
	void recieveUDP(); //obs³uguje odbieranie wiadomoœci UDP
	void sendTCP(sf::Packet);
	//receiveMessage wywo³uje receivePlayersPositions
	void receivePlayersPositions(); //odbiera pozycje graczy od serwera


	bool joinServer();
	void printAdresses();

};
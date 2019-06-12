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
#include <stdlib.h>
#include <time.h> 


class LocalGame
{
private:
	void colision(float deltatime);

	int spinD;
	bool isColliding;
	bool developerMode;
	bool endFlag = false;

	Camera kamera;
	std::string playerName;
	float stalaCzasowa = 1;

	bool resetButton;

	struct serverInformation
	{
		unsigned short serverUdpPort=0;
		sf::IpAddress serverAddress;
		unsigned short playerCount = 0;
	}serverInfo;
	

	bool inView(sf::Vector2f);

	std::shared_ptr<sf::RenderWindow> window;

	std::shared_ptr<Player> player;
	std::vector<std::shared_ptr<Player>> otherPlayers;
	std::vector<std::shared_ptr<Ship>> wreckages;
	std::vector<Bullet> bullets;//œwiadomie zrobi³em bez wskaŸnika, zapytaj siê potem dlaczego
	std::vector<std::vector<sf::RectangleShape>> backgroundMap;
	std::vector<std::shared_ptr<map>> maps;
	std::shared_ptr<map> actualMap;
	odcinek delitingLine;


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
	bool loadMaps();

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
	LocalGame(std::shared_ptr<sf::RenderWindow>);
	~LocalGame();
	void gameLoop();
	void playerEvent(const double&); // funkcja przechwytuje stworzenie pocisku, zmiany kursu itp

	std::shared_ptr<Player> getPlayerById(unsigned int);

	void sendPlayerPosition(); //wysy³a pozycje i dane gracza
	void loadMap();
	bool loadGameFiles();
	//void swimButBewereOfIslands(std::shared_ptr<Player> player, std::shared_ptr<map> map );

	void receiveTCP(); //odbiera pakiety TCP
	void recieveUDP(); //obs³uguje odbieranie wiadomoœci UDP
	void sendTCP(sf::Packet);
	void receivePlayersPositions(); //odbiera pozycje graczy od serwera
	void setPlayerName(std::string);
	void setPlayerShip(std::string);


	bool joinServer(std::string);
	void printAdresses();

	void saveMap();
	bool loadWorkMap();
	void spawnPoints();

};
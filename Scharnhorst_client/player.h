#pragma once
#include "includes.h"
#include "functions.h"
#include "ship.h"
#include "bullet.h"
#include <fstream>
class Player
{
private:
	double HP;
	double maxHP;
	std::string playerName;
	unsigned int playerId;
	float angleOfView;

	std::shared_ptr<std::vector<jw::bulletInfo>> newBullets;
	std::shared_ptr<Ship> playerShip;
	sf::Text playerNameText;
	sf::Text playerShipNameText;
	sf::Font playerNameFont;

	unsigned int actualBulletId;

public:
	unsigned int getPlayerId();
	void setShipName(std::string);
	void setId(unsigned int);
	void doStuff(double&);
	void sendPlayerPosition(sf::UdpSocket&, sf::IpAddress, unsigned short);
	void sendBullets(sf::TcpSocket&);
	void draw(sf::RenderWindow&);
	void shoot();
	void setShip(Ship);
	void setAngleOfView(float);

	std::shared_ptr<Ship>& getShip();
	Player();
	//Player(unsigned int, std::string);
	Player(unsigned int, std::string, std::string = "Scharnhorst");
	~Player();
};


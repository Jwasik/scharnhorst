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
	unsigned int killCount;
	std::string playerName;
	unsigned int playerId;
	float angleOfView;

	std::shared_ptr<std::vector<jw::bulletInfo>> newBullets;
	std::shared_ptr<Ship> playerShip;
	sf::Text playerNameText;
	sf::Text playerShipNameText;
	sf::Text playerHPtext;
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
	void updateGui(std::vector<sf::Text>&, sf::View&);
	void calculateHPindicator();

	void subtractHP(float);
	void setHP(float);
	double getPlayerHP();

	std::shared_ptr<Ship>& getShip();
	Player();
	//Player(unsigned int, std::string);
	Player(unsigned int, std::string, std::string = "Scharnhorst");
	~Player();
};


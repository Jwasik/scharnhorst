#pragma once
#include "includes.h"
#include "ship.h"
#include "bullet.h"
class Player
{
private:
	float sightAngle = 0;
	std::string playerName;
	unsigned int playerId;
	float angleOfView;

	std::shared_ptr<std::vector<Bullet>> newBullets;
	std::shared_ptr<Ship> playerShip;
	sf::Text playerNameText;
	sf::Text playerShipNameText;
	sf::Font playerNameFont;
public:
	unsigned int getPlayerId();
	void setShipName(std::string);
	void setId(unsigned int);
	void doStuff(double&);
	void sendPlayerPosition(sf::UdpSocket&, sf::IpAddress, unsigned short);
	void draw(sf::RenderWindow&);
	void rotateTurretsTo(float angleOfView);
	void shoot();

	std::shared_ptr<Ship>& getShip();
	Player();
	//Player(unsigned int, std::string);
	Player(unsigned int, std::string, std::string = "Scharnhorst");
	~Player();
};


#pragma once
#include "includes.h"
#include "ship.h"
class Player
{
private:
	float sightAngle = 0;
	std::string playerName;
	unsigned int playerId;
	float angleOfView;


public:
	std::shared_ptr<Ship> playerShip;
	sf::Text playerNameText;
	sf::Text playerShipNameText;
	sf::Font playerNameFont;

	unsigned int getPlayerId();
	void setId(unsigned int);
	void doStuff(double&);
	void sendPlayerPosition(sf::UdpSocket&, sf::IpAddress, unsigned short);
	void draw(sf::RenderWindow&);
	void rotateTurretsTo(float angleOfView);

	std::shared_ptr<Ship>& getShip();
	Player();
	//Player(unsigned int, std::string);
	Player(unsigned int, std::string, std::string = "Scharnhorst");
	~Player();
};


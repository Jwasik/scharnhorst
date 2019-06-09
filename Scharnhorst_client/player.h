#pragma once
#include "includes.h"
#include "functions.h"
#include "ship.h"
#include "bullet.h"
#include <fstream>
#include "map.h"
class Player
{
private:
	double HP;
	double maxHP;
	unsigned int killCount;
	std::string playerName;
	unsigned int playerId;
	float angleOfView;
	sf::Vector2f previousPosition;
	float previousRotation;

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
	void mainPlayerDoStuff(double &deltaTime, std::shared_ptr<map> map);
	void sendPlayerPosition(sf::UdpSocket&, sf::IpAddress, unsigned short);
	void sendBullets(sf::TcpSocket&);
	void draw(sf::RenderWindow&);
	void shoot();
	void setShip(Ship);
	void setAngleOfView(float);
	void updateGui(std::vector<sf::Text>&, sf::View&);
	void calculateHPindicator();
	void respawn(sf::Vector2f);

	void subtractHP(float);
	void setHP(float);
	double getPlayerHP();
	double getMaxPlayerHP();

	unsigned int getScore();
	void setScore(unsigned int);
	void increaseScore();

	std::shared_ptr<Ship>& getShip();
	std::string getPlayerName();

	Player();
	//Player(unsigned int, std::string);
	Player(unsigned int, std::string, std::string = "Scharnhorst");
	~Player();
};


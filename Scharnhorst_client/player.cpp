#include "pch.h"
#include "player.h"

unsigned int Player::getPlayerId()
{
	return this->playerId;
}

void Player::setShipName(std::string name)
{
	this->playerShipNameText.setString(name);
	this->getShip()->setName(name);
}

void Player::setId(unsigned int newId)
{
	this->playerId = newId;
}



void Player::doStuff(double &deltaTime)
{
	if (this->playerShip != nullptr)
	{
		playerShip->swim(deltaTime);
		this->playerNameText.setPosition(this->getShip()->getPosition()+sf::Vector2f(-100,-200));
		this->playerShipNameText.setPosition(this->getShip()->getPosition()+sf::Vector2f(-100,-170));
		this->getShip()->setTurrets(this->angleOfView, deltaTime);
	}
}

void Player::sendPlayerPosition(sf::UdpSocket &socket, sf::IpAddress address, unsigned short port)
{
	sf::Packet sendingPacket;
	sendingPacket.clear();

	std::string order = "POS";
	sendingPacket << order;
	sendingPacket << this->playerId;
	sendingPacket << this->getShip()->getPosition().x;
	sendingPacket << this->getShip()->getPosition().y;
	sendingPacket << this->getShip()->getRotation();
	sendingPacket << this->angleOfView;

	socket.send(sendingPacket,address,port);
}

void Player::draw(sf::RenderWindow &window)
{
	this->playerShip->draw(window);
	window.draw(playerNameText);
	window.draw(playerShipNameText);
}


std::shared_ptr<Ship> & Player::getShip()
{
	return this->playerShip;
}

Player::Player()
{
	playerShip = std::make_shared<Ship>();
	angleOfView = 0;
}

Player::Player(unsigned int id, std::string playerName, std::string shipType)
{
	this->playerShip = std::make_shared<Ship>();
	this->playerId = id;
	this->playerName = playerName;

	this->playerNameText.setString(playerName);
	this->playerShipNameText.setString(shipType);

	this->playerNameFont.loadFromFile("PressStart2P.ttf");
	this->playerNameText.setFont(this->playerNameFont);
	this->playerShipNameText.setFont(this->playerNameFont);

	this->playerNameText.setFillColor(sf::Color::Blue);

	this->playerShipNameText.setFillColor(sf::Color::Red);
	playerShipNameText.setCharacterSize(20);
	angleOfView = 0;
}

void Player::rotateTurretsTo(float angleOfView)
{
	this->angleOfView = angleOfView;
}

void Player::shoot()
{
	this->playerShip->shoot(this->newBullets);
}



Player::~Player()
{
}

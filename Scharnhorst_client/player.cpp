#include "pch.h"
#include "player.h"


unsigned int Player::getPlayerId()
{
	return this->playerId;
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
	sendingPacket << this->getShip()->getCannonRotation();

	socket.send(sendingPacket,address,port);
}

void Player::draw(sf::RenderWindow &window)
{
	this->playerShip->draw(window);
}


std::shared_ptr<Ship> & Player::getShip()
{
	return this->playerShip;
}

Player::Player()
{
	playerShip = std::make_shared<Ship>();
}

Player::Player(unsigned int id, std::string playerName)
{
	this->playerShip = std::make_shared<Ship>();
	this->playerId = id;
	this->playerName = playerName;
}

Player::Player(unsigned int id, std::string playerName, std::string shipType)
{
	this->playerShip = std::make_shared<Ship>();
	this->playerId = id;
	this->playerName = playerName;
}




Player::~Player()
{
}

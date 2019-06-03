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
		this->playerNameText.setPosition(this->getShip()->getPosition()+sf::Vector2f(-100,-200));//Nazwa gracza
		this->playerShipNameText.setPosition(this->getShip()->getPosition()+sf::Vector2f(-100,-170));//Nazwa statku
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

void Player::sendBullets(sf::TcpSocket &socket)
{
	for (auto & bullet : *newBullets)
	{
		bullet.ownerId = this->playerId;
		bullet.bulletId = this->actualBulletId;
		actualBulletId++;

		sf::Packet bulletPacket;
		bulletPacket.clear();

		std::string order = "BUL";
		bulletPacket << order;
		bulletPacket << bullet;
		socket.send(bulletPacket);
	}
	newBullets->clear();
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
	this->newBullets = std::make_shared<std::vector<jw::bulletInfo>>();
	angleOfView = 0;

	this->playerNameFont.loadFromFile("PressStart2P.ttf");
	this->playerNameText.setFont(this->playerNameFont);
	this->playerShipNameText.setFont(this->playerNameFont);

	this->playerNameText.setFillColor(sf::Color::Blue);

	this->playerShipNameText.setFillColor(sf::Color::Red);
	playerShipNameText.setCharacterSize(20);

	this->actualBulletId = 1;
}

Player::Player(unsigned int id, std::string playerName, std::string shipType) : Player()
{
	this->playerId = id;
	this->playerName = playerName;

	this->playerNameText.setString(playerName);
	this->playerShipNameText.setString(shipType);
}

void Player::shoot()
{
	this->playerShip->shoot(this->newBullets);
}

void Player::setShip(Ship newShip)
{
	this->setShipName(newShip.getType());
	*(this->playerShip) = newShip;
	this->maxHP = newShip.width * newShip.length * 16;
	this->HP = maxHP;
}

void Player::setAngleOfView(float angle)
{
	this->angleOfView = angle;
}

void Player::updateGui(std::vector<sf::Text>& content, sf::View &view)
{
	content[0] .setString("HP: "+ std::to_string(int(this->HP)) + " / " + std::to_string(int(this->maxHP)));
	content[1].setString("SPEED: " + std::to_string(int(this->getShip()->actualSpeed)));
	content[2].setString("GEAR: " + std::to_string(int(this->getShip()->gear)));
	for (unsigned int i = 3; i < 12; i++)
	{
		if (i-3 == this->getShip()->turrets.size())return;
		this->getShip()->turrets[i-3]->updateHudTurret(content,i);
	}
}



Player::~Player()
{
}

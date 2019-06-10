#include "pch.h"
#include "player.h"

unsigned int Player::getPlayerId()
{
	return this->playerId;
}

void Player::setShipName(std::string name)
{
	//this->playerShipNameText.setString(name);
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
		this->playerShip->swim(deltaTime);
		this->playerNameText.setPosition(this->getShip()->getPosition()+sf::Vector2f(-100,-200));//Nazwa gracza
		this->playerShipNameText.setPosition(this->getShip()->getPosition()+sf::Vector2f(-100,-170));//Nazwa statku
		this->playerHPtext.setPosition(this->getShip()->getPosition()+sf::Vector2f(-100,-140));//HP
		this->getShip()->setTurrets(this->angleOfView, deltaTime);
	}
}

void Player::mainPlayerDoStuff(double &deltaTime, std::shared_ptr<map> map)
{
	bool is = 0;

	for (auto isle : map->islands)
	{
		if ((isle->touch(&(this->playerShip->hitbox[0]))) || (isle->touch(&(this->playerShip->hitbox[1]))))
		{
			is = 1;
			break;
		}
	}

	if (this->playerShip != nullptr)
	{
		this->playerShip->swim(deltaTime);
		this->playerNameText.setPosition(this->getShip()->getPosition() + sf::Vector2f(-100, -200));//Nazwa gracza
		this->playerShipNameText.setPosition(this->getShip()->getPosition() + sf::Vector2f(-100, -170));//Nazwa statku
		this->playerHPtext.setPosition(this->getShip()->getPosition() + sf::Vector2f(-100, -140));//HP
		this->getShip()->setTurrets(this->angleOfView, deltaTime);

		if (is)
		{
			if (this->playerShip->actualSpeed < 0)
			{
				this->playerShip->actualSpeed = this->playerShip->actualSpeed / 10;

			}
			else
			{
			this->playerShip->actualSpeed = this->playerShip->actualSpeed/10;
			this->playerShip->setPosition(previousPosition);
			//this->playerShip->hitbox[0].rotate(-(this->playerShip->getRotation() - previousRotation));
			//this->playerShip->hitbox[1].rotate(-(this->playerShip->getRotation() - previousRotation));
			//his->playerShip->setRotation(previousRotation);
			this->playerShip->hitbox[0].setPosition(previousPosition);
			this->playerShip->hitbox[1].setPosition(previousPosition);
			}
			








		}
		else
		{
			previousPosition = this->playerShip->getPosition();
			previousRotation = this->playerShip->getRotation();

		}
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
	window.draw(playerHPtext);
}


std::shared_ptr<Ship> & Player::getShip()
{
	return this->playerShip;
}

std::string Player::getPlayerName()
{
	return this->playerName;
}

Player::Player()
{
	this->killCount = 0;
	playerShip = std::make_shared<Ship>();
	this->newBullets = std::make_shared<std::vector<jw::bulletInfo>>();
	angleOfView = 0;

	this->playerNameFont.loadFromFile("PressStart2P.ttf");
	this->playerNameText.setFont(this->playerNameFont);
	this->playerShipNameText.setFont(this->playerNameFont);
	this->playerHPtext.setFont(this->playerNameFont);
	this->playerHPtext.setCharacterSize(10);

	this->playerNameText.setFillColor(sf::Color::Blue);
	this->playerHPtext.setFillColor(sf::Color::White);
	this->playerShipNameText.setFillColor(sf::Color::Red);

	this->playerShipNameText.setCharacterSize(20);
	
	this->killCount = 0;
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
	*(this->playerShip) = newShip;
	this->maxHP = newShip.width * newShip.length * 16;
	this->HP = maxHP;
	this->playerShipNameText.setString(this->getShip()->getType());
}

void Player::setAngleOfView(float angle)
{
	this->angleOfView = angle;
}

void Player::updateGui(std::vector<sf::Text>& content, sf::View &view)
{
	content[0].setString("HP: "+ std::to_string(int(this->HP)) + " / " + std::to_string(int(this->maxHP)));
	content[1].setString("SPEED: " + std::to_string(int(this->getShip()->actualSpeed)));
	content[2].setString("GEAR: " + std::to_string(int(this->getShip()->gear)));
	for (unsigned int i = 3; i < 12; i++)
	{
		if (i-3 == this->getShip()->turrets.size())return;
		this->getShip()->turrets[i-3]->updateHudTurret(content,i);
	}
}

void Player::calculateHPindicator()
{
	this->playerHPtext.setString(std::to_string(int(this->HP)) + " / " + std::to_string(int(this->maxHP)));
	if (this->HP <= (this->maxHP*0.2))this->playerHPtext.setFillColor(sf::Color::Red);
	else this->playerHPtext.setFillColor(sf::Color::White);
}

void Player::respawn(sf::Vector2f mapSize)
{
	this->HP = this->maxHP;
	unsigned int x, y;//Wylosowane wspó³rzêdne
	x = std::rand();
	y = std::rand();
	x %= unsigned int(mapSize.x);
	x *= 128;
	y %= unsigned int(mapSize.y);
	y *= 128;
	this->playerShip->setPosition(sf::Vector2f(x,y));
}

Player::~Player()
{
}

void Player::subtractHP(float damage)
{
	this->HP -= damage;
}

void Player::setHP(float HP)
{
	this->HP = HP;
}

double Player::getPlayerHP()
{
	return this->HP;
}

double Player::getMaxPlayerHP()
{
	return this->maxHP;
}

unsigned int Player::getScore()
{
	return this->killCount;
}

void Player::setScore(unsigned int score)
{
	this->killCount = score;
}

void Player::increaseScore()
{
	this->killCount++;
}

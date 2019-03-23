#include "pch.h"
#include "localGame.h"
#include <windows.h>



LocalGame::LocalGame()
{
	this->playerName = "Karl";
	window = std::make_shared<sf::RenderWindow>(gameInfo.resolution,"Scharnhorst");

	inSocket.bind(sf::Socket::AnyPort);
	inSocket.setBlocking(false);
}

void LocalGame::gameLoop()
{
	sf::Clock time;
	time.restart();

	double deltaTime;
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		deltaTime = time.restart().asSeconds()*stalaCzasowa;

		this->player->doStuff(deltaTime);
		for (auto & player : otherPlayers)
		{
			player->doStuff(deltaTime);
		}
		this->playerEvent(deltaTime);

		this->sendPlayerPosition(); //wysy³a pozycje i dane gracza
		this->sendAction(); //wysy³a informacje o strzale
		this->recieveMessage(); //odbiera wiadomoœci TCP
		this->sendMessage(); //wysy³a wiadomoœæ TCP

		window->clear();
		player->draw(*window);
		for (auto & player : otherPlayers)
		{
			player->draw(*window);
		}
		window->display();
		system("cls");
	}
}

void LocalGame::playerEvent(const double &deltaTime)
{
	if (player == nullptr)return;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		if (this->isWClicked == 0)
		{
			player->getShip()->changeGear(1);
			this->isWClicked = 1;
		}
	}
	else
	{
		this->isWClicked = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		if (this->isSClicked == 0)
		{
			player->getShip()->changeGear(0);
			isSClicked = 1;
		}
	}
	else
	{
		isSClicked = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		player->getShip()->spin(0, deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		player->getShip()->spin(1, deltaTime);
	}
}

std::shared_ptr<Player> LocalGame::getPlayerById(unsigned int searchedId)
{
	auto x = 
	std::find_if(otherPlayers.begin(), otherPlayers.end(), [&searchedId](std::shared_ptr<Player> &player) {return player->getPlayerId()==searchedId; });
	if (x != otherPlayers.end())
	{
		return *x;
	}
	else return nullptr;
}

bool LocalGame::joinServer()
{
	std::string IP;
	std::cout << "type server IP and port" << std::endl;
	std::cin >> IP;
	orderSocket.setBlocking(false);

	if (connectToServer(IP) == false)return 0;
	
	sf::Packet newPlayerPacket;
	newPlayerPacket << "PLA" << unsigned int(0) << this->playerName << 1;
	
	orderSocket.send(newPlayerPacket);
	newPlayerPacket.clear();

	sf::Clock connectionClock;
	connectionClock.restart();
	std::string receivedMessage;
	while (connectionClock.getElapsedTime().asSeconds() < 10)
	{
		orderSocket.receive(newPlayerPacket);
		if (newPlayerPacket >> receivedMessage)
		{
			if (receivedMessage == "PLJ")
			{
				std::string newPlayerName = "error";
				unsigned int id = 0;
				float x, y, angle=0;
				newPlayerPacket >> id;
				newPlayerPacket >> newPlayerName;
				std::cout << "received PLJ : " << id << ' ' << newPlayerName << std::endl;
				player = std::make_shared<Player>(id,newPlayerName);
				newPlayerPacket >> x;
				newPlayerPacket >> y;
				newPlayerPacket >> angle;

				player->getShip()->setPosition(sf::Vector2f(x,y));
				player->getShip()->setRotation(angle);
				std::cout << "joined game succesfully" << std::endl;
				while (1);
				return 1;
			}
			else
			{
				receivedMessage.clear();
			}
		}
	}
	std::cout << "could not create new player on server" << std::endl;
	return 0;
}

void LocalGame::printAdresses()
{
	std::cout << "TCP client working on: " << sf::IpAddress::getLocalAddress() << ':' << orderSocket.getLocalPort() << std::endl;
	std::cout << "UDP client working on: " << sf::IpAddress::getLocalAddress() << ':' << inSocket.getLocalPort() << std::endl;
	std::cout << "UDP server working on: " << serverInfo.serverAddress << ':' << serverInfo.serverUdpPort << std::endl;
}

bool LocalGame::connectToServer(const std::string &adress)
{


	auto dots = std::count_if(adress.begin(), adress.end(), [](char a) {return a == '.'; });
	if (dots != 3)
	{
		std::cout << "wrong IP format" << std::endl;
		return 0;
	}
	auto pos = adress.find(':');
	if (pos == std::string::npos)
	{
		std::cout << "need port number" << std::endl;
		return 0;
	}


	std::string IP = adress.substr(0, pos);
	std::stringstream port(adress.substr(pos + 1));


	unsigned short portNum;
	port >> portNum;

	std::cout << IP << ' ';
	std::cout << portNum << std::endl;

	if (portNum < 1025 || portNum >65535)
	{
		std::cout << "port number must be between 1024 and 65535" << std::endl;
		return 0;
	}

	sf::Clock connectionClock;
	connectionClock.restart();



	sf::Socket::Status status;
	do
	{
		status =orderSocket.connect(sf::IpAddress(IP), portNum);
		if (connectionClock.getElapsedTime().asMilliseconds() > 3000)
		{
			std::cout << "max time elapsed" << std::endl;
			return 0;
		}
	} while (status == sf::TcpSocket::Status::Error);

	
	//-----------------------------------------------------------

	sf::Packet helloPacket;
	helloPacket.clear();
	helloPacket << "HI_" << inSocket.getLocalPort();
	std::cout << "sending \"HI\" to server" << std::endl;
	orderSocket.send(helloPacket);
	helloPacket.clear();

	connectionClock.restart();

	while (1)
	{
		if (connectionClock.getElapsedTime().asSeconds() > 2)return false;
		if (orderSocket.receive(helloPacket) == sf::Socket::Done)
		{
			std::string message;
			helloPacket >> message;
			if (message == "HI_")
			{
				this->serverInfo.serverAddress = orderSocket.getRemoteAddress();
				helloPacket >> serverInfo.serverUdpPort;
				std::cout << "server responded with \"HI\" and port " << serverInfo.serverUdpPort << std::endl;
				this->serverInfo.serverAddress = IP;
				return true;
			}
		}

	}
	return false;

}


LocalGame::~LocalGame()
{
}

void LocalGame::sendPlayerPosition()
{
	this->player->sendPlayerPosition(outSocket, this->serverInfo.serverAddress, this->serverInfo.serverUdpPort);
}

void LocalGame::sendAction()
{
}

void LocalGame::sendMessage()
{
}

void LocalGame::receiveNewPlayer(sf::Packet)
{
}

void LocalGame::receivePlayerPosition(sf::Packet receivedPacket)
{
	unsigned int playerId;
	float x, y, shipAngle, cannonAngle;
	receivedPacket >> playerId;
	receivedPacket >> x;
	receivedPacket >> y;
	receivedPacket >> shipAngle;
	receivedPacket >> cannonAngle;
	
	auto player = this->getPlayerById(playerId);
	if (player == nullptr)
	{
		receivedPacket.clear();
		return;
	}
	else
	{
		player->getShip()->setPosition(sf::Vector2f(x,y));
		player->getShip()->setRotation(shipAngle);
		player->getShip()->setCannonRotation(cannonAngle);
		receivedPacket.clear();
	}

}

void LocalGame::receiveAction(sf::Packet receivedPacket)
{

}

void LocalGame::recieveMessage()
{
	sf::Packet receivedPacket;
	receivedPacket.clear();
	std::string receivedMessage;

	sf::Clock connectionClock;
	connectionClock.restart();
	while (connectionClock.getElapsedTime().asMilliseconds() < 30)
	{
		inSocket.receive(receivedPacket, this->serverInfo.serverAddress, this->serverInfo.serverUdpPort);
		if (receivedPacket >> receivedMessage)
		{
			if (receivedMessage == "POS")
			{
				receivePlayerPosition(receivedPacket);
				continue;
			}
			if (receivedMessage == "PPS")
			{
				unsigned int count = 0;
				receivedPacket >> count;
				for (unsigned int i = 0; i < count; i++)
				{
					receivePlayerPosition(receivedPacket);
				}
				continue;
			}
		}
		else break;
	}
}

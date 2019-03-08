#include "pch.h"
#include "localGame.h"




LocalGame::LocalGame()
{
	inSocket.bind(sf::Socket::AnyPort);
}

bool LocalGame::joinServer()
{
	std::string IP;
	std::cout << "insert server IP and port" << std::endl;
	std::cin >> IP;
	orderSocket.setBlocking(false);

	return connectToServer(IP);

}

void LocalGame::printAdresses()
{
	std::cout << "TCP client working on: " << sf::IpAddress::getLocalAddress() << ':' << orderSocket.getLocalPort() << std::endl;
	std::cout << "UDP client working on: " << sf::IpAddress::getLocalAddress() << ':' << inSocket.getLocalPort() << std::endl;
	std::cout << "UDP server working on: " << serverAddress << ':' << serverUdpPort << std::endl;
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
				helloPacket >> serverUdpPort;
				std::cout << "server responded with \"HI\" and port " << serverUdpPort << std::endl;
				this->serverAddress = IP;
				return true;
			}
		}

	}
	return false;

}


LocalGame::~LocalGame()
{
}

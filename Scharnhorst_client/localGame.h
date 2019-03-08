#pragma once
#include "includes.h"

class LocalGame
{
private:
	unsigned short serverUdpPort;
	std::string serverAddress;

	sf::TcpSocket orderSocket;
	sf::UdpSocket inSocket, outSocket;
public:
	bool connectToServer(const std::string&);

	LocalGame();
	~LocalGame();

	bool joinServer();

	void printAdresses();
};


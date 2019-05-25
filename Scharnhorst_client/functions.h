#pragma once
#include "includes.h"

namespace jw
{
	//TCPConnect(sf::socket,std::string adres) ³¹czy socket z podanym adresem.


	//Wypisuje na ekran podany sf::status
	void printStatus(const sf::Socket::Status&);
	struct bulletInfo
	{
		std::string name;
		sf::Vector2f position;
		float angle;
		std::string ownerName;
	};
}

template <typename T>
void operator+ (std::vector<T> &a,std::vector<T> b)
{
	for (int i = 0; i < b.size(); i++)
	{
		a.push_back(b[i]);
	}
}

sf::Packet operator<<(sf::Packet& packet, jw::bulletInfo &info)
{
	packet << info.name;
	packet << info.position.x;
	packet << info.position.y;
	packet << info.angle;
	packet << info.ownerName;
	return packet;
}

std::ostream& operator<<(std::ostream &stream,sf::Vector2f vec)
{
	stream << vec.x << ' ' << vec.x << std::endl;
	return stream;
}

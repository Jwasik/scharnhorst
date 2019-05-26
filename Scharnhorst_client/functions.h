#pragma once
#include "includes.h"

namespace jw
{
	//TCPConnect(sf::socket,std::string adres) ��czy socket z podanym adresem.


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

sf::Packet operator<<(sf::Packet&, const jw::bulletInfo&);
sf::Packet& operator>>(sf::Packet&, jw::bulletInfo&);

std::ostream& operator<<(std::ostream&, sf::Vector2f);


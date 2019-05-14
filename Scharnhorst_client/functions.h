#pragma once
#include "includes.h"

namespace jw
{
	//TCPConnect(sf::socket,std::string adres) ³¹czy socket z podanym adresem.


	//Wypisuje na ekran podany sf::status
	void printStatus(const sf::Socket::Status&);
}

template <typename T>
void operator+ (vector<T> &a, vector<T> b)
{
	for (int i = 0; i < b.size(); i++)
	{
		a.push_back(b[i]);
	}
}

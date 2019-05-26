#include "pch.h"
#include "functions.h"





void jw::printStatus(const sf::Socket::Status &status)
{
	switch (status)
	{
	case sf::Socket::Status::Error:
			std::cout << "connection error" << std::endl;
			break;
	case sf::Socket::Status::Done:
		std::cout << "connection done" << std::endl;
		break;
	case sf::Socket::Status::NotReady:
		std::cout << "connection not ready" << std::endl;
		break;
	case sf::Socket::Status::Disconnected:
		std::cout << "connection disconnected" << std::endl;
		break;
	case sf::Socket::Status::Partial:
		std::cout << "connection partial done" << std::endl;
		break;
		default:
			std::cout << "unknown connection status" << std::endl;

	}
}



sf::Packet operator<<(sf::Packet & packet, const jw::bulletInfo & info)
{
	packet << info.name;
	packet << info.position.x;
	packet << info.position.y;
	packet << info.angle;
	packet << info.ownerName;
	return packet;
}

sf::Packet& operator>>(sf::Packet &packet, jw::bulletInfo &info)
{
	packet >> info.name;
	packet >> info.position.x;
	packet >> info.position.y;
	packet >> info.angle;
	packet >> info.ownerName;

	return packet;
}

std::ostream & operator<<(std::ostream & stream, sf::Vector2f vec)
{
	stream << vec.x << ' ' << vec.x << std::endl;
	return stream;
}

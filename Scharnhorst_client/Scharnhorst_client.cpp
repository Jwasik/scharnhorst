#include "pch.h"
#include "includes.h"
#include "localGame.h"
#include <windows.h>


const float maxFPS = 80;
float frameTime = 1000 / maxFPS; //czas klatki w ms


int main()
{
	try 
	{
		std::string playerName, shipType;
		std::cout << "type your name" << std::endl;
		std::getline(std::cin,playerName);
		std::cout << "choose your ship" << std::endl;
		std::getline(std::cin, shipType);


		LocalGame gameClient(playerName, shipType);
		std::string address;

		while (!gameClient.joinServer());
		gameClient.printAdresses();

		gameClient.gameLoop();
	}
	catch (std::string error)
	{
		std::cout << "exception occured" << std::endl;
		std::cout << error << std::endl;
	}
	return 0;
}
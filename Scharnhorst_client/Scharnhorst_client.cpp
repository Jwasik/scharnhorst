#include "pch.h"
#include "includes.h"
#include "localGame.h"
#include <windows.h>

const float maxFPS = 80;
float frameTime = 1000 / maxFPS; //czas klatki w ms

int main()
{
	LocalGame gameClient;
	std::string address;

	/*while (!gameClient.joinServer());
	gameClient.printAdresses();*/

	gameClient.gameLoop();
	return 0;
}
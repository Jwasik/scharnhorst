#include "pch.h"
#include "includes.h"
#include "localGame.h"



int main()
{
	LocalGame gameClient;
	std::string address;

	while (!gameClient.joinServer());
	gameClient.printAdresses();


	return 0;
}
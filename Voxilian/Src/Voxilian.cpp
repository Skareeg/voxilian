// Voxilian.cpp : Defines the entry point for the console application.
//
#include "..\stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <ctime>
#include "Game\Game.h"

int main(int argc, char** argv)
{
	std::cout<<"Welcome to Voxilian!\n";
	system("pause");
	Game gm;
	gm.Init();
	while(gm.isRunning)
	{
		gm.Run();
	}
	return 0;
}

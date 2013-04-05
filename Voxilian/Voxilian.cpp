// Voxilian.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include "Voxel.h"
#include <ctime>
#include "Types.h"
#include "GLSYS.h"
#include "Game.h"

int main(int argc, char** argv)
{
	std::cout<<"Welcome to Voxilian!\n";
	system("pause");
	Game gm;
	gm.Init();
	LOG("Game State Initialized.\n");
	while(glS.WindowEscaped()==false)
	{
		gm.Render();
		gm.Run();
	}
	LOG("Game State Terminating.\n");
	gm.End();
	return 0;
}

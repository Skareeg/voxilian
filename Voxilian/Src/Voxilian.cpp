// Voxilian.cpp : Defines the entry point for the console application.
//

#include "..\stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include "Voxel\Voxel.h"
#include <ctime>
#include "Utilities\Types.h"
#include "Utilities\GLSYS.h"
#include "Game.h"
//#include "Thread\tinythread.h"
#include <thread>

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

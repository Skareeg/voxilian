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
	Game gm;
	gm.Init();
	while(glS.WindowEscaped()==false)
	{
		gm.Render();
		gm.Run();
	}
	gm.End();
	return 0;
}

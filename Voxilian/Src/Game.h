#ifndef GAME_H
#define GAME_H

#include "Utilities\Types.h"
#include "Utilities\Math.h"
#include "Utilities\Camera.h"
#include "Utilities\GLSYS.h"
#include "Voxel\Voxel.h"
#include "Voxel\VoxelManager.h"
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Utilities\CMDCall.h"
#include "Voxel\Objects\VOX.h"

using namespace std;

class Game
{
public:
	Voxel vx;
	VoxelManager voxelmanager;
	Spacial::Manager m;
	void Init();
	void Render();
	void Run();
	void End();
};

#endif
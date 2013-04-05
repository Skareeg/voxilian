#ifndef GAME_H
#define GAME_H

#include "Types.h"
#include "Math.h"
#include "Camera.h"
#include "GLSYS.h"
#include "Voxel.h"
#include "VoxelManager.h"
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

class Game
{
public:
	Voxel vx;
	VoxelManager voxelmanager;
	void Init();
	void Render();
	void Run();
	void End();
};

#endif
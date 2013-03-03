#ifndef GAME_H
#define GAME_H

#include "Types.h"
#include "Math.h"
#include "Camera.h"
#include "GLSYS.h"
#include "Voxel.h"
#include "VoxelManager.h"

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
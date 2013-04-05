#ifndef CNKM_H
#define CNKM_H

#include "Types.h"
#include "VoxelChunk.h"
#include "Math.h"

#define VXSize 2
#define VZSize 2
#define VYSize 1

class VoxelManager
{
public:
	//These are the voxel objects. They are vectorized to allow for a large voxel world.
	std::vector<VoxelChunk> voxels;

	//This is the write position for the voxel manager.
	Vector3 vwrite;

	//Initialize the voxel manager.
	void Init();

	//Update the voxels and manager.
	void Update(Vector3 vpos);

	//Render the voxels.
	void Render();

	//Create voxels spheres.
	void VDSphere(Vector3 vpos, float radius, float density, bool solid);
};

#endif
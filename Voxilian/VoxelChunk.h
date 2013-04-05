#ifndef VOXC_H
#define VOXC_H

#include "Types.h"
#include "Math.h"
#include "GLSYS.h"
#include "Voxel.h"

class VoxelChunk
{
public:
	//These are the voxels themselves.
	Voxel vxVoxels[VoxSize+1][VoxSize+1][VoxSize+1];

	//This is the voxels position.
	Vector3 vPosition;

	//This is this voxels local write position.
	Vector3 vWrite;

	//This is the voxel initiation code. It must be called.
	void Init(Vector3 position);

	//This is the marching cubes application code. Call to update from the density grid.
	void Calculate();

	//This is the voxel drawing code.
	void Draw();

	//This is the code to create spheres in the voxel.
	void VDSphere(float radius, float density, bool solid);
};
#endif
#ifndef VOX_H
#define VOX_H

#include "Types.h"
#include "Math.h"
#include "GLSYS.h"

//This is the threshold value for the chunk.
#define VoxHold 0.5f
//This is the standard size of a chunk.
#define VoxSize 10

//These are the types of voxels available.
#define VOXTYPE_TRIAG 0
#define VOXTYPE_CUBE 1
#define VOXTYPE_HEX 2

class VoxelChunk;

class Voxel
{
public:
	//This defines the type of voxel.
	int nType;

	//This is the density grid.
	float fDensity;

	//This is the voxels position.
	Vector3 vPosition;

	//These are the voxels neighbors.
	VoxelChunk* vcVoxelChunk;

	//This is the voxels associated gridcell.
	VoxelCell vc;

	//This is the triangular mesh of this voxel, if used.
	std::vector<Triangle> mesh;

	//This is the voxel initiation code. It must be called.
	void Init(Vector3 position);

	//This is the MC calcuation code.
	void Calculate();

	//This is the voxel drawing code.
	void Draw();
};
#endif